#include "sim.h"

void errorHint(string msg){
    cout << "Error: " << msg << endl;
}
void inputHint(){
    cout << "Type in:" << endl;
    cout << "\t0: load irs" << endl;
    cout << "\t1: run" << endl;
    cout << "\t2: step" << endl;
    cout << "\t3: status" << endl;
    cout << "\t4: exit" << endl;
}

bool Sim::Execute(Instr ir){
    int type = RIJC(ir.args[0]);
    bool res = false;

    switch (type){
    case RIJC_R1:
        res = executeR1(ir);
        break;
    case RIJC_R2:
        res = executeR2(ir);
        break;
    case RIJC_R3:
        res = executeR3(ir);
        break;
    case RIJC_I1:
        res = executeI1(ir);
        break;
    case RIJC_I2:
        res = executeI2(ir);
        break;
    case RIJC_I3:
        res = executeI3(ir);
    case RIJC_J:
        res = executeJ(ir);
        break;
    case RIJC_C:
        res = executeC(ir);
        break;
    default:
        break;
    }
    return res;
}

bool Sim::executeR1(Instr ir){
    int rd,rs,rt;
    rd = regIndex[ir.args[1]];
    rs = regIndex[ir.args[2]];
    rt = regIndex[ir.args[3]];

    if(ir.args[0] == "add"){
        regs[rd] = regs[rs] + regs[rt];
    }
    else if(ir.args[0] == "sub"){
        regs[rd] = regs[rs] - regs[rt];
    }
    else if(ir.args[0] == "slt"){
        regs[rd] = (regs[rs] < regs[rt])?1:0;
    }
    else if(ir.args[0] == "sltu"){
        regs[rd] = ((unsigned)regs[rs] < (unsigned)regs[rt])?1:0;
    }
    else if(ir.args[0] == "and"){
        regs[rd] = regs[rs] & regs[rt];
    }
    else if(ir.args[0] == "or"){
        regs[rd] = regs[rs] | regs[rt];
    }
    else if(ir.args[0] == "xor"){
        regs[rd] = regs[rs] ^ regs[rt];
    }
    else if(ir.args[0] == "nor"){
        regs[rd] = ~(regs[rs] | regs[rt]);
    }
    else if(ir.args[0] == "sllv"){
        regs[rd] = regs[rs]<<regs[rt];
    }
    else if(ir.args[0] == "srlv"){
        regs[rd] = (unsigned)regs[rs]>>regs[rt];
    }
    else if(ir.args[0] == "srav"){
        regs[rd] = regs[rs]>>regs[rt];
    }
    else{
        return false;
    }
    return true;
}

bool Sim::executeR2(Instr ir){
    int rd,rs,sa;
    rd = regIndex[ir.args[1]];
    rs = regIndex[ir.args[2]];
    sa = stoi(ir.args[3]);

    if(ir.args[0] == "sll"){
        regs[rd] = regs[rs]<<sa;
    }
    else if(ir.args[0] == "srl"){
        regs[rd] = (unsigned)regs[rs]>>sa;
    }
    else if(ir.args[0] == "sra"){
        regs[rd] = regs[rs]>>sa;
    }
    else{
        return false;
    }
    return true;
}

bool Sim::executeR3(Instr ir){
    if(ir.args[0] == "jr"){
        int rs = regIndex[ir.args[1]];
        PC = regs[rs];
    }
    else if(ir.args[0] == "jalr"){
        int rs=regIndex[ir.args[1]];
        int rd=regIndex[ir.args[2]];
        regs[rd] = PC;
        PC=regs[rs];
    }
    else if(ir.args[0] == "syscall"){

    }
    else{
        return false;
    }
    return true;
}

bool Sim::executeI1(Instr ir){
    int rt,rs,dat=0;
    unsigned dot=0;
    rt = regIndex[ir.args[1]];
    rs = regIndex[ir.args[2]];

    if(ir.args[0] == "addi"){
        dat = stoi(ir.args[3]);
        regs[rt] = regs[rs] + dat;
    }
    else if(ir.args[0] == "slti"){
        dat = stoi(ir.args[3]);
        regs[rt] = (regs[rs] < dat)?1:0;
    }
    else if(ir.args[0] == "sltiu"){
        dat = stoi(ir.args[3]);
        regs[rt] = ((unsigned)regs[rs] < (unsigned)dat)?1:0;
    }
    else if(ir.args[0] == "andi"){
        dot = stoul(ir.args[3]);
        regs[rt] = regs[rs] & dot;
    }
    else if(ir.args[0] == "ori"){
        dot = stoul(ir.args[3]);
        regs[rt] = regs[rs] | dot;
    }
    else if(ir.args[0] == "xori"){
        dot = stoul(ir.args[3]);
        regs[rt] = regs[rs] ^ dot;
    }
    else{
        return false;
    }
    return true;
}

