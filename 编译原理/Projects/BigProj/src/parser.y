%{
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "grammartree.h"
#include <cstdio>
#include "func.h"

extern char* yytext;
extern int col;
extern FILE* yyin;
extern FILE* yyout;
GrammarTreeNode* root = NULL;
extern int yylineno;
extern void yyerror(const char* msg);
extern int yylex(void);

string int2string(int a);
GrammarTreeNode *treeCreate(std::string name, int arg_cnt, ...);
void treeNodeFree(GrammarTreeNode *node);
void treePrint(GrammarTreeNode *node, int level);

%}

%token <gtn> AUTO SIZEOF GOTO RETURN println

%token <gtn> DO WHILE FOR CONTINUE BREAK SWITCH DEFAULT CASE IF ELSE

%token <gtn> FLOAT DOUBLE CHAR VOID INT LONG BOOL SHORT VOLATILE
%token <gtn> CONST SIGNED UNSIGNED

%token <gtn> STATIC EXTERN INLINE TYPEDEF STRUCT ENUM UNION

%token <gtn> CONSTANT CONSTANT_INT CONSTANT_DOUBLE
%token <gtn> ELLIPSIS STRING_LITERAL

%token <gtn> ASSIGN_RIGHTSHIFT ASSIGN_LEFTSHIFT
%token <gtn> ASSIGN_ADD ASSIGN_SUB ASSIGN_MUL ASSIGN_DIV ASSIGN_MOD
%token <gtn> ASSIGN_AND ASSIGN_OR TYPE_NAME ASSIGN_XOR

%token <gtn> IDENTIFIER

%token <gtn> OP_RIGHTSHIFT OP_LEFTSHIFT
%token <gtn> OP_INC OP_DEC OP_PTR
%token <gtn> OP_AND OP_OR OP_LE OP_GE OP_EQ OP_NE

%token <gtn> ';' ',' ':' '.' 			
%token <gtn> '&' '|' '~' '^'			
%token <gtn> '+' '-' '*' '/' '%'		
%token <gtn> '>' '<' '?' '!' '='		
%token <gtn> '(' ')' '[' ']' '{' '}'	

%type <gtn> program primary_expression postfix_expression argument_expression_list unary_expression
%type <gtn> unary_operator cast_expression multiplicative_expression additive_expression shift_expression
%type <gtn> relational_expression equality_expression and_expression exclusive_or_expression inclusive_or_expression
%type <gtn> logical_and_expression logical_or_expression conditional_expression assignment_expression
%type <gtn> assignment_operator expression constant_expression declaration declaration_specifiers init_declarator_list
%type <gtn> init_declarator storage_class_specifier type_specifier struct_or_union_specifier struct_or_union
%type <gtn> struct_declaration_list struct_declaration specifier_qualifier_list struct_declarator_list struct_declarator
%type <gtn> enum_specifier enumerator_list enumerator type_qualifier function_specifier declarator direct_declarator
%type <gtn> pointer type_qualifier_list parameter_type_list parameter_list parameter_declaration identifier_list
%type <gtn> type_name abstract_declarator direct_abstract_declarator initializer initializer_list designation
%type <gtn> designator_list designator statement labeled_statement compound_statement block_item_list block_item
%type <gtn> expression_statement selection_statement iteration_statement jump_statement translation_unit
%type <gtn> external_declaration function_definition declaration_list print_statement
%start program

%union{
    class GrammarTreeNode* gtn;
}

%%

program
    : translation_unit         { $$ = treeCreate("program",1,$1);root = $$;}
	;

primary_expression
	: IDENTIFIER				{$$ = treeCreate("primary_expression",1,$1);}
	| CONSTANT					{$$ = treeCreate("primary_expression",1,$1);}
	| CONSTANT_INT				{$$ = treeCreate("primary_expression",1,$1);}
	| CONSTANT_DOUBLE			{$$ = treeCreate("primary_expression",1,$1);}
	| STRING_LITERAL			{$$ = treeCreate("primary_expression",1,$1);}
	| '(' expression ')'		{$$ = treeCreate("primary_expression",3,$1,$2,$3);}
	;

