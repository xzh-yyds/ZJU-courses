#pragma once
#ifndef GRAMMARTREE_H
#define GRAMMARTREE_H
#include <iostream>
#include <string>
#include <cstdarg>
#include <cstring>
#include "stdarg.h"
#include <stdlib.h>
#include <stdio.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/CommandLine.h>

extern char *yytext;
extern int yylineno;
using namespace std; 	
using namespace llvm;

string int2string(int a); 

class GrammarTreeNode
{
public:
	// static Module *module;
	static LLVMContext MyGlobalContext;
	static IRBuilder<> Builder(LLVMContext);
	// static std::map<std::string, Value*> NamedValues;
	std::string content;
	std::string name;
	int line_no,intval;
	double douval;
	float floval;
	string vtype;
	bool booval;
	GrammarTreeNode *left;
	GrammarTreeNode *right;
	GrammarTreeNode()
	{
		left = NULL;
		right = NULL;
		content = "";
		name = "";
		line_no = -1;
		vtype = "int";
	};
	GrammarTreeNode(string nname, int t, int lineNO)
	{
		this->name = nname;
		this->line_no = lineNO;

		if (this->name == "CONSTANT_INT")
		{
			int int_value;

			if (strlen(yytext) > 1 && yytext[0] == 0 && yytext[1] != 'x')
			{
				sscanf(yytext, "%o", &int_value);
			}
			else if (strlen(yytext) > 1 && yytext[0] == 0 && yytext[1] == 'x')
			{
				sscanf(yytext, "%x", &int_value);
			}
			else
			{
				int_value = atoi(yytext);
			}
			this->content = int2string(int_value);
			// this->content = "12";
			this->intval = int_value;
			// std::cout<<this->content<<std::endl;
		}
		else if (this->name == "CONSTANT_DOUBLE")
		{
			this->content = yytext;
			char* pend;
			this->douval = strtod(yytext,&pend);
			this->vtype = "double";

		}
		else if (this->name == "TRUE")
		{
			this->content = int2string(1);
			this->booval = true;
		}
		else if (this->name == "FALSE")
		{
			this->content = int2string(0);
			this->booval = false;
		}
		else if (this->name == "STRING_LITERAL")
		{
			this->content = yytext;
		}
		else
		{
			this->content = yytext;
		}
	};

	// Value *ValueCodegen(){
	// 	return ConstantFP::get(MyGlobalContext,APFloat(this->douval));
	// };

	// Function* FuncCodegen(){
	// 	return nullptr;
	// };



	// void genllvmir(){
	// 	module->print(outs(),nullptr);
	// };

};

// GrammarTreeNode *treeCreate(std::string name, int num, ...);
void treeNodeFree(GrammarTreeNode *node);
void treePrint(GrammarTreeNode *node, int level);
#endif