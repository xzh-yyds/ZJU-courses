# Homework 2

##### Merkle Patricia Tire的数据结构

node的数据结构

```go
type node interface {
	fstring(string) string
	cache() (hashNode, bool)
}

type (
	fullNode struct {
		Children [17]node // Actual trie node data to encode/decode (needs custom encoder)
		flags    nodeFlag
	}
	shortNode struct {
		Key   []byte
		Val   node
		flags nodeFlag
	}
	hashNode  []byte
	valueNode []byte
)
```

可以看到node一共有4种类型, 其中

+ `fullNode`对应了黄皮书里的分支节点
+ `shortNode`对应了黄皮书里的拓展节点和叶子节点, `shortNode.Val`的类型表示当前节点是叶子节点还是拓展节点
	+ `shortNode.Val`是`valueNode`表示当前节点是叶节点
	+ `shortNode.Val`指向下一个node表示当前节点是拓展节点



tire的数据结构

```go
// Trie is a Merkle Patricia Trie.
// The zero value is an empty trie with no database.
// Use New to create a trie that sits on top of a database.
//
// Trie is not safe for concurrent use.
type Trie struct {
	root         node
	db           Database
	originalRoot common.Hash

	// Cache generation values.
	// cachegen increases by one with each commit operation.
	// new nodes are tagged with the current generation and unloaded
	// when their generation is older than than cachegen-cachelimit.
	cachegen, cachelimit uint16
}
```

+ `root`是当前的root节点 
+ `db`是后端的KV储存
+ `originalRoot`是启动时加载的hash值, 通过这个hash值可以在数据库里会恢复出整颗tire树
+ `cachegen`是当前tire树的cache版本, 每次调用commit的时候cache版本号会增加, cache版本会被附在node上, 如果当前的`cachegen - cachelimit`大于node的cache版本, 说明node已经过期了, 会被从内存中移除, 也就是cache更新的LRU算法, 一个node缓存如果一段时间没有被使用就会被清理掉



##### 操作流程

tire的new操作

```go
// New creates a trie with an existing root node from db.
//
// If root is the zero hash or the sha3 hash of an empty string, the
// trie is initially empty and does not require a database. Otherwise,
// New will panic if db is nil and returns a MissingNodeError if root does
// not exist in the database. Accessing the trie loads nodes from db on demand.
func New(root common.Hash, db *Database) (*Trie, error) {
	if db == nil {
		panic("trie.New called without a database")
	}
	trie := &Trie{
		db: db,
	}
	if root != (common.Hash{}) && root != emptyRoot {
		rootnode, err := trie.resolveHash(root[:], nil)
		if err != nil {
			return nil, err
		}
		trie.root = rootnode
	}
	return trie, nil
}
```

new操作接收一个hash值和一个Database参数

+ hash值不为空表示从数据库加载一个已经存在的tire树, 要调用`tire.resolveHash`来加载整颗树
+ 否则就新建一个tire树并返回



Tire树的使用流程

首先创建一个空的Trie树，然后插入一些数据，最后调用trie.Commit()方法进行序列化并得到一个hash值(root)

```go
func TestInsert(t *testing.T) {
	trie := newEmpty()
	updateString(trie, "doe", "reindeer")
	updateString(trie, "dog", "puppy")
	updateString(trie, "do", "cat")
	root, err := trie.Commit()
}
```

Commit()经过一系列的调用，最终调用了hasher.go的hash方法