bool Sim::executeI2(Instr ir){
    if(ir.args.size()<3){
        return false;
    }

    int rt, dat, rs;
    int high = 0, low = 0;
    rt = regIndex[ir.args[1]];
    dat = stoi(ir.args[2]);
    rs = regIndex[strInBrackets(ir.args[2])];
    
    int b0, b1, b2, b3;
    if(ir.args[0] == "lui"){
        regs[rt] = dat<<16;
    }
    else if(ir.args[0] == "lw"){
        char* p = (char*)((Memory) + dat + regs[rs]);
        b0 = *p;
        b1 = *(p+1);
        b2 = *(p+2);
        b3 = *(p+3);
        regs[rt] = b0<<24 | b1<<16 | b2<<8 | b3;
    }
    else if(ir.args[0]=="lwx"){
        char* p = (char*)((Memory) + dat + regs[rs]);
        b0 = *p;
        b1 = *(p+1);
        b2 = *(p+2);
        b3 = *(p+3);
        regs[rt] = b3<<24 | b2<<16 | b1<<8 | b0;
    }
    else if(ir.args[0]=="lh"){
        char* p = (char*)((Memory) + dat + regs[rs]);
        b0 = *p;
        b1 = *(p+1);
        regs[rt] = b0<<8 | b1;

        if(regs[rt] & 0x00008000){
            regs[rt] |= 0xFFFF0000;
        }
    }
    else if(ir.args[0]=="lhx"){
        char* p = (char*)((Memory) + dat + regs[rs]);
        b0 = *p;
        b1 = *(p+1);
        regs[rt] = b1<<8 | b0;

        if(regs[rt] & 0x00008000){
            regs[rt] |= 0xFFFF0000;
        }
    }
    else if(ir.args[0]=="lhu"){
        char* p = (char*)((Memory) + dat + regs[rs]);
        b0 = *p;
        b1 = *(p+1);
        regs[rt] = b0<<8 | b1;
    }
    else if(ir.args[0]=="lhux"){
        char* p = (char*)((Memory) + dat + regs[rs]);
        b0 = *p;
        b1 = *(p+1);
        regs[rt] = b1<<8 | b0;
    }
    else if(ir.args[0]=="sw"){
        char* p = (char*)((Memory) + dat + regs[rs]);
        b0 = (regs[rt] & 0xFF000000)>>24;
        b1 = (regs[rt] & 0x00FF0000)>>16;
        b2 = (regs[rt] & 0x0000FF00)>>8;
        b3 = (regs[rt] & 0x000000FF);
        *p = b0;
        *(p+1) = b1;
        *(p+2) = b2;
        *(p+3) = b3;
    }
    else if(ir.args[0]=="swx"){
        char* p = (char*)((Memory) + dat + regs[rs]);
        b3 = (regs[rt] & 0xFF000000)>>24;
        b2 = (regs[rt] & 0x00FF0000)>>16;
        b1 = (regs[rt] & 0x0000FF00)>>8;
        b0 = (regs[rt] & 0x000000FF);
        *p = b0;
        *(p+1) = b1;
        *(p+2) = b2;
        *(p+3) = b3;
    }
    else if(ir.args[0]=="sh"){
        char* p = (char*)((Memory) + dat + regs[rs]);
        b0 = (regs[rt] & 0x0000FF00)>>8;
        b1 = (regs[rt] & 0x000000FF);
        *p = b0;
        *(p+1) = b1;
    }
    else if(ir.args[0]=="shx"){
        char* p = (char*)((Memory) + dat + regs[rs]);
        b1 = (regs[rt] & 0x0000FF00)>>8;
        b0 = (regs[rt] & 0x000000FF);
        *p = b0;
        *(p+1) = b1;
    }
    else{
        return false;
    }
    return true;
}

bool Sim::executeI3(Instr ir){
    if(ir.args.size()<4){
        return false;
    }

    int rs,rt,ofs;
    rs=regIndex[ir.args[1]];
    rt=regIndex[ir.args[2]];
    ofs=stoi(ir.args[3]);

    if(ir.args[0] == "beq"){
        if(regs[rt] == regs[rs]){
            PC = PC + ofs<<2;
        }
    }
    else if(ir.args[0] == "bne"){
        if(regs[rt] != regs[rs]){
            PC = PC + ofs<<2;
        }
    }
    else{
        return false;
    }
    return true;
}

bool Sim::executeJ(Instr ir){
    int addr=stoi(ir.args[1]);
    if(addr > 0x03FFFFFF){
        return false;
    }
    if(ir.args[0] == "j"){
        PC = (PC & 0xF0000000) | addr<<2;
    }
    else if(ir.args[0] == "jal"){
        regs[31]=PC;
        PC = (PC & 0xF0000000) | addr<<2;
    }
    else{
        return false;
    }
    return true;
}

bool Sim::executeC(Instr ir){
    if(ir.args.size()==3){
        int rt=regIndex[ir.args[1]];
        int rc=regIndex[ir.args[2]];
        
        if(ir.args[0]=="mfc0"){
            regs[rt]=regs[rc];
        }
        else if(ir.args[0]=="mtc0"){
            regs[rc]=regs[rt];
        }
    }
    else if(ir.args.size()==1){
        if(ir.args[0]=="eret"){

        }
    }
    else{
        return false;
    }
    return true;
}
