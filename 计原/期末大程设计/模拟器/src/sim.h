#ifndef SIM_H
#define SIM_H

#include <cstring>
#include <iostream>
#include "instr.h"

#define MEM_SIZE 1024
#define REG_NUM 32

#define CMD_LDINS 0
#define CMD_RUN 1
#define CMD_STEP 2
#define CMD_STATUS 3
#define CMD_AGAIN 4
#define CMD_EXIT 5

#define RIJC_R1 0
#define RIJC_R2 1
#define RIJC_R3 2
#define RIJC_I1 3
#define RIJC_I2 4
#define RIJC_I3 5
#define RIJC_J 6
#define RIJC_C 7

typedef unsigned int word;

void errorHint(string msg);

void inputHint();

void Hint(string msg);

class Sim{
private:
    unsigned char Memory[MEM_SIZE];
    int regs[REG_NUM];
    int PC;
    int entry;

public:
    Sim();
    ~Sim();

    void Start();
    void LoadInstr(vector<int> bin32s, int ofs);
    void LoadBin(vector<unsigned char> bin8s, int ofs);
    
    void Step();
    void Run();
    void ShowStatus();
    void PrintRegs();
    void Again();
    void ShutDown();

    Instr FetchInstr();
    Instr GetNextInstr();

    bool Execute(Instr ins);
    bool executeR1(Instr ir);
    bool executeR2(Instr ir);
    bool executeR3(Instr ir);
    bool executeI1(Instr ir);
    bool executeI2(Instr ir);
    bool executeI3(Instr ir);
    bool executeJ(Instr ir);
    bool executeC(Instr ir);
};

int RIJC(string op);

unsigned char hexstr2int8(string s);

#endif