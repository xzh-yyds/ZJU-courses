# Homework 3

##### Fabric交易流程

1. 客户端使用相应的SDK提供的API构造并提交交易提案，提案中包含

	+ channellD: 通道信息
	+ chaincodeID: 要调用的链码信息
	+ timestamp: 时间戳
	+ sign: 客户端签名
	+ txPayload: 事务本身内容

2. 背书节点对接收到的交易提案请求进行验证，包括

	+ 交易提案格式是否正确
	+ 交易在之前并未提交过
	+ 客户端签名是否有效
	+ 请求者在通道中是否有相应的权限

	验证通过后，会调用链码进行模拟执行，产生包括响应值，读集和写集的事物结果，对结果进行背书并响应给客户端

3. 客户端收到足够的消息和背书签名后，会构建合法的交易请求并广播给Ordering服务节点；

	如果客户端的请求仅仅是查询分类账，则客户端将检查查询相应信息，并且不会将事务提交给Ordering服务；

	如果客户端应用程序的请求时更新分类账本数据，则会将事务提交给Ordering服务以继续下一步的操作；并且客户端会在提交事务之前检查确定请求是否已经满足指定的认可策略(即指定的背书节点都认可)

4. 交易请求被提交到Ordering服务节点，该事务将包含读/写集，背书签名和通道ID，Ordering节点接收到事务请求之后，并不需要检查交易中的具体数据，它只是从网络中的所有通道接收交易，按时间顺序对他们进行排序，并创建交易区块，之后广播给同一通道内所有组织的Leader节点

5. Leader节点对接收到的区块进行验证, 包括

	+ 交易消息结构是否正确
	+ 是否重复
	+ 是否有足够的背书，读写集版本

	验证通过后将结果写入到本地的分类账本中

6. Leader节点同步广播给同一通道内的其他节点；

	分类账本更新: 每个Peer节点将区块附加到区块链中,，写集被提交到当前状态数据库中，并且对于每个有效的事务，发出一个事件，通知客户端事务已被不可变地附加到链中，以及该事务是否已经经过验证或为无效事务。



##### 涉及到的数据结构

step 1涉及到的数据结构:

chaincode：

```go
package main

import (
	"errors"
	"fmt"
	"github.com/hyperledger/fabric/core/chaincode/shim"
)

type DemoChaincode struct { }

func (t *DemoChaincode) Init(stub shim.ChaincodeStubInterface) pb.Response {
	// more logics using stub here
	return stub.Success(nil)
}

func (t *DemoChaincode) Invoke(stub shim.ChaincodeStubInterface) pb.Response
	// more logics using stub here
	return stub.Success(nil)
}

func main() {
	err := shim.Start(new(DemoChaincode))
	if err != nil {
		fmt.Printf("Error starting DemoChaincode: %s", err)
	}
}
```

chaincode启动时调用shim层的Start方法，然后初始化.



step 2涉及到的数据结构：

endorser：（代码略去了细节）

```go
package endorser

import ()

var endorserLogger = flogging.MustGetLogger("endorser")

type PrivateDataDistributor interface {}

type Support interface {}

type ChannelFetcher interface {}

type Channel struct {}

type Endorser struct {}

func (e *Endorser) callChaincode(txParams *ccprovider.TransactionParams, input *pb.ChaincodeInput, chaincodeName string) (*pb.Response, *pb.ChaincodeEvent, error) {}

func (e *Endorser) SimulateProposal(txParams *ccprovider.TransactionParams, chaincodeName string, chaincodeInput *pb.ChaincodeInput) (*pb.Response, []byte, *pb.ChaincodeEvent, error) {}

func (e *Endorser) preProcess(up *UnpackedProposal, channel *Channel) error {}

func (e *Endorser) ProcessProposal(ctx context.Context, signedProp *pb.SignedProposal) (*pb.ProposalResponse, error) {}

func (e *Endorser) ProcessProposalSuccessfullyOrError(up *UnpackedProposal) (*pb.ProposalResponse, error) {}

func acquireTxSimulator(chainID string, chaincodeName string) bool {}

func shorttxid(txid string) string {}

func CreateCCEventBytes(ccevent *pb.ChaincodeEvent) ([]byte, error) {}

func decorateLogger(logger *flogging.FabricLogger, txParams *ccprovider.TransactionParams) *flogging.FabricLogger {}
```

endorser会调用ProcessProposal进行具体的背书处理



step 3涉及到的数据结构:

orderer：

orderer节点启动时调用order包下的main方法

```go
func Main() {
	fullCmd := kingpin.MustParse(app.Parse(os.Args[1:]))

	// "version" command
	if fullCmd == version.FullCommand() {
		fmt.Println(metadata.GetVersionInfo())
		return
	}

	conf := config.Load()
	initializeLoggingLevel(conf)
	initializeLocalMsp(conf)

	Start(fullCmd, conf)
}
```

