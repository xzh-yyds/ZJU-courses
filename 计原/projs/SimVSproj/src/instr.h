#ifndef INSTR_H
#define INSTR_H

#include <vector>
#include <string>
#include <map>

using namespace std;

extern map<int,string> regName;
extern map<string,int> regIndex;

class Instr{
public:
    string all;
    vector<string> args;
public:
    Instr();
    ~Instr();
    Instr(int bin);
    Instr(string s);
    int toBin();
};


string prepare(string s);

vector<string> strSplit(string s,char c);

string strInBrackets(string s);

vector<Instr> MultiTranslate(vector<string> codes);

vector<int> Instrs2Bin32s(vector<Instr> irs);

string reasmC(int code);
string reasmJ(int code);
string reasmR(int code);
string reasm(int code);

int translate(vector<string> opm);
int funcNum(string op);
int translateR(int op, vector<string> instr);
int translateI(int op, vector<string> instr);
int translateJ(int op, vector<string> instr);
int translateC(int op, vector<string> instr);

int isRIJC(string op);
int opcode(string op);


#endif