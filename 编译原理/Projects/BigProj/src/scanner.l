%{
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstdio>
#include "parser.hpp"
#include "grammartree.h"
#define YYSTYPE GrammarTreeNode*

void col_count();
void mutiline_comment();
void singleline_comment();


int typeCheck();
void unmatch();
int col;
const int tab_size=4;
%}

%option yylineno

D		[0-9]
L		[a-zA-Z]
H		[a-fA-F0-9]
E		([Ee][+-]?{D}+)
P		([Pp][+-]?{D}+)
FS		(f|F|l|L)
IS		((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))

%%
"/*"			{ mutiline_comment(); }
"//"[^\n]*      { singleline_comment(); }

"println"	    {   col_count();
					yylval.gtn=new GrammarTreeNode("println",0,yylineno);
					return(println);}

"auto"			{	col_count(); 
					yylval.gtn=new GrammarTreeNode("AUTO",0,yylineno);
					return(AUTO);	}
"sizeof"		{ 	col_count();
					yylval.gtn=new GrammarTreeNode("SIZEOF",0,yylineno);
					return(SIZEOF); }
"goto"			{	col_count();
					yylval.gtn=new GrammarTreeNode("GOTO",0,yylineno);
					return(GOTO); }
"return"		{	col_count(); 
					yylval.gtn=new GrammarTreeNode("RETURN",0,yylineno);
					return(RETURN); }

"do"			{	col_count();
					yylval.gtn=new GrammarTreeNode("DO",0,yylineno);
					return(DO); }
"while"			{	col_count();
					yylval.gtn=new GrammarTreeNode("WHILE",0,yylineno);
					return(WHILE); }
"for"			{	col_count();
					yylval.gtn=new GrammarTreeNode("FOR",0,yylineno);
					return(FOR); }
"continue"		{	col_count();
					yylval.gtn=new GrammarTreeNode("CONTINUE",0,yylineno);
					return(CONTINUE); }
"break"			{	col_count();
					yylval.gtn=new GrammarTreeNode("BREAK",0,yylineno);
					return(BREAK); }
"switch"		{	col_count();
					yylval.gtn=new GrammarTreeNode("SWITCH",0,yylineno);
					return(SWITCH); }
"default"		{	col_count();
					yylval.gtn=new GrammarTreeNode("DEFAULT",0,yylineno);
					return(DEFAULT); }
"case"			{	col_count();
					yylval.gtn=new GrammarTreeNode("CASE",0,yylineno);
					return(CASE); }
"if"			{	col_count();
					yylval.gtn=new GrammarTreeNode("IF",0,yylineno);
					return(IF); }
"else"			{	col_count();
					yylval.gtn=new GrammarTreeNode("ELSE",0,yylineno);
					return(ELSE); }

"float"			{	col_count();
					yylval.gtn=new GrammarTreeNode("FLOAT",0,yylineno);
					return(FLOAT); }
"double"		{	col_count();
					yylval.gtn=new GrammarTreeNode("DOUBLE",0,yylineno);
					return(DOUBLE); }
"char"			{	col_count();
					yylval.gtn=new GrammarTreeNode("CHAR",0,yylineno);
					return(CHAR); }
"void"			{	col_count(); 
					yylval.gtn=new GrammarTreeNode("VOID",0,yylineno);
					return(VOID); }
"int"			{	col_count();
					yylval.gtn=new GrammarTreeNode("INT",0,yylineno);
					return(INT); }
"long"			{	col_count();
					yylval.gtn=new GrammarTreeNode("LONG",0,yylineno);
					return(LONG); }
"bool"			{	col_count();
					yylval.gtn=new GrammarTreeNode("BOOL",0,yylineno);
					return(BOOL); }
"const"			{	col_count();
					yylval.gtn=new GrammarTreeNode("CONST",0,yylineno);
					return(CONST); }
"short"			{	col_count();
					yylval.gtn=new GrammarTreeNode("SHORT",0,yylineno);
					return(SHORT); }
"signed"		{	col_count();
					yylval.gtn=new GrammarTreeNode("SIGNED",0,yylineno);
					return(SIGNED); }
"unsigned"		{	col_count();
					yylval.gtn=new GrammarTreeNode("UNSIGNED",0,yylineno);
					return(UNSIGNED); }

"static"		{	col_count();
					yylval.gtn=new GrammarTreeNode("STATIC",0,yylineno);
					return(STATIC); }
"extern"		{	col_count();
					yylval.gtn=new GrammarTreeNode("EXTERN",0,yylineno);
					return(EXTERN); }
"inline"		{	col_count();
					yylval.gtn=new GrammarTreeNode("INLINE",0,yylineno);
					return(INLINE); }
"typedef"		{	col_count();
					yylval.gtn=new GrammarTreeNode("TYPEDEF",0,yylineno);
					return(TYPEDEF); }