其中start方法时启动后的核心内容

```go
func Start(cmd string, conf *config.TopLevel) {
	logger.Debugf("Start()")
	signer := localmsp.NewSigner()
	manager := initializeMultichannelRegistrar(conf, signer)
	server := NewServer(manager, signer, &conf.Debug)

	switch cmd {
	case start.FullCommand(): // "start" command
		logger.Infof("Starting %s", metadata.GetVersionInfo())
		initializeProfilingService(conf)
		grpcServer := initializeGrpcServer(conf)
		ab.RegisterAtomicBroadcastServer(grpcServer.Server(), server)
		logger.Info("Beginning to serve requests")
		grpcServer.Start()
	case benchmark.FullCommand(): // "benchmark" command
		logger.Info("Starting orderer in benchmark mode")
		benchmarkServer := performance.GetBenchmarkServer()
		benchmarkServer.RegisterService(server)
		benchmarkServer.Start()
	}
}
```

包括gRPC服务结构初始化以及gRPC服务的启动



step 4中涉及到的数据结构:

3种排序服务: Solo, Kafka, Raft

solo：（略去细节）

```go
package solo

import ()

var logger = flogging.MustGetLogger("orderer.consensus.solo")

type consenter struct{}
type chain struct {
    support  consensus.ConsenterSupport
    sendChan chan *message
    exitChan chan struct{}
}
type message struct {
    configSeq uint64
    normalMsg *cb.Envelope
    configMsg *cb.Envelope
}

func New() consensus.Consenter {}

func (solo *consenter) HandleChain(support consensus.ConsenterSupport, metadata *cb.Metadata) (consensus.Chain, error) {}

func newChain(support consensus.ConsenterSupport) *chain {}
func (ch *chain) Start() {}
func (ch *chain) Halt() {}
func (ch *chain) WaitReady() error {}
func (ch *chain) Order(env *cb.Envelope, configSeq uint64) error {}
func (ch *chain) Configure(config *cb.Envelope, configSeq uint64) error {}
func (ch *chain) Errored() <-chan struct{} {}
func (ch *chain) main() {}
```

其中main方法的主体是一个for循环：

```go
func (ch *chain) main() {
    var timer <-chan time.Time
    var err error

    for {
        seq := ch.support.Sequence()
        err = nil
        select {
        case msg := <-ch.sendChan:
            if msg.configMsg == nil {
                // NormalMsg
                if msg.configSeq < seq {
                    _, err = ch.support.ProcessNormalMsg(msg.normalMsg)
                    if err != nil {
                        logger.Warningf("Discarding bad normal message: %s", err)
                        continue
                    }
                }
                batches, pending := ch.support.BlockCutter().Ordered(msg.normalMsg)

                for _, batch := range batches {
                    block := ch.support.CreateNextBlock(batch)
                    ch.support.WriteBlock(block, nil)
                }

                switch {
                case timer != nil && !pending:
                    // Timer is already running but there are no messages pending, stop the timer
                    timer = nil
                case timer == nil && pending:
                    // Timer is not already running and there are messages pending, so start it
                    timer = time.After(ch.support.SharedConfig().BatchTimeout())
                    logger.Debugf("Just began %s batch timer", ch.support.SharedConfig().BatchTimeout().String())
                default:
                    // Do nothing when:
                    // 1. Timer is already running and there are messages pending
                    // 2. Timer is not set and there are no messages pending
                }

            } else {
                // ConfigMsg
                if msg.configSeq < seq {
                    msg.configMsg, _, err = ch.support.ProcessConfigMsg(msg.configMsg)
                    if err != nil {
                        logger.Warningf("Discarding bad config message: %s", err)
                        continue
                    }
                }
                batch := ch.support.BlockCutter().Cut()
                if batch != nil {
                    block := ch.support.CreateNextBlock(batch)
                    ch.support.WriteBlock(block, nil)
                }

                block := ch.support.CreateNextBlock([]*cb.Envelope{msg.configMsg})
                ch.support.WriteConfigBlock(block, nil)
                timer = nil
            }
        case <-timer:
            //clear the timer
            timer = nil

            batch := ch.support.BlockCutter().Cut()
            if len(batch) == 0 {
                logger.Warningf("Batch timer expired with no pending requests, this might indicate a bug")
                continue
            }
            logger.Debugf("Batch timer expired, creating block")
            block := ch.support.CreateNextBlock(batch)
            ch.support.WriteBlock(block, nil)
        case <-ch.exitChan:
            logger.Debugf("Exiting")
            return
        }
    }
}
```

