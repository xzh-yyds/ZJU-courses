# Simple compiler of subset of C

### About files

src: source codes

docs:  the experiment report

test cases: just like its name

tokens.txt: what the scanner identifies

derivations: used in parsing

gram_tree_struct: about the structure of the AST

### Available features:
* while, for 
* if-else , switch-case
* +-*/
* int , float , double ,int* ,float*, double*
* function() 
* println

### derivations :
    ----------derivations----------
    
    program
        : 	translation_unit
        ;
    
    // 基本表达式
    primary_expression
        : 	IDENTIFIER 
        | 	TRUE 
        | 	CONSTANT_INT 
        | 	CONSTANT_DOUBLE 
        | 	'(' expression ')'
        ;
    
    // 后缀表达式
    postfix_expression
        : 	primary_expression
        | 	postfix_expression '[' expression ']'
        | 	postfix_expression '(' ')'
        | 	postfix_expression '(' argument_expression_list ')'
        | 	postfix_expression OP_INC
        | 	postfix_expression OP_DEC
        ;
    
    // 参数表
    argument_expression_list
        :	assignment_expression
        | 	argument_expression_list ',' assignment_expression
        ;
    
    // 一元表达式
    unary_expression
        :	postfix_expression
        | 	OP_INC unary_expression
        | 	OP_DEC unary_expression
        | 	unary_operator unary_expression
        ;
    
    // 单目运算符
    unary_operator
        :	'+' 
        | 	'-' 
        | 	'~' 
        | 	'!' 
        ;
    
    // 可乘表达式
    multiplicative_expression
        : 	unary_expression
        | 	multiplicative_expression '*' unary_expression
        | 	multiplicative_expression '/' unary_expression
        | 	multiplicative_expression '%' unary_expression
        ;
    
    // 可加表达式
    additive_expression
        : 	multiplicative_expression
        | 	additive_expression '+' multiplicative_expression
        | 	additive_expression '-' multiplicative_expression
        ;
    
    // 移位表达式
    shift_expression
        :	additive_expression
        | 	shift_expression OP_LEFTSHIFT additive_expression
        | 	shift_expression OP_RIGHTSHIFT additive_expression
        ;
    
    // 关系表达式
    relational_expression
        :	shift_expression
        | 	relational_expression '<' shift_expression
        | 	relational_expression '>' shift_expression
        | 	relational_expression OP_LE shift_expression
        | 	relational_expression OP_GE shift_expression
        ;
    
    // 相等表达式
    equality_expression
        :	relational_expression 
        | 	equality_expression OP_EQ relational_expression
        | 	equality_expression OP_NE relational_expression
        ;
    
    // 且
    and_expression
        :	equality_expression
        | 	and_expression '&' equality_expression
        ;
    
    // 异或
    exclusive_or_expression
        :	and_expression
        | 	exclusive_or_expression '^' and_expression
        ;
    
    // 或
    inclusive_or_expression
        : 	exclusive_or_expression
        | 	inclusive_or_expression '|' exclusive_or_expression
        ;
    
    // and逻辑表达式
    logical_and_expression
        :	inclusive_or_expression
        | 	logical_and_expression OP_AND inclusive_or_expression
        ;
    
    // or逻辑表达式
    logical_or_expression
        :	logical_and_expression
        | 	logical_or_expression OP_OR logical_and_expression
        ;
    
    // 赋值表达式
    assignment_expression
        :	logical_or_expression
        | 	unary_expression assignment_operator assignment_expression
        ;
    
    // 赋值运算符
    assignment_operator
        :	'='
        | 	ASSIGN_MUL
        | 	ASSIGN_DIV
        | 	ASSIGN_MOD
        | 	ASSIGN_ADD
        | 	ASSIGN_SUB 
        | 	ASSIGN_LEFTSHIFT
        | 	ASSIGN_RIGHTSHIFT
        | 	ASSIGN_AND
        | 	ASSIGN_XOR
        | 	ASSIGN_OR
        ;
    
    // 表达式
    expression
        :	assignment_expression
        | 	expression ',' assignment_expression
        ;
    
    // 定义与说明产生式: e.g. int a = 10, c = 12, d;
    declaration
        :	type_specifier ';'
        |	type_specifier init_declarator_list ';'
        ;
    
    // 系列定义/声明表
    init_declarator_list
        :	init_declarator
        |	init_declarator_list ',' init_declarator
        ;
    
    // 定义/定义并赋值
    init_declarator
        :	declarator
        | 	declarator '=' initializer
        ;
    
    // 类型说明符
    type_specifier
        :	VOID
        | 	CHAR
        | 	INT
        | 	DOUBLE
        |	FLOAT
        | 	BOOL
        ;
    
    // 说明符
    declarator
        :	IDENTIFIER 	//变量
        |	'(' declarator ')'	//.....
        | 	declarator '[' assignment_expression ']'	//数组 int k[10]
        |	declarator '[' '*' ']'	//....              
        |	declarator '[' ']'		//数组               c[] = "how are you"
        |	declarator '(' parameter_list ')'	//函数  fibonacci(int i,int j)    
        |	declarator '(' identifier_list ')'	//函数  fibonacci(0,1)
        |	declarator '(' ')'	//函数                  void swap()
        ;
    
    // 参数列表
    parameter_list
        :	parameter_declaration
        |	parameter_list ',' parameter_declaration
        ;
    
    // 参数声明
    parameter_declaration
        :	type_specifier declarator
        | 	type_specifier abstract_declarator
        | 	type_specifier
        ;
    
    // id列表
    identifier_list
        :	IDENTIFIER
        |	identifier_list ',' IDENTIFIER
        ;
    
    // 抽象声明
    abstract_declarator
        :	'(' abstract_declarator ')' 
        |	'[' ']'     
        |	'[' assignment_expression ']'
        |	abstract_declarator '[' ']'
        |	abstract_declarator '[' assignment_expression ']'
        |	'[' '*' ']'
        |	abstract_declarator '[' '*' ']'
        |	'(' ')'
        |	'(' parameter_list ')'
        |	abstract_declarator '(' ')'
        |	abstract_declarator '(' parameter_list ')'
        ;
    
    // 初始化 int a[4][] = {{1,2,3},1,3,}
    initializer
        :	assignment_expression
        |	'{' initializer_list '}' 		//列表初始化 {1,1,1}
        |	'{' initializer_list ',' '}'	//列表初始化 {1,1,1,}
        ;
    
    // 
    initializer_list
        :	initializer
        |	designation initializer
        |	initializer_list ',' initializer
        |	initializer_list ',' designation initializer
        ;
    
    // 左值赋值操作 a[1][2][3] = 
    designation
        :	designator_list '='
        ;
    
    //取值列表 数组中的数组(高维数组),嵌套结构体(struct)
    designator_list
        :	designator
        |	designator_list designator
        ;
    
    //指示器取值 数组的[index]取值 和结构体的.运算取成员变量值
    designator
        :	'[' logical_or_expression ']'
        |	'.' IDENTIFIER
        ;
    
    // 声明： 标签声明，符合声明，表达式声明，选择声明，循环声明，跳转声明
    statement
        :	labeled_statement
        |	compound_statement
        |	expression_statement
        |	selection_statement
        |	iteration_statement
        |	jump_statement
        ;
    
    // 标签声明 有goto 的目的标签 还有 switch-case的 case : 标签
    labeled_statement
        :	IDENTIFIER ':' statement
        |	CASE logical_or_expression ':' statement
        ;
    
    // 复合语句 在{}中写的部分代码
    compound_statement
        :	'{' '}'
        |	'{' block_item_list '}'
        ;
    
    // 匹配{}clause中的每一行操作
    block_item_list
        :	block_item
        |	block_item_list block_item
        ;
    
    // 每一行代码既可以是一个声明
    block_item
        :	declaration
        |	statement
        ;


    expression_statement
        :	';'
        |	expression ';'
        ;
    
    // 条件语句
    selection_statement
        :	IF '(' expression ')' statement %prec LOWER_THAN_ELSE
        |	IF '(' expression ')' statement ELSE statement
        |	SWITCH '(' expression ')' statement
        ;
    
    // 循环语句
    iteration_statement
        :	WHILE '(' expression ')' statement
        |	DO statement WHILE '(' expression ')' ';'
        |	FOR '(' expression_statement expression_statement ')' statement
        |	FOR '(' expression_statement expression_statement expression ')' statement
        |	FOR '(' declaration expression_statement ')' statement
        |	FOR '(' declaration expression_statement expression ')' statement
        ;
    
    // 跳转指令
    jump_statement
        :	GOTO IDENTIFIER ';'
        |	CONTINUE ';'
        |	BREAK ';'
        |	RETURN ';'
        |	RETURN expression ';'
        ;
    
    print_statement
    	: println '(' STRING_LITERAL ',' expression ')'';' 
    	;
    
    // 翻译单元 由一个个的external-declaration组成
    translation_unit
        :	external_declaration
        |	translation_unit external_declaration
        ;
    
    // 每一个.c 文件中的external-declaration不是全局数据声明就是函数声明
    external_declaration
        :	function_definition
        |	declaration
        ;
    
    // 函数定义   e.g.  int myfunc(int k, int j){};
    function_definition
        :	type_specifier declarator declaration_list compound_statement
        | 	type_specifier declarator compound_statement
        ;
        
    declaration_list
        :	declaration
        |	declaration_list declaration
        ;

