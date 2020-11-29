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
#define CMD_EXIT 4

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

class Sim{
private:
    unsigned char Memory[MEM_SIZE];
    int regs[REG_NUM];
    int PC;
public:
    Sim(){
        memset(Memory, 0, sizeof(Memory));
        memset(regs, 0, sizeof(regs));
        PC = 0;
    }
    ~Sim(){

    }
    void Start(){
        int cmd = -1;
        inputHint();
        cin >> cmd;
        while(cmd != CMD_EXIT){
            if(cmd == CMD_LDINS){
                string line;
                getline(cin, line);
                vector<string> codes;
                while(line != "#"){
                    codes.push_back(line);
                    getline(cin, line);
                }
                vector<Instr> instrs = MultiTranslate(codes);
                Load(instrs);
            }
            else if(cmd == CMD_RUN){
                Run();
            }
            else if(cmd == CMD_STEP){
                cout << "step" << endl;
                Step();
            }
            else if(cmd == CMD_STATUS){
                ShowStatus();
            }
            else{

            }
            inputHint();
            cin >> cmd;
        }
        ShutDown();
    }

    void Load(vector<Instr> instrs){
        int base = 0;
        char* p = (char*)Memory + base;
        int b0, b1, b2, b3;
        for(int i=0; i<(int)instrs.size(); i++){
            int bin32 = instrs[i].toBin();
            b0 = (bin32 & 0xFF000000);
            b1 = (bin32 & 0x00FF0000);
            b2 = (bin32 & 0x0000FF00);
            b3 = (bin32 & 0x000000FF);
            *(int*)p = b0 | b1 | b2 | b3;
            p = p + 4;
        }
        this->PC = base;
    }

    bool Execute(Instr ins);

    Instr FetchInstr(){
        int* addr = (int*)(Memory + PC);
        int ir = *addr;
        PC = PC + sizeof(word);
        return Instr(ir);
    }

    Instr GetCurInstr(){
        int* addr = (int*)(Memory + PC);
        int ir = *addr;
        cout << "cur:" << ir << endl;
        return Instr(ir);
    }

    void Step(){
        Instr ins = FetchInstr();
        Execute(ins);
    }

    void Run(){
        Instr ins = FetchInstr();
        while(Execute(ins)){
            Instr ins = FetchInstr();
        }
    }

    void ShowStatus(){
        PrintRegs();
        string ir = GetCurInstr().all;
        cout<<ir<<endl;
    }

    void PrintRegs(){
        for(int i=0; i<REG_NUM; i++){
            printf("%8X\t", regs[i]);
            if(i&1) 
                cout<<endl;
        }
        // cout << endl;
    }

    void ShutDown(){
        cout << "Bye~" << endl;
    }

    bool executeR1(Instr ir);
    bool executeR2(Instr ir);
    bool executeR3(Instr ir);
    bool executeI1(Instr ir);
    bool executeI2(Instr ir);
    bool executeI3(Instr ir);
    bool executeJ(Instr ir);
    bool executeC(Instr ir);
};

#endif