%{
#include<stdio.h>
#include<string.h>
int char_cnt=0;
int word_cnt=0;
int line_cnt=0;
%}
letter [A-Za-z]
digit [0-9]
word ({letter}|{digit})+
line \n
%%
{word} {
	word_cnt++;
	char_cnt+=strlen(yytext);
}
{line} {
	line_cnt++;
	char_cnt++;
}
. {char_cnt++;}
%%
int main(int argc, char **argv){
	argv++;
	argc--;
	if(argc>0){
		yyin=fopen(argv[0],"r");
	}else{
		yyin=stdin;
	}
	yylex();
	printf("line_cnt:%d\n",line_cnt+1);
	printf("word_cnt:%d\n",word_cnt);
	printf("char_cnt:%d\n",char_cnt);
	return 0;
}
int yywrap(){
	return 1;
}