Kafka的主要过程也是一个for循环：（略去很多细节）

```go
func (chain *chainImpl) processMessagesToBlocks() ([]uint64, error) {
    ......
    for {
        select {
        case <-chain.haltChan:
        case kafkaErr := <-chain.channelConsumer.Errors():
            logger.Errorf("[channel: %s] Error during consumption: %s", chain.ChannelID(), kafkaErr)
            counts[indexRecvError]++
            select {
            case <-chain.errorChan: // If already closed, don't do anything
            default:
                switch kafkaErr.Err {
                case sarama.ErrOffsetOutOfRange:
                default:
                }
            }
            select {
            case <-chain.errorChan: // we are not ignoring the error
            default: // we are ignoring the error
            }
        case <-topicPartitionSubscriptionResumed:
        case <-deliverSessionTimedOut:
        case in, ok := <-chain.channelConsumer.Messages():
            if !ok {}
            if topicPartitionSubscriptionResumed != nil {}
            select {
            case <-chain.errorChan: // If this channel was closed...
            default:
            }
            if err := proto.Unmarshal(in.Value, msg); err != nil {} 
            else {}
            switch msg.Type.(type) {
            case *ab.KafkaMessage_Connect:
            case *ab.KafkaMessage_TimeToCut:
            case *ab.KafkaMessage_Regular:
            }
        case <-chain.timer:
        }
    }
}
```

Raft的主要过程还是一个for循环：（略去很多细节）

```go
func (c *Chain) run() {
    ......
    for {
        select {
        case s := <-submitC:
            if s == nil {continue}
            if soft.RaftState == raft.StatePreCandidate || soft.RaftState == raft.StateCandidate {}
            s.leader <- soft.Lead
            if soft.Lead != c.raftID {continue}
            batches, pending, err := c.ordered(s.req)
            if err != nil {}
            if pending {startTimer()} 
            else {stopTimer()}
            c.propose(propC, bc, batches...)
            if c.configInflight {}
            else if c.blockInflight >= c.opts.MaxInflightBlocks {}

        case app := <-c.applyC:
            if app.soft != nil {
                newLeader := atomic.LoadUint64(&app.soft.Lead) // etcdraft requires atomic access
                if newLeader != soft.Lead {}
                foundLeader := soft.Lead == raft.None && newLeader != raft.None
                quitCandidate := isCandidate(soft.RaftState) && !isCandidate(app.soft.RaftState)
                if foundLeader || quitCandidate {}
                if isCandidate(app.soft.RaftState) || newLeader == raft.None {}
                soft = raft.SoftState{Lead: newLeader, RaftState: app.soft.RaftState}
                select {
                case c.observeC <- soft:
                default:
                }
            }
            c.apply(app.entries)
            if c.justElected {} 
            else if c.configInflight {} 
            else if c.blockInflight < c.opts.MaxInflightBlocks {}

        case <-timer.C():
            ticking = false
            batch := c.support.BlockCutter().Cut()
            if len(batch) == 0 {
                c.logger.Warningf("Batch timer expired with no pending requests, this might indicate a bug")
                continue
            }
            c.logger.Debugf("Batch timer expired, creating block")
            c.propose(propC, bc, batch) // we are certain this is normal block, no need to block

        case sn := <-c.snapC:
            if sn.Metadata.Index != 0 {} 
            else {}
            if err := c.catchUp(sn); err != nil {}

        case <-c.doneC:
            stopTimer()
            cancelProp()
            select {
            case <-c.errorC: // avoid closing closed channel
            default:
                close(c.errorC)
            }
            c.logger.Infof("Stop serving requests")
            c.periodicChecker.Stop()
            return
        }
    }
}
```



step 6中涉及到通道：

通道创建:

- 客户端调用 sendCreateChainTransaction()，检查指定的配置交易文件，或者利用默认配置，构造一个创建应用通道的配置交易结构，封装为 Envelope，指定 channel 头部类型为 CONFIG_UPDATE。
- 客户端发送配置交易到 Ordering 服务。
- Orderer 收到 CONFIG_UPDATE 消息后，检查指定的通道还不存在，则开始新建过程，构造该应用通道的初始区块。
	- Orderer 首先检查通道应用（Application）配置中的组织都在创建的联盟（Consortium）配置组织中。
	- 之后从系统通道中获取 Orderer 相关的配置，并创建应用通道配置，对应 mod_policy 为系统通道配置中的联盟指定信息。
	- 接下来根据 CONFIG_UPDATE 消息的内容更新获取到的配置信息。所有配置发生变更后版本号都要更新。
	- 最后，创建签名 Proposal 消息（头部类型为 ORDERER_TRANSACTION），发送到系统通道中，完成应用通道的创建过程。