"struct"		{	col_count();
					yylval.gtn=new GrammarTreeNode("STRUCT",0,yylineno);
					return(STRUCT); }
"enum"			{	col_count();
					yylval.gtn=new GrammarTreeNode("ENUM",0,yylineno);
					return(ENUM); }
"union"			{	col_count();
					yylval.gtn=new GrammarTreeNode("UNION",0,yylineno);
					return(UNION); }

{L}({L}|{D})*		{	col_count();
						yylval.gtn=new GrammarTreeNode("IDENTIFIER",0,yylineno);
						return(typeCheck()); }

0[xX]{H}+{IS}?		{	col_count();
						yylval.gtn=new GrammarTreeNode("CONSTANT_INT",0,yylineno);
						return(CONSTANT_INT); }
0[0-7]*{IS}?		{	col_count();
						yylval.gtn=new GrammarTreeNode("CONSTANT_INT",0,yylineno);
						return(CONSTANT_INT); }
[1-9]{D}*{IS}?		{	col_count(); 
						yylval.gtn=new GrammarTreeNode("CONSTANT_INT",0,yylineno);
						return(CONSTANT_INT); }
L?'(\\.|[^\\'\n])+'	{	col_count(); return(CONSTANT); }

{D}+{E}{FS}?			{	col_count();
							yylval.gtn=new GrammarTreeNode("CONSTANT_DOUBLE",0,yylineno);
							return(CONSTANT_DOUBLE); }
{D}*"."{D}+{E}?{FS}?	{	col_count();
							yylval.gtn=new GrammarTreeNode("CONSTANT_DOUBLE",0,yylineno);
							return(CONSTANT_DOUBLE); }
{D}+"."{D}*{E}?{FS}?	{	col_count();
							yylval.gtn=new GrammarTreeNode("CONSTANT_DOUBLE",0,yylineno);
							return(CONSTANT_DOUBLE); }
0[xX]{H}+{P}{FS}?			{	col_count(); return(CONSTANT); }
0[xX]{H}*"."{H}+{P}{FS}?    {	col_count(); return(CONSTANT); }
0[xX]{H}+"."{H}*{P}{FS}?    {	col_count(); return(CONSTANT); }

L?\"(\\.|[^\\"\n])*\"	{ 	col_count();
							yylval.gtn=new GrammarTreeNode("STRING_LITERAL",0,yylineno);
							return(STRING_LITERAL); }

"..."		{	col_count();
				yylval.gtn=new GrammarTreeNode("ELLIPSIS",0,yylineno);
				return(ELLIPSIS); }
">>="		{	col_count();
				yylval.gtn=new GrammarTreeNode("ASSIGN_RIGHTSHIFT",0,yylineno);
				return(ASSIGN_RIGHTSHIFT); }
"<<="		{	col_count();
				yylval.gtn=new GrammarTreeNode("ASSIGN_LEFTSHIFT",0,yylineno);
				return(ASSIGN_LEFTSHIFT); }
"+="		{	col_count();
				yylval.gtn=new GrammarTreeNode("ASSIGN_ADD",0,yylineno);
				return(ASSIGN_ADD); }
"-="		{	col_count();
				yylval.gtn=new GrammarTreeNode("ASSIGN_SUB",0,yylineno);
				return(ASSIGN_SUB); }
"*="		{	col_count();
				yylval.gtn=new GrammarTreeNode("ASSIGN_MUL",0,yylineno);
				return(ASSIGN_MUL); }
"/="		{	col_count();
				yylval.gtn=new GrammarTreeNode("ASSIGN_DIV",0,yylineno);
				return(ASSIGN_DIV); }
"%="		{	col_count();
				yylval.gtn=new GrammarTreeNode("ASSIGN_MOD",0,yylineno);
				return(ASSIGN_MOD); }
"&="		{	col_count();
				yylval.gtn=new GrammarTreeNode("ASSIGN_AND",0,yylineno);
				return(ASSIGN_AND); }
"^="		{	col_count();
				yylval.gtn=new GrammarTreeNode("ASSIGN_XOR",0,yylineno);
				return(ASSIGN_XOR); }
"|="		{	col_count();
				yylval.gtn=new GrammarTreeNode("ASSIGN_OR",0,yylineno);
				return(ASSIGN_OR); }
">>"		{	col_count();
				yylval.gtn=new GrammarTreeNode("OP_RIGHTSHIFT",0,yylineno);
				return(OP_RIGHTSHIFT); }
"<<"		{	col_count();
				yylval.gtn=new GrammarTreeNode("OP_LEFTSHIFT",0,yylineno);
				return(OP_LEFTSHIFT); }
"++"		{	col_count();
				yylval.gtn=new GrammarTreeNode("OP_INC",0,yylineno);
				return(OP_INC); }
"--"		{	col_count();
				yylval.gtn=new GrammarTreeNode("OP_DEC",0,yylineno);
				return(OP_DEC); }