```go
func (t *Trie) Commit() (root common.Hash, err error) {
	if t.db == nil {
		panic("Commit called on trie with nil database")
	}
	return t.CommitTo(t.db)
}
// CommitTo writes all nodes to the given database.
// Nodes are stored with their sha3 hash as the key.
//
// Committing flushes nodes from memory. Subsequent Get calls will
// load nodes from the trie's database. Calling code must ensure that
// the changes made to db are written back to the trie's attached
// database before using the trie.
func (t *Trie) CommitTo(db DatabaseWriter) (root common.Hash, err error) {
	hash, cached, err := t.hashRoot(db)
	if err != nil {
		return (common.Hash{}), err
	}
	t.root = cached
	t.cachegen++
	return common.BytesToHash(hash.(hashNode)), nil
}
func (t *Trie) hashRoot(db DatabaseWriter) (node, node, error) {
	if t.root == nil {
		return hashNode(emptyRoot.Bytes()), nil, nil
	}
	h := newHasher(t.cachegen, t.cachelimit)
	defer returnHasherToPool(h)
	return h.hash(t.root, db, true)
}
```

hash方法主要做了两个操作。 一个是保留原有的树形结构，并用cache变量中， 另一个是计算原有树形结构的hash并把hash值存放到cache变量中保存下来。

计算原有hash值的主要流程是首先调用h.hashChildren(n,db)把所有的子节点的hash值求出来，把原有的子节点替换成子节点的hash值。 这是一个递归调用的过程，会从树叶依次往上计算直到树根。然后调用store方法计算当前节点的hash值，并把当前节点的hash值放入cache节点，设置dirty参数为false(新创建的节点的dirty值是为true的)，然后返回，返回值cache变量包含了原有的node节点，并且包含了node节点的hash值，hash变量返回了当前节点的hash值(这个值其实是根据node和node的所有子节点计算出来的)。

```go
// hash collapses a node down into a hash node, also returning a copy of the
// original node initialized with the computed hash to replace the original one.
func (h *hasher) hash(n node, db DatabaseWriter, force bool) (node, node, error) {
	// If we're not storing the node, just hashing, use available cached data
	if hash, dirty := n.cache(); hash != nil {
		if db == nil {
			return hash, n, nil
		}
		if n.canUnload(h.cachegen, h.cachelimit) {
			// Unload the node from cache. All of its subnodes will have a lower or equal
			// cache generation number.
			cacheUnloadCounter.Inc(1)
			return hash, hash, nil
		}
		if !dirty {
			return hash, n, nil
		}
	}
	// Trie not processed yet or needs storage, walk the children
	collapsed, cached, err := h.hashChildren(n, db)
	if err != nil {
		return hashNode{}, n, err
	}
	hashed, err := h.store(collapsed, db, force)
	if err != nil {
		return hashNode{}, n, err
	}
	// Cache the hash of the node for later reuse and remove
	// the dirty flag in commit mode. It's fine to assign these values directly
	// without copying the node first because hashChildren copies it.
	cachedHash, _ := hashed.(hashNode)
	switch cn := cached.(type) {
	case *shortNode:
		cn.flags.hash = cachedHash
		if db != nil {
			cn.flags.dirty = false
		}
	case *fullNode:
		cn.flags.hash = cachedHash
		if db != nil {
			cn.flags.dirty = false
		}
	}
	return hashed, cached, nil
}
```

hashChildren方法,这个方法把所有的子节点替换成他们的hash，可以看到cache变量接管了原来的Trie树的完整结构，collapsed变量把子节点替换成子节点的hash值。

- 如果当前节点是shortNode, 首先把collapsed.Key从Hex Encoding 替换成 Compact Encoding, 然后递归调用hash方法计算子节点的hash和cache，这样就把子节点替换成了子节点的hash值
- 如果当前节点是fullNode, 那么遍历每个子节点，把子节点替换成子节点的Hash值
- 否则的化这个节点没有children，直接返回

