#include <iostream>
#include <string>
#include "sim.h"
#include "instr.h"

using namespace std;

int main(){
    vector<Instr> irs;
    irs.push_back(Instr("addi $s1, $zero, 3"));
    irs.push_back(Instr("xor $t0, $t0, t0"));
    irs.push_back(Instr("add $t0, $t0, $s1"));
    irs.push_back(Instr("addi $s1, $s1, -1"));
    irs.push_back(Instr("add $t0, $t0, $s1"));
    irs.push_back(Instr("bne $s1, $zero, -3"));
    irs.push_back(Instr("add $s0, $t0, $zero"));

    // Sim vm;
    // vm.Load(irs);
    // vm.Start();
    int im =  0x0000FFFF;
    
    int a = -3;

    cout << (1 + (a<<2)) << endl;

    return 0;
}