- 客户端利用 gRPC 通道从 Orderer 服务获取到该应用通道的初始区块（具体过程类似 fetch 命令）。
- 客户端将收到的区块写入到本地的 chainID + ".block" 文件。这个文件后续会被需要加入到通道的节点使用。

通道加入：

- 客户端首先创建一个 ChaincodeSpec 结构，其 input 中的 Args 第一个参数是 CSCC.JoinChain（指定调用配置链码的操作），第二个参数为所加入通道的初始区块。
- 利用 ChaincodeSpec 构造一个 ChaincodeInvocationSpec 结构。
- 利用 ChaincodeInvocationSpec，创建 Proposal 结构并进行签名，channel 头部类型为 CONFIG。
- 客户端通过 gRPC 将 Proposal 签名后发给 Endorser（所操作的 Peer），调用 `ProcessProposal(ctx context.Context, in *SignedProposal, opts ...grpc.CallOption) (*ProposalResponse, error)` 方法进行处理，主要通过配置系统链码进行本地链的初始化工作。
- 初始化完成后，即可收到来自通道内的 Gossip 消息等。



整个过程中涉及到的：

Peer节点：（略去很多细节）

```go
package peer

import ()

var peerLogger = flogging.MustGetLogger("peer")

type CollectionInfoShim struct {}
func (cis *CollectionInfoShim) CollectionValidationInfo(chaincodeName, collectionName string, validationState validation.State) ([]byte, error, error) {}
type gossipSupport struct {}
func ConfigBlockFromLedger(ledger ledger.PeerLedger) (*common.Block, error) {}
func (p *Peer) updateTrustedRoots(cm channelconfig.Resources) {}
type DeliverChainManager struct {}
func (d DeliverChainManager) GetChain(chainID string) deliver.Chain {}
type fileLedgerBlockStore struct {}
func (flbs fileLedgerBlockStore) AddBlock(*common.Block) error {}
func (flbs fileLedgerBlockStore) RetrieveBlocks(startBlockNumber uint64) (commonledger.ResultsIterator, error) {}
func (flbs fileLedgerBlockStore) Shutdown() {}
func NewConfigSupport(peer *Peer) cc.Manager {}
type configSupport struct {}
func (c *configSupport) GetChannelConfig(cid string) cc.Config {}
type Peer struct {}
func (p *Peer) openStore(cid string) (*transientstore.Store, error) {}

func (p *Peer) CreateChannel(
    cid string,
    cb *common.Block
    deployedCCInfoProvider ledger.DeployedChaincodeInfoProvider,
    legacyLifecycleValidation plugindispatcher.LifecycleResources,
    newLifecycleValidation plugindispatcher.CollectionAndLifecycleResources,
) error {}
func (p *Peer) CreateChannelFromSnapshot(
    snapshotDir string,
    deployedCCInfoProvider ledger.DeployedChaincodeInfoProvider,
    legacyLifecycleValidation plugindispatcher.LifecycleResources,
    newLifecycleValidation plugindispatcher.CollectionAndLifecycleResources,
) error {}

func RetrievePersistedChannelConfig(ledger ledger.PeerLedger) (*common.Config, error) {}

func (p *Peer) createChannel(
    cid string,
    l ledger.PeerLedger,
    deployedCCInfoProvider ledger.DeployedChaincodeInfoProvider,
    legacyLifecycleValidation plugindispatcher.LifecycleResources,
    newLifecycleValidation plugindispatcher.CollectionAndLifecycleResources,
) error {}

func (p *Peer) Channel(cid string) *Channel {}
func (p *Peer) StoreForChannel(cid string) *transientstore.Store {}
func (p *Peer) GetChannelsInfo() []*pb.ChannelInfo {}
func (p *Peer) GetChannelConfig(cid string) channelconfig.Resources {}
func (p *Peer) GetStableChannelConfig(cid string) channelconfig.Resources {}
func (p *Peer) GetLedger(cid string) ledger.PeerLedger {}
func (p *Peer) GetMSPIDs(cid string) []string {}
func (p *Peer) GetPolicyManager(cid string) policies.Manager {}
func (p *Peer) JoinBySnaphotStatus() *pb.JoinBySnapshotStatus {}
func (p *Peer) initChannel(cid string) {}
func (p *Peer) GetApplicationConfig(cid string) (channelconfig.Application, bool) {}

func (p *Peer) Initialize(
    init func(string),
    server *comm.GRPCServer,
    pm plugin.Mapper,
    deployedCCInfoProvider ledger.DeployedChaincodeInfoProvider,
    legacyLifecycleValidation plugindispatcher.LifecycleResources,
    newLifecycleValidation plugindispatcher.CollectionAndLifecycleResources,
    nWorkers int,
) {}
```