```go
// hashChildren replaces the children of a node with their hashes if the encoded
// size of the child is larger than a hash, returning the collapsed node as well
// as a replacement for the original node with the child hashes cached in.
func (h *hasher) hashChildren(original node, db DatabaseWriter) (node, node, error) {
	var err error

	switch n := original.(type) {
	case *shortNode:
		// Hash the short node's child, caching the newly hashed subtree
		collapsed, cached := n.copy(), n.copy()
		collapsed.Key = hexToCompact(n.Key)
		cached.Key = common.CopyBytes(n.Key)

		if _, ok := n.Val.(valueNode); !ok {
			collapsed.Val, cached.Val, err = h.hash(n.Val, db, false)
			if err != nil {
				return original, original, err
			}
		}
		if collapsed.Val == nil {
			collapsed.Val = valueNode(nil) // Ensure that nil children are encoded as empty strings.
		}
		return collapsed, cached, nil

	case *fullNode:
		// Hash the full node's children, caching the newly hashed subtrees
		collapsed, cached := n.copy(), n.copy()

		for i := 0; i < 16; i++ {
			if n.Children[i] != nil {
				collapsed.Children[i], cached.Children[i], err = h.hash(n.Children[i], db, false)
				if err != nil {
					return original, original, err
				}
			} else {
				collapsed.Children[i] = valueNode(nil) // Ensure that nil children are encoded as empty strings.
			}
		}
		cached.Children[16] = n.Children[16]
		if collapsed.Children[16] == nil {
			collapsed.Children[16] = valueNode(nil)
		}
		return collapsed, cached, nil

	default:
		// Value and hash nodes don't have children so they're left as were
		return n, original, nil
	}
}
```

store方法，如果一个node的所有子节点都替换成了子节点的hash值，那么直接调用rlp.Encode方法对这个节点进行编码，如果编码后的值小于32，并且这个节点不是根节点，那么就把他们直接存储在他们的父节点里面，否者调用h.sha.Write方法进行hash计算，然后把hash值和编码后的数据存储到数据库里面，然后返回hash值。

```go
func (h *hasher) store(n node, db DatabaseWriter, force bool) (node, error) {
	// Don't store hashes or empty nodes.
	if _, isHash := n.(hashNode); n == nil || isHash {
		return n, nil
	}
	// Generate the RLP encoding of the node
	h.tmp.Reset()
	if err := rlp.Encode(h.tmp, n); err != nil {
		panic("encode error: " + err.Error())
	}

	if h.tmp.Len() < 32 && !force {
		return n, nil // Nodes smaller than 32 bytes are stored inside their parent
	}
	// Larger nodes are replaced by their hash and stored in the database.
	hash, _ := n.cache()
	if hash == nil {
		h.sha.Reset()
		h.sha.Write(h.tmp.Bytes())
		hash = hashNode(h.sha.Sum(nil))
	}
	if db != nil {
		return hash, db.Put(hash, h.tmp.Bytes())
	}
	return hash, nil
}
```



tire树的查询