postfix_expression
	: primary_expression									{$$ = treeCreate("postfix_expression",1,$1);}
	| postfix_expression '[' expression ']'					{$$ = treeCreate("postfix_expression",4,$1,$2,$3,$4);}	
	| IDENTIFIER '(' ')'							{$$ = treeCreate("postfix_expression",3,$1,$2,$3);}
	| IDENTIFIER '(' argument_expression_list ')'	{$$ = treeCreate("postfix_expression",4,$1,$2,$3,$4);}
	| postfix_expression '.' IDENTIFIER						{$$ = treeCreate("postfix_expression",3,$1,$2,$3);}
	| postfix_expression OP_PTR IDENTIFIER					{$$ = treeCreate("postfix_expression",3,$1,$2,$3);}
	| postfix_expression OP_INC								{$$ = treeCreate("postfix_expression",2,$1,$2);}
	| postfix_expression OP_DEC								{$$ = treeCreate("postfix_expression",2,$1,$2);}
	| '(' type_name ')' '{' initializer_list '}'			{$$ = treeCreate("postfix_expression",6,$1,$2,$3,$4,$5,$6);}
	| '(' type_name ')' '{' initializer_list ',' '}'		{$$ = treeCreate("postfix_expression",7,$1,$2,$3,$4,$5,$6,$7);}
	;

argument_expression_list
	: assignment_expression									{$$ = treeCreate("argument_expression_list",1,$1);}
	| argument_expression_list ',' assignment_expression	{$$ = treeCreate("argument_expression_list",3,$1,$2,$3);}
	;

unary_expression
	: postfix_expression				{$$ = treeCreate("unary_expression",1,$1);}
	| OP_INC unary_expression			{$$ = treeCreate("unary_expression",2,$1,$2);}
	| OP_DEC unary_expression			{$$ = treeCreate("unary_expression",2,$1,$2);}
	| unary_operator cast_expression 	{$$ = treeCreate("unary_expression",2,$1,$2);}
	| SIZEOF unary_expression			{$$ = treeCreate("unary_expression",2,$1,$2);}
	| SIZEOF '(' type_name ')'			{$$ = treeCreate("unary_expression",4,$1,$2,$3,$4);}
	;

unary_operator
	: '&'		{$$ = treeCreate("unary_operator",1,$1);}
	| '*'		{$$ = treeCreate("unary_operator",1,$1);}
	| '+'		{$$ = treeCreate("unary_operator",1,$1);}
	| '-'		{$$ = treeCreate("unary_operator",1,$1);}
	| '~'		{$$ = treeCreate("unary_operator",1,$1);}
	| '!'		{$$ = treeCreate("unary_operator",1,$1);}
	;

cast_expression
	: unary_expression								{$$ = treeCreate("cast_expression",1,$1);}
	| '(' type_name ')' cast_expression				{$$ = treeCreate("cast_expression",4,$1,$2,$3,$4);}
	;

multiplicative_expression
	: cast_expression									{$$ = treeCreate("multiplicative_expression",1,$1);}
	| multiplicative_expression '*' cast_expression		{$$ = treeCreate("multiplicative_expression",3,$1,$2,$3);}
	| multiplicative_expression '/' cast_expression		{$$ = treeCreate("multiplicative_expression",3,$1,$2,$3);}
	| multiplicative_expression '%' cast_expression		{$$ = treeCreate("multiplicative_expression",3,$1,$2,$3);}
	;

additive_expression
	: multiplicative_expression								{$$ = treeCreate("additive_expression",1,$1);}
	| additive_expression '+' multiplicative_expression		{$$ = treeCreate("additive_expression",3,$1,$2,$3);}
	| additive_expression '-' multiplicative_expression		{$$ = treeCreate("additive_expression",3,$1,$2,$3);}
	;

shift_expression
	: additive_expression									{$$ = treeCreate("shift_expression",1,$1);}
	| shift_expression OP_LEFTSHIFT additive_expression		{$$ = treeCreate("shift_expression",3,$1,$2,$3);}
	| shift_expression OP_RIGHTSHIFT additive_expression	{$$ = treeCreate("shift_expression",3,$1,$2,$3);}
	;

relational_expression
	: shift_expression									{$$ = treeCreate("relational_expression",1,$1);}
	| relational_expression '<' shift_expression		{$$ = treeCreate("relational_expression",3,$1,$2,$3);}
	| relational_expression '>' shift_expression		{$$ = treeCreate("relational_expression",3,$1,$2,$3);}
	| relational_expression OP_LE shift_expression		{$$ = treeCreate("relational_expression",3,$1,$2,$3);}
	| relational_expression OP_GE shift_expression		{$$ = treeCreate("relational_expression",3,$1,$2,$3);}
	;