"->"		{	col_count();
				yylval.gtn=new GrammarTreeNode("OP_PTR",0,yylineno);
				return(OP_PTR); }
"&&"		{	col_count();
				yylval.gtn=new GrammarTreeNode("OP_AND",0,yylineno);
				return(OP_AND); }
"||"		{	col_count();
				yylval.gtn=new GrammarTreeNode("OP_OR",0,yylineno);
				return(OP_OR); }
"<="		{	col_count();
				yylval.gtn=new GrammarTreeNode("OP_LE",0,yylineno);
				return(OP_LE); }
">="		{	col_count();
				yylval.gtn=new GrammarTreeNode("OP_GE",0,yylineno);
				return(OP_GE); }
"=="		{	col_count();
				yylval.gtn=new GrammarTreeNode("OP_EQ",0,yylineno);
				return(OP_EQ); }
"!="		{	col_count();
				yylval.gtn=new GrammarTreeNode("OP_NE",0,yylineno);
				return(OP_NE); }

";"			{	col_count();
				yylval.gtn=new GrammarTreeNode(";",0,yylineno);
				return(';'); }
","			{	col_count();
				yylval.gtn=new GrammarTreeNode(",",0,yylineno);
				return(','); }
":"			{	col_count();
				yylval.gtn=new GrammarTreeNode(":",0,yylineno);
				return(':'); }
"="			{	col_count();
				yylval.gtn=new GrammarTreeNode("=",0,yylineno);
				return('='); }
"."			{	col_count();
				yylval.gtn=new GrammarTreeNode(".",0,yylineno);
				return('.'); }
"&"			{	col_count();
				yylval.gtn=new GrammarTreeNode("&",0,yylineno);
				return('&'); }
"!"			{	col_count();
				yylval.gtn=new GrammarTreeNode("!",0,yylineno);
				return('!'); }
"~"			{	col_count();
				yylval.gtn=new GrammarTreeNode("~",0,yylineno);
				return('~'); }
"-"			{	col_count();
				yylval.gtn=new GrammarTreeNode("-",0,yylineno);
				return('-'); }
"+"			{	col_count();
				yylval.gtn=new GrammarTreeNode("+",0,yylineno);
				return('+'); }
"*"			{	col_count();
				yylval.gtn=new GrammarTreeNode("*",0,yylineno);
				return('*'); }
"/"			{	col_count();
				yylval.gtn=new GrammarTreeNode("/",0,yylineno);
				return('/'); }
"%"			{	col_count();
				yylval.gtn=new GrammarTreeNode("%",0,yylineno);
				return('%'); }
"<"			{	col_count();
				yylval.gtn=new GrammarTreeNode("<",0,yylineno);
				return('<'); }
">"			{	col_count();
				yylval.gtn=new GrammarTreeNode(">",0,yylineno);
				return('>'); }
"^"			{	col_count();
				yylval.gtn=new GrammarTreeNode("^",0,yylineno);	
				return('^'); }
"|"			{	col_count();
				yylval.gtn=new GrammarTreeNode("|",0,yylineno);
				return('|'); }
"?"			{	col_count();
				yylval.gtn=new GrammarTreeNode("?",0,yylineno);
				return('?'); }
"("			{	col_count();
				yylval.gtn=new GrammarTreeNode("(",0,yylineno);
				return('('); }
")"			{	col_count();
				yylval.gtn=new GrammarTreeNode(")",0,yylineno);
				return(')'); }
"["			{	col_count();
				yylval.gtn=new GrammarTreeNode("[",0,yylineno);
				return('['); }
"]"			{	col_count();
				yylval.gtn=new GrammarTreeNode("]",0,yylineno);
				return(']'); }
"{"			{	col_count();
				yylval.gtn=new GrammarTreeNode("{",0,yylineno);
				return('{'); }
"}"			{	col_count();
				yylval.gtn=new GrammarTreeNode("}",0,yylineno);
				return('}'); }


[\t\v\n\f]	{ 	col_count();}
.			{ 	unmatch();	}

%%

int yywrap(){
	return 1;
}

// void yyerror(const char* msg) {
//     printf("%s,%s,Line %d", yytext, msg, yylineno);
// }

void mutiline_comment(){
	col=0;
	char c, prv=0;
	while(cin>>c){
		if(c=='/' && prv=='*'){
			return;
		}
		prv=c;
	}
	printf("unterminated comment\n");
}

void singleline_comment(){

}

void col_count(){
	for(int i=0;yytext[i]!='\0';i++){
		if(yytext[i]=='\n'){
			col=0;
		}else if(yytext[i]=='\t'){
			col+=tab_size-(col%tab_size);
		}else{
			col++;
		}
	}
	// ECHO;
}

int typeCheck(){
	return IDENTIFIER;
}

void unmatch(){

}