```go
// Get returns the value for key stored in the trie.
// The value bytes must not be modified by the caller.
func (t *Trie) Get(key []byte) []byte {
	res, err := t.TryGet(key)
	if err != nil {
		log.Error(fmt.Sprintf("Unhandled trie error: %v", err))
	}
	return res
}

// TryGet returns the value for key stored in the trie.
// The value bytes must not be modified by the caller.
// If a node was not found in the database, a MissingNodeError is returned.
func (t *Trie) TryGet(key []byte) ([]byte, error) {
	value, newroot, didResolve, err := t.tryGet(t.root, keybytesToHex(key), 0)
	if err == nil && didResolve {
		t.root = newroot
	}
	return value, err
}

func (t *Trie) tryGet(origNode node, key []byte, pos int) (value []byte, newnode node, didResolve bool, err error) {
	switch n := (origNode).(type) {
	case nil:
		return nil, nil, false, nil
	case valueNode:
		return n, n, false, nil
	case *shortNode:
		if len(key)-pos < len(n.Key) || !bytes.Equal(n.Key, key[pos:pos+len(n.Key)]) {
			// key not found in trie
			return nil, n, false, nil
		}
		value, newnode, didResolve, err = t.tryGet(n.Val, key, pos+len(n.Key))
		if err == nil && didResolve {
			n = n.copy()
			n.Val = newnode
		}
		return value, n, didResolve, err
	case *fullNode:
		value, newnode, didResolve, err = t.tryGet(n.Children[key[pos]], key, pos+1)
		if err == nil && didResolve {
			n = n.copy()
			n.Children[key[pos]] = newnode
		}
		return value, n, didResolve, err
	case hashNode:
		child, err := t.resolveHash(n, key[:pos])
		if err != nil {
			return nil, n, true, err
		}
		value, newnode, _, err := t.tryGet(child, key, pos)
		return value, newnode, true, err
	default:
		panic(fmt.Sprintf("%T: invalid node: %v", origNode, origNode))
	}
}

// TryGetNode attempts to retrieve a trie node by compact-encoded path. It is not
// possible to use keybyte-encoding as the path might contain odd nibbles.
func (t *Trie) TryGetNode(path []byte) ([]byte, int, error) {
	item, newroot, resolved, err := t.tryGetNode(t.root, compactToHex(path), 0)
	if err != nil {
		return nil, resolved, err
	}
	if resolved > 0 {
		t.root = newroot
	}
	if item == nil {
		return nil, resolved, nil
	}
	enc, err := rlp.EncodeToBytes(item)
	if err != nil {
		log.Error("Encoding existing trie node failed", "err", err)
		return nil, resolved, err
	}
	return enc, resolved, err
}

func (t *Trie) tryGetNode(origNode node, path []byte, pos int) (item node, newnode node, resolved int, err error) {
	// If we reached the requested path, return the current node
	if pos >= len(path) {
		// Don't return collapsed hash nodes though
		if _, ok := origNode.(hashNode); !ok {
			// Short nodes have expanded keys, compact them before returning
			item := origNode
			if sn, ok := item.(*shortNode); ok {
				item = &shortNode{
					Key: hexToCompact(sn.Key),
					Val: sn.Val,
				}
			}
			return item, origNode, 0, nil
		}
	}
	// Path still needs to be traversed, descend into children
	switch n := (origNode).(type) {
	case nil:
		// Non-existent path requested, abort
		return nil, nil, 0, nil

	case valueNode:
		// Path prematurely ended, abort
		return nil, nil, 0, nil

	case *shortNode:
		if len(path)-pos < len(n.Key) || !bytes.Equal(n.Key, path[pos:pos+len(n.Key)]) {
			// Path branches off from short node
			return nil, n, 0, nil
		}
		item, newnode, resolved, err = t.tryGetNode(n.Val, path, pos+len(n.Key))
		if err == nil && resolved > 0 {
			n = n.copy()
			n.Val = newnode
		}
		return item, n, resolved, err

	case *fullNode:
		item, newnode, resolved, err = t.tryGetNode(n.Children[path[pos]], path, pos+1)
		if err == nil && resolved > 0 {
			n = n.copy()
			n.Children[path[pos]] = newnode
		}
		return item, n, resolved, err

	case hashNode:
		child, err := t.resolveHash(n, path[:pos])
		if err != nil {
			return nil, n, 1, err
		}
		item, newnode, resolved, err := t.tryGetNode(child, path, pos)
		return item, newnode, resolved + 1, err

	default:
		panic(fmt.Sprintf("%T: invalid node: %v", origNode, origNode))
	}
}
```

查询节点主要是调用`Get`方法, 遍历tire树来获取key



tire树的插入

