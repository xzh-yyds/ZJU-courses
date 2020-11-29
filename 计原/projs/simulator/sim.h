#ifndef _SIM_H
#define _SIM_H

#include<iostream>
#include<vector>
#include<string>
#include<map>
using namespace std;

vector<string> strSplit(string s,char c);
string prepare(string s);


class Instruction{
private:
public:
	string all;
	vector<string> opms;

	Instruction(string instr);
	Instruction();
	~Instruction();
};

struct Label{
    string name;
    int lineNum;
};

void scan();

int regIndex(string regName);

string strInBrackets(string s);

int RIJC(string op);
void execute(Instruction instr);
void executeR1(Instruction instr);
void executeR2(Instruction instr);
void executeR3(Instruction instr);
void executeI1(Instruction instr);
void executeI2(Instruction instr);
void executeJ(Instruction instr);
void executeC(Instruction instr);

void initial();

void load(vector<Instruction> instrs);

int funcNum(string op);
int str2num(string s);
int translateR(int op, vector<string> instr);
int translateI(int op, vector<string> instr);
int translateJ(int op, vector<string> instr);
int translateC(int op, vector<string> instr);
int isRIJC(string op);
int opcode(string op);
int translate(string instr);

#endif