equality_expression
	: relational_expression								{$$ = treeCreate("equality_expression",1,$1);}
	| equality_expression OP_EQ relational_expression	{$$ = treeCreate("equality_expression",3,$1,$2,$3);}
	| equality_expression OP_NE relational_expression	{$$ = treeCreate("equality_expression",3,$1,$2,$3);}
	;

and_expression
	: equality_expression							{$$ = treeCreate("and_expression",1,$1);}
	| and_expression '&' equality_expression		{$$ = treeCreate("and_expression",3,$1,$2,$3);}
	;

exclusive_or_expression
	: and_expression								{$$ = treeCreate("exclusive_or_expression",1,$1);}
	| exclusive_or_expression '^' and_expression	{$$ = treeCreate("exclusive_or_expression",3,$1,$2,$3);}
	;

inclusive_or_expression
	: exclusive_or_expression								{$$ = treeCreate("inclusive_or_expression",1,$1);}
	| inclusive_or_expression '|' exclusive_or_expression	{$$ = treeCreate("inclusive_or_expression",3,$1,$2,$3);}
	;

logical_and_expression
	: inclusive_or_expression									{$$ = treeCreate("logical_and_expression",1,$1);}
	| logical_and_expression OP_AND inclusive_or_expression		{$$ = treeCreate("logical_and_expression",3,$1,$2,$3);}
	;

logical_or_expression
	: logical_and_expression								{$$ = treeCreate("logical_or_expression",1,$1);}
	| logical_or_expression OP_OR logical_and_expression	{$$ = treeCreate("logical_or_expression",3,$1,$2,$3);}
	;

conditional_expression
	: logical_or_expression												{$$ = treeCreate("conditional_expression",1,$1);}
	| logical_or_expression '?' conditional_expression ':' conditional_expression	{$$ = treeCreate("conditional_expression",5,$1,$2,$3,$4,$5);}
	;

assignment_expression
	: conditional_expression										{$$ = treeCreate("assignment_expression",1,$1);}
	| unary_expression assignment_operator assignment_expression	{$$ = treeCreate("assignment_expression",3,$1,$2,$3);}
	;

assignment_operator
	: '='					{$$ = treeCreate("assignment_operator",1,$1);}
	| ASSIGN_MUL			{$$ = treeCreate("assignment_operator",1,$1);}
	| ASSIGN_DIV			{$$ = treeCreate("assignment_operator",1,$1);}
	| ASSIGN_MOD			{$$ = treeCreate("assignment_operator",1,$1);}
	| ASSIGN_ADD			{$$ = treeCreate("assignment_operator",1,$1);}
	| ASSIGN_SUB 			{$$ = treeCreate("assignment_operator",1,$1);}
	| ASSIGN_LEFTSHIFT		{$$ = treeCreate("assignment_operator",1,$1);}
	| ASSIGN_RIGHTSHIFT		{$$ = treeCreate("assignment_operator",1,$1);}
	| ASSIGN_AND			{$$ = treeCreate("assignment_operator",1,$1);}
	| ASSIGN_XOR			{$$ = treeCreate("assignment_operator",1,$1);}
	| ASSIGN_OR				{$$ = treeCreate("assignment_operator",1,$1);}
	;

expression
	: assignment_expression						{$$ = treeCreate("expression",1,$1);}
	| expression ',' assignment_expression		{$$ = treeCreate("expression",3,$1,$2,$3);}
	;
 
constant_expression
	: conditional_expression					{$$ = treeCreate("constant_expression",1,$1);}
	;

declaration
	: declaration_specifiers ';'							{$$ = treeCreate("declaration",2,$1,$2);}
	| declaration_specifiers init_declarator_list ';'		{$$ = treeCreate("declaration",3,$1,$2,$3);}
	;