```go
func (t *Trie) insert(n node, prefix, key []byte, value node) (bool, node, error) {
	if len(key) == 0 {
		if v, ok := n.(valueNode); ok {
			return !bytes.Equal(v, value.(valueNode)), value, nil
		}
		return true, value, nil
	}
	switch n := n.(type) {
	case *shortNode:
		matchlen := prefixLen(key, n.Key)
		// If the whole key matches, keep this short node as is
		// and only update the value.
		if matchlen == len(n.Key) {
			dirty, nn, err := t.insert(n.Val, append(prefix, key[:matchlen]...), key[matchlen:], value)
			if !dirty || err != nil {
				return false, n, err
			}
			return true, &shortNode{n.Key, nn, t.newFlag()}, nil
		}
		// Otherwise branch out at the index where they differ.
		branch := &fullNode{flags: t.newFlag()}
		var err error
		_, branch.Children[n.Key[matchlen]], err = t.insert(nil, append(prefix, n.Key[:matchlen+1]...), n.Key[matchlen+1:], n.Val)
		if err != nil {
			return false, nil, err
		}
		_, branch.Children[key[matchlen]], err = t.insert(nil, append(prefix, key[:matchlen+1]...), key[matchlen+1:], value)
		if err != nil {
			return false, nil, err
		}
		// Replace this shortNode with the branch if it occurs at index 0.
		if matchlen == 0 {
			return true, branch, nil
		}
		// Otherwise, replace it with a short node leading up to the branch.
		return true, &shortNode{key[:matchlen], branch, t.newFlag()}, nil

	case *fullNode:
		dirty, nn, err := t.insert(n.Children[key[0]], append(prefix, key[0]), key[1:], value)
		if !dirty || err != nil {
			return false, n, err
		}
		n = n.copy()
		n.flags = t.newFlag()
		n.Children[key[0]] = nn
		return true, n, nil

	case nil:
		return true, &shortNode{key, value, t.newFlag()}, nil

	case hashNode:
		// We've hit a part of the trie that isn't loaded yet. Load
		// the node and insert into it. This leaves all child nodes on
		// the path to the value in the trie.
		rn, err := t.resolveHash(n, prefix)
		if err != nil {
			return false, nil, err
		}
		dirty, nn, err := t.insert(rn, prefix, key, value)
		if !dirty || err != nil {
			return false, rn, err
		}
		return true, nn, nil

	default:
		panic(fmt.Sprintf("%T: invalid node: %v", n, n))
	}
}
```

tire树的插入是一个递归调用, 从根节点开始一起往下, 知道找到可以插入的位置

+ 参数`node`是当前的节点
+ `prefix`是当前已经处理完的key部分
+ `key`是没有处理的key部分
+ `value`是要插入的值
+ bool类型的返回值表示操作是否更新了tire
+ node类型的返回值是完成插入后的根节点
+ error类型的返回值是错误信息

具体操作:

+ 如果节点类型是nil说明整棵树是空的, 直接返回`shortNode{key, value, t.newFlag()}`, 然后整棵树的根就有了一个`shortNode`节点
+ 如果当前节点是`shortNode`(叶节点), 首先计算公共前缀, 如果公共前缀相同, 说明两个key是一样的, 如果value也一样, 就返回一个错误, 如果没有错误就更新`shortNode`的值然后返回, 如果公共前缀不完全匹配, 就需要把公共前缀提取出来形成一个独立的节点(拓展节点), 拓展节点后面连接一个branch节点
+ 如果当前节点是`fullNode`(branch节点), 直接向对应子节点调用insert方法, 然后把对应子节点指向新的节点
+ 如果当前节点是`hashNode`, 说明对应的节点还不在内存里, 先调用`t.resolveHash`把节点加载到内存, 然后对其调用insert方法



##### MPT的作用

MPT在以太坊中主要用来存储用户账户的状态及其变更，交易信息，交易的收据信息等等。

MPT将PT中的普通指针换成了hash指针，这样就可以计算出一个根hash值，并写到以太坊的block header中，只要整棵树中有一个分支发生了改变，根节点的hash值就会改变，这样就可以防止数据被篡改，以太坊中账户的安全就得到了保障。

MPT还提供了merkle proof，可以将整个账户的一条分支发给某个节点，来帮助它验证某个账户中的余额状态。

MPT可以用来证明某个是否不存在，方法和sorted MT一样，先找到账户会在MPT中的位置，然后把位置的分支做merkle proof，就可以证明该账户是否存在。