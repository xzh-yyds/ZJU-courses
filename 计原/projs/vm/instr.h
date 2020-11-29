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

int RIJC(string op);

vector<Instr> MultiTranslate(vector<string> codes);

string reasmC(int code);
string reasmJ(int code);
string reasmR(int code);
string reasm(int code);

int translate(vector<string> opm);

#endif