declaration_specifiers
	: storage_class_specifier								{$$ = treeCreate("declaration_specifiers",1,$1);}
	| storage_class_specifier declaration_specifiers		{$$ = treeCreate("declaration_specifiers",2,$1,$2);}
	| type_specifier										{$$ = treeCreate("declaration_specifiers",1,$1);}
	| type_specifier declaration_specifiers					{$$ = treeCreate("declaration_specifiers",2,$1,$2);}
	| type_qualifier										{$$ = treeCreate("declaration_specifiers",1,$1);}
	| type_qualifier declaration_specifiers					{$$ = treeCreate("declaration_specifiers",2,$1,$2);}
	| function_specifier									{$$ = treeCreate("declaration_specifiers",1,$1);}
	| function_specifier declaration_specifiers				{$$ = treeCreate("declaration_specifiers",2,$1,$2);}
	;

init_declarator_list
	: init_declarator										{$$ = treeCreate("init_declarator_list",1,$1);}
	| init_declarator_list ',' init_declarator				{$$ = treeCreate("init_declarator_list",3,$1,$2,$3);}
	;

init_declarator
	: declarator											{$$ = treeCreate("init_declarator",1,$1);}
	| declarator '=' initializer							{$$ = treeCreate("init_declarator",3,$1,$2,$3);}
	;

storage_class_specifier
	: TYPEDEF				{$$ = treeCreate("storage_class_specifier",1,$1);}
	| EXTERN				{$$ = treeCreate("storage_class_specifier",1,$1);}
	| STATIC				{$$ = treeCreate("storage_class_specifier",1,$1);}
	| AUTO					{$$ = treeCreate("storage_class_specifier",1,$1);}
	// | REGISTER				{$$ = treeCreate("storage_class_specifier",1,$1);}
	;	

type_specifier
	: VOID								{$$ = treeCreate("type_specifier",1,$1);}
	| CHAR								{$$ = treeCreate("type_specifier",1,$1);}
	| SHORT								{$$ = treeCreate("type_specifier",1,$1);}
	| INT								{$$ = treeCreate("type_specifier",1,$1);}
	| LONG								{$$ = treeCreate("type_specifier",1,$1);}
	| FLOAT								{$$ = treeCreate("type_specifier",1,$1);}
	| DOUBLE								{$$ = treeCreate("type_specifier",1,$1);}
	| SIGNED							{$$ = treeCreate("type_specifier",1,$1);}
	| UNSIGNED							{$$ = treeCreate("type_specifier",1,$1);}
	| BOOL								{$$ = treeCreate("type_specifier",1,$1);}
	// | COMPLEX							{$$ = treeCreate("type_specifier",1,$1);}
	// | IMAGINARY							{$$ = treeCreate("type_specifier",1,$1);}
	| struct_or_union_specifier			{$$ = treeCreate("type_specifier",1,$1);}
	| enum_specifier					{$$ = treeCreate("type_specifier",1,$1);}
	// | TYPE_NAME							{$$ = treeCreate("type_specifier",1,$1);}
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'	{$$ = treeCreate("struct_or_union_specifier",5,$1,$2,$3,$4,$5);}
	| struct_or_union '{' struct_declaration_list '}'				{$$ = treeCreate("struct_or_union_specifier",4,$1,$2,$3,$4);}
	| struct_or_union IDENTIFIER									{$$ = treeCreate("struct_or_union_specifier",2,$1,$2);}
	;

struct_or_union
	: STRUCT										{$$ = treeCreate("struct_or_union",1,$1);}
	| UNION											{$$ = treeCreate("struct_or_union",1,$1);}
	;		

struct_declaration_list
	: struct_declaration							{$$ = treeCreate("struct_declarator_list",1,$1);}
	| struct_declaration_list struct_declaration	{$$ = treeCreate("struct_declarator_list",2,$1,$2);}
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'	{$$ = treeCreate("struct_declaration",3,$1,$2,$3);}
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list		{$$ = treeCreate("specifier_qualifier_list",2,$1,$2);}
	| type_specifier								{$$ = treeCreate("specifier_qualifier_list",1,$1);}
	| type_qualifier specifier_qualifier_list		{$$ = treeCreate("specifier_qualifier_list",2,$1,$2);}
	| type_qualifier								{$$ = treeCreate("specifier_qualifier_list",1,$1);}
	;

struct_declarator_list
	: struct_declarator								{$$ = treeCreate("struct_declarator_list",1,$1);}
	| struct_declarator_list ',' struct_declarator	{$$ = treeCreate("struct_declarator_list",3,$1,$2,$3);}
	;

