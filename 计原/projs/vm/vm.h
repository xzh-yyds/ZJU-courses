#ifndef VM_H
#define VM_H

#include <cstring>
#include <iostream>
#include "instr.h"

#define MEM_SIZE 0x00000400
#define REG_NUM 32

#define CMD_LDINS 0
#define CMD_RUN 1
#define CMD_STEP 2
#define CMD_EXIT 3
#define CMD_STATUS 4

typedef unsigned int word;

class VM{
private:
    unsigned char Memory[MEM_SIZE];
    int regs[REG_NUM];
    int PC;
public:
    VM(){
        memset(Memory, 0, sizeof(Memory));
        memset(regs, 0, sizeof(regs));
        PC = 0;
    }
    ~VM(){

    }
    void Start(){
        int cmd = -1;
        while(cmd != CMD_EXIT){
            if(cmd == CMD_LDINS){
                string line;
                getline(cin, line);
                vector<string> codes;
                while(line != "#"){
                    codes.push_back(line);
                    getline(cin, line);
                }
                vector<Instr> instrs = translate(codes);
                Load(instrs);
            }
            else if(cmd == CMD_RUN){
                Run();
            }
            else if(cmd == CMD_STEP){
                Step();
            }
            else if(cmd == CMD_STATUS){
                ShowStatus();
            }
            else{

            }
            cout << "CMD: " << endl;
            cin >> cmd;
        }
        ShutDown();
    }

    void Load(vector<Instr> instrs){
        int base = 0;
        for(int i=0; i<(int)instrs.size(); i++){
            int bin32 = instrs[i].toBin();
            int j=2*i;
            Memory[base+j]=(short)(0x0000FFFF & bin32>>16);
            Memory[base+j+1]=(short)(0x0000FFFF & bin32);
        }
        this->PC = base;
    }

    bool Execute(Instr ins){

    }

    Instr FetchInstr(){
        int l = (int)Memory[PC];
        int h = (int)Memory[PC+1];
        int b32 = l | h<<16;
        PC = PC + sizeof(word);
        return Instr(b32);
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
    }

    void PrintRegs(){
        for(int i=0; i<REG_NUM; i++){
            printf("%X\t", regs[i]);
            if(i&1) 
                cout<<endl;
        }
        cout << endl;
    }

    void ShutDown(){
        cout << "Bye~" << endl;
    }
};

#endif