struct_declarator
	: declarator									{$$ = treeCreate("struct_declarator",1,$1);}
	| ':' constant_expression						{$$ = treeCreate("struct_declarator",2,$1,$2);}
	| declarator ':' constant_expression			{$$ = treeCreate("struct_declarator",3,$1,$2,$3);}
	;

enum_specifier
	: ENUM '{' enumerator_list '}'					{$$ = treeCreate("enum_specifier",4,$1,$2,$3,$4);}
	| ENUM IDENTIFIER '{' enumerator_list '}'		{$$ = treeCreate("enum_specifier",5,$1,$2,$3,$4,$5);}
	| ENUM '{' enumerator_list ',' '}'				{$$ = treeCreate("enum_specifier",5,$1,$2,$3,$4,$5);}
	| ENUM IDENTIFIER '{' enumerator_list ',' '}'	{$$ = treeCreate("enum_specifier",6,$1,$2,$3,$4,$5,$6);}
	| ENUM IDENTIFIER								{$$ = treeCreate("enum_specifier",2,$1,$2);}
	;

enumerator_list
	: enumerator									{$$ = treeCreate("enumerator_list",1,$1);}
	| enumerator_list ',' enumerator				{$$ = treeCreate("enumerator_list",3,$1,$2,$3);}
	;

enumerator
	: IDENTIFIER									{$$ = treeCreate("enumerator",1,$1);}
	| IDENTIFIER '=' constant_expression			{$$ = treeCreate("enumerator",3,$1,$2,$3);}
	;

type_qualifier
	: CONST											{$$ = treeCreate("type_qualifier",1,$1);}
	// | RESTRICT										{$$ = treeCreate("type_qualifier",1,$1);}
	| VOLATILE										{$$ = treeCreate("type_qualifier",1,$1);}
	;

function_specifier
	: INLINE						{$$ = treeCreate("function_specifier",1,$1);}
	;

declarator
	: pointer direct_declarator		{$$ = treeCreate("declarator",2,$1,$2);}
	| direct_declarator				{$$ = treeCreate("declarator",1,$1);}
	;

direct_declarator
	: IDENTIFIER					{$$ = treeCreate("direct_declarator",1,$1);}
	| '(' declarator ')'			{$$ = treeCreate("direct_declarator",3,$1,$2,$3);}
	| direct_declarator '[' type_qualifier_list assignment_expression ']'   {$$ = treeCreate("direct_declarator",5,$1,$2,$3,$4,$5);}
	| direct_declarator '[' type_qualifier_list ']'							{$$ = treeCreate("direct_declarator",4,$1,$2,$3,$4);}
	| direct_declarator '[' assignment_expression ']'						{$$ = treeCreate("direct_declarator",4,$1,$2,$3,$4);}
	| direct_declarator '[' STATIC type_qualifier_list assignment_expression ']' {$$ = treeCreate("direct_declarator",6,$1,$2,$3,$4,$5,$6);}
	| direct_declarator '[' type_qualifier_list STATIC assignment_expression ']' {$$ = treeCreate("direct_declarator",6,$1,$2,$3,$4,$5,$6);}
	| direct_declarator '[' type_qualifier_list '*' ']'						{$$ = treeCreate("direct_declarator",5,$1,$2,$3,$4,$5);}
	| direct_declarator '[' '*' ']'											{$$ = treeCreate("direct_declarator",4,$1,$2,$3,$4);}
	| direct_declarator '[' ']'												{$$ = treeCreate("direct_declarator",3,$1,$2,$3);}
	| direct_declarator '(' parameter_type_list ')'							{$$ = treeCreate("direct_declarator",4,$1,$2,$3,$4);}
	| direct_declarator '(' identifier_list ')'								{$$ = treeCreate("direct_declarator",4,$1,$2,$3,$4);}
	| direct_declarator '(' ')'												{$$ = treeCreate("direct_declarator",3,$1,$2,$3);}
	;

pointer
	: '*'										{$$ = treeCreate("pointer",1,$1);}
	| '*' type_qualifier_list					{$$ = treeCreate("pointer",2,$1,$2);}
	| '*' pointer								{$$ = treeCreate("pointer",2,$1,$2);}
	| '*' type_qualifier_list pointer			{$$ = treeCreate("pointer",3,$1,$2,$3);}
	;

type_qualifier_list
	: type_qualifier							{$$ = treeCreate("type_qualifier_list",1,$1);}
	| type_qualifier_list type_qualifier		{$$ = treeCreate("type_qualifier_list",2,$2);}
	;


parameter_type_list
	: parameter_list							{$$ = treeCreate("parameter_type_list",1,$1);}
	| parameter_list ',' ELLIPSIS				{$$ = treeCreate("parameter_type_list",3,$1,$2,$3);}
	;

parameter_list
	: parameter_declaration						{$$ = treeCreate("parameter_list",1,$1);}
	| parameter_list ',' parameter_declaration	{$$ = treeCreate("parameter_list",3,$1,$2,$3);}
	;

parameter_declaration
	: declaration_specifiers declarator				{$$ = treeCreate("parameter_declaration",2,$1,$2);}	
	| declaration_specifiers abstract_declarator	{$$ = treeCreate("parameter_declaration",2,$1,$2);}
	| declaration_specifiers						{$$ = treeCreate("parameter_declaration",1,$1);}
	;

identifier_list
	: IDENTIFIER						{$$ = treeCreate("identifier_list",1,$1);}
	| identifier_list ',' IDENTIFIER	{$$ = treeCreate("identifier_list",3,$1,$2,$3);}
	;

type_name
	: specifier_qualifier_list						{$$ = treeCreate("type_name",1,$1);}
	| specifier_qualifier_list abstract_declarator	{$$ = treeCreate("type_name",2,$1,$2);}
	;

abstract_declarator
	: pointer								{$$ = treeCreate("abstract_declarator",1,$1);}
	| direct_abstract_declarator			{$$ = treeCreate("abstract_declarator",1,$1);}
	| pointer direct_abstract_declarator	{$$ = treeCreate("abstract_declarator",2,$1,$2);}
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'			
	| '[' ']'
	| '[' assignment_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' assignment_expression ']'
	| '[' '*' ']'
	| direct_abstract_declarator '[' '*' ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer
	: assignment_expression				{$$ = treeCreate("initializer",1,$1);}
	| '{' initializer_list '}'			{$$ = treeCreate("initializer",3,$1,$2,$3);}
	| '{' initializer_list ',' '}'		{$$ = treeCreate("initializer",4,$1,$2,$3,$4);}
	;

initializer_list		
	: initializer									{$$ = treeCreate("initializer_list",1,$1);}
	| designation initializer						{$$ = treeCreate("initializer_list",2,$1,$2);}
	| initializer_list ',' initializer				{$$ = treeCreate("initializer_list",3,$1,$2,$3);}
	| initializer_list ',' designation initializer	{$$ = treeCreate("initializer_list",4,$1,$2,$3,$4);}
	;

designation
	: designator_list '='				{$$ = treeCreate("designation",2,$1,$2);}
	;

designator_list
	: designator						{$$ = treeCreate("designator_list",1,$1);}
	| designator_list designator		{$$ = treeCreate("designator_list",2,$1,$2);}
	;

designator
	: '[' constant_expression ']'		{$$ = treeCreate("designator",3,$1,$2,$3);}
	| '.' IDENTIFIER					{$$ = treeCreate("designator",2,$1,$2);}
	;

statement
	: labeled_statement					{$$ = treeCreate("statement",1,$1);}
	| compound_statement				{$$ = treeCreate("statement",1,$1);}
	| expression_statement				{$$ = treeCreate("statement",1,$1);}
	| selection_statement				{$$ = treeCreate("statement",1,$1);}
	| iteration_statement				{$$ = treeCreate("statement",1,$1);}
	| jump_statement					{$$ = treeCreate("statement",1,$1);}
	| print_statement  					{$$ = treeCreate("statement",1,$1);}
	;
	
print_statement
	: println '(' STRING_LITERAL ',' expression ')'';' {$$ = treeCreate("print_statement",7,$1,$2,$3,$4,$5,$6,$7);}
	;

labeled_statement								
	: IDENTIFIER ':' statement					{$$ = treeCreate("labeled_statement",3,$1,$2,$3);}
	| CASE constant_expression ':' statement	{$$ = treeCreate("labeled_statement",4,$1,$2,$3,$4);}
	| DEFAULT ':' statement						{$$ = treeCreate("labeled_statement",3,$1,$2,$3);}
	;

compound_statement
	: '{' '}'							{$$ = treeCreate("compound_statement",2,$1,$2);}
	| '{' block_item_list '}'			{$$ = treeCreate("compound_statement",3,$1,$2,$3);}
	;

block_item_list
	: block_item					{$$ = treeCreate("block_item_list",1,$1);}
	| block_item_list block_item	{$$ = treeCreate("block_item_list",2,$1,$2);}
	;

block_item
	: declaration					{$$ = treeCreate("block_item",1,$1);}
	| statement			 			{$$ = treeCreate("block_item",1,$1);}
	;

expression_statement
	: ';'							{$$ = treeCreate("expression_statement",1,$1);}
	| expression ';'				{$$ = treeCreate("expression_statement",2,$1,$2);}
	;

selection_statement
	: IF '(' equality_expression ')' statement					{$$ = treeCreate("selection_statement",5,$1,$2,$3,$4,$5);}
	| IF '(' equality_expression ')' statement ELSE statement	{$$ = treeCreate("selection_statement",7,$1,$2,$3,$4,$5,$6,$7);}
	| SWITCH '(' equality_expression ')' statement				{$$ = treeCreate("selection_statement",5,$1,$2,$3,$4,$5);}
	;

iteration_statement
	: WHILE '(' expression ')' statement				{$$ = treeCreate("iteration_statement",5,$1,$2,$3,$4,$5);}
	| DO statement WHILE '(' expression ')' ';'			{$$ = treeCreate("iteration_statement",7,$1,$2,$3,$4,$5,$6,$7);}
	| FOR '(' expression_statement expression_statement ')' statement				{$$ = treeCreate("iteration_statement",6,$1,$2,$3,$4,$5,$6);}
	| FOR '(' expression_statement expression_statement expression ')' statement	{$$ = treeCreate("iteration_statement",7,$1,$2,$3,$4,$5,$6,$7);}
	| FOR '(' declaration expression_statement ')' statement						{$$ = treeCreate("iteration_statement",6,$1,$2,$3,$4,$5,$6);}
	| FOR '(' declaration expression_statement expression ')' statement				{$$ = treeCreate("iteration_statement",7,$1,$2,$3,$4,$5,$6,$7);}
	;

jump_statement
	: GOTO IDENTIFIER ';'			{$$ = treeCreate("jump_statement",3,$1,$2,$3);}
	| CONTINUE ';'					{$$ = treeCreate("jump_statement",2,$1,$2);}
	| BREAK ';'						{$$ = treeCreate("jump_statement",2,$1,$2);}
	| RETURN ';'					{$$ = treeCreate("jump_statement",2,$1,$2);}
	| RETURN expression ';'			{$$ = treeCreate("jump_statement",3,$1,$2,$3);}
	;

translation_unit
	: external_declaration   					 {$$ = treeCreate("translation_unit",1,$1);}
	| translation_unit external_declaration 	 {$$ = treeCreate("translation_unit",2,$1,$2);}
	;

external_declaration
	: function_definition	{$$ = treeCreate("external_declaration",1,$1);}
	| declaration	        {$$ = treeCreate("external_declaration",1,$1);}
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement		{$$ = treeCreate("function_definition",4,$1,$2,$3,$4);}
	| declaration_specifiers declarator compound_statement						{$$ = treeCreate("function_definition",3,$1,$2,$3);}
	;

declaration_list
	: declaration						{$$ = treeCreate("declaration_list",1,$1);}
	| declaration_list declaration		{$$ = treeCreate("declaration_list",2,$1,$2);}
	;


%%

void yyerror(char const *s){
	fflush(stdout);
	printf("\n%*s\n%*s\n", col, "^", col, s);
}



int main(int argc, char* argv[]){
    if(argc>1){
        yyin=fopen(argv[1],"r");
    }else{
        yyin=stdin;
    }
    yyparse();
    printf("\n");
    treePrint(root,0);
	// printtree(root);
    
	gen(root,argv[1]);

	string cmd = "llc ";
	cmd+=argv[1];
	cmd+=".ll -o ";
	cmd+=argv[1];
	cmd+=".s & clang ";
	cmd+=argv[1];
	cmd+=".s -o ";
	cmd+=argv[1];
	cmd+=".out ";
	// string cmd = "llc "+argv[1]+" -o "+ argv[1]+".s & gcc "+argv[1]+".s -o "+argv[1]+".out"
	system(cmd.c_str());

    // treeNodeFree(root);

    fclose(yyin);

    return 0;
}
