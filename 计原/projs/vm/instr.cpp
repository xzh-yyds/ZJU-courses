#include "instr.h"
#include <iostream>

map<int,string> regName = {
    {0, "$zero"},
    {1, "$at"},
    {2, "$v0"},
    {3, "$v1"},
    {4, "$a0"},
    {5, "$a1"},
    {6, "$a2"},
    {7, "$a3"},
    {8, "$t0"},
    {9, "$t1"},
    {10, "$t2"},
    {11, "$t3"},
    {12, "$t4"},
    {13, "$t5"},
    {14, "$t6"},
    {15, "$t7"},
    {16, "$s0"},
    {17, "$s1"},
    {18, "$s2"},
    {19, "$s3"},
    {20, "$s4"},
    {21, "$s5"},
    {22, "$s6"},
    {23, "$s7"},
    {24, "$t8"},
    {25, "$t9"},
    {26, "$k0"},
    {27, "$k1"},
    {28, "$gp"},
    {29, "$sp"},
    {30, "$fp"},
    {31, "$ra"},
};

map<string,int> regIndex = {
    {"zero", 0},
    {"$at", 1},
    {"$v0", 2},
    {"$v1", 3},
    {"$a0", 4},
    {"$a1", 5},
    {"$a2", 6},
    {"$a3", 7},
    {"$t0", 8},
    {"$t1", 9},
    {"$t2", 10},
    {"$t3", 11},
    {"$t4", 12},
    {"$t5", 13},
    {"$t6", 14},
    {"$t7", 15},
    {"$s0", 16},
    {"$s1", 17},
    {"$s2", 18},
    {"$s3", 19},
    {"$s4", 20},
    {"$s5", 21},
    {"$s6", 22},
    {"$s7", 23},
    {"$t8", 24},
    {"$t9", 25},
    {"$k0", 26},
    {"$k1", 27},
    {"$gp", 28},
    {"$sp", 29},
    {"$fp", 30},
    {"$ra", 31},
};

vector<string> strSplit(string s,char c){
    vector<string> res;
    int begin=0;
    for(int i=0;i<s.length();i++){
        if(s[i]==c){
            res.push_back(s.substr(begin,i-begin));
            begin=i+1;
        }
    }
    res.push_back(s.substr(begin,s.length()-begin));
    return res;
}

string strInBrackets(string s){
    int i=0,j=0;
    while(i<s.length() && s[i]!='('){
        i++;
    }
    j=i;
    while(j<s.length() && s[j]!=')'){
        j++;
    }
    if(j>=s.length()){
        return "";
    }
    return s.substr(i+1,j-i-1);
}

int RIJC(string op){
    if(op=="add"){
        return 1;
    }else if(op=="sub"){
        return 1;
    }else if(op=="slt"){
        return 1;
    }else if(op=="sltu"){
        return 1;
    }else if(op=="and"){
        return 1;
    }else if(op=="or"){
        return 1;
    }else if(op=="xor"){
        return 1;
    }else if(op=="nor"){
        return 1;
    }else if(op=="sllv"){
        return 1;
    }else if(op=="srlv"){
        return 1;
    }else if(op=="srav"){
        return 1;
    }

    else if(op=="sll"){
        return 2;
    }else if(op=="srl"){
        return 2;
    }else if(op=="sra"){
        return 2;
    }

    else if(op=="jr"){
        return 3;
    }else if(op=="jalr"){
        return 3;
    }else if(op=="syscall"){
        return 3;
    }

    else if(op=="addi"){
        return 4;
    }else if(op=="slti"){
        return 4;
    }else if(op=="sltiu"){
        return 4;
    }else if(op=="andi"){
        return 4;
    }else if(op=="ori"){
        return 4;
    }else if(op=="xori"){
        return 4;
    }

    else if(op=="lui"){
        return 5;
    }else if(op=="lw"){
        return 5;
    }else if(op=="lwx"){
        return 5;
    }else if(op=="lh"){
        return 5;
    }else if(op=="lhx"){
        return 5;
    }else if(op=="lhux"){
        return 5;
    }else if(op=="sw"){
        return 5;
    }else if(op=="swx"){
        return 5;
    }else if(op=="sh"){
        return 5;
    }else if(op=="shx"){
        return 5;
    }

    else if(op=="beq"){
        return 6;
    }else if(op=="bne"){
        return 6;
    }

    else if(op=="j"){
        return 7;
    }else if(op=="jal"){
        return 7;
    }

    else if(op=="mfc0"){
        return 8;
    }else if(op=="mtc0"){
        return 8;
    }else if(op=="eret"){
        return 8;
    }

    return -1;
}

vector<Instr> MultiTranslate(vector<string> codes){
    vector<Instr> res;
    return res;
}

string reasmC(int code){
    int func=code & 0x0000003F;
    if(func==24) return "eret";
    int rt=(code & 0x001F0000)>>16;
    int rc=(code & 0x0000F800)>>11;
    int rs=(code & 0x03E00000)>>21;
    string regrt=regName[rt];
    string regrc=regName[rc];
    if(rs==4) return "mtc0 "+regrt+","+regrc;
    if(rs==0) return "mfc0 "+regrt+","+regrc;
    return "error";
}
string reasmJ(int code){
    int op=(code & 0xFC000000)>>26;
    int addr=(code & 0x03FFFFFF);
    if(op==2) return "j " + to_string(addr);
    if(op==3) return "jal " + to_string(addr);
    return "error";
}
string reasmR(int code){
    string opname;
    int rs=(code & 0x03E00000)>>21;
    int rt=(code & 0x001F0000)>>16;
    int rd=(code & 0x0000F800)>>11;
    int sa=(code & 0x00000C70)>>6;
    int func=code & 0x0000003F;
    int rtype=0;
    switch(func){
    case 32: opname="add"; break;
    case 34: opname="sub"; break;
    case 42: opname="slt"; break;
    case 43: opname="sltu"; break;
    case 36: opname="and"; break;
    case 37: opname="or"; break;
    case 38: opname="xor"; break;
    case 39: opname="nor"; break;
    case 0:  opname="sll"; rtype=1; break;
    case 4:  opname="sllv"; break;
    case 2:  opname="srl"; rtype=1; break;
    case 6:  opname="srlv"; break;
    case 3:  opname="sra"; rtype=1; break;
    case 7:  opname="srav"; break;
    case 8:  opname="jr"; rtype=2; break;
    case 9:  opname="jalr"; rtype=3; break;
    case 12: return "syscall"; break;
    default: break;
    }
    if(rtype==1) return opname+" "+regName[rd]+","+regName[rs]+","+regName[sa];
    if(rtype==2) return opname+" "+regName[rs];
    if(rtype==3) return opname+" "+regName[rs]+","+regName[rd];
    if(rtype==0) return opname+" "+regName[rd]+","+regName[rs]+","+regName[rt];
    return "error";
}
string reasm(int code){
    int op=(code & 0xFC000000)>>26;
    if(op==2||op==3) return reasmJ(code);
    if(op==16) return reasmC(code);
    string opname;
    int itype=0;
    switch (op){
    case 15: opname="lui"; break;
    case 8:  opname="addi"; break;
    case 10: opname="slti"; break;
    case 11: opname="sltiu"; break;
    case 12: opname="andi"; itype=4; break;
    case 13: opname="ori"; itype=4; break;
    case 14: opname="xori"; itype=4; break;
    case 35: opname="lw"; itype=1; break;
    case 34: opname="lwx"; itype=1; break;
    case 33: opname="lh"; itype=1; break;
    case 32: opname="lhx"; itype=1; break;
    case 37: opname="lhu"; itype=1; break;
    case 36: opname="lhux"; itype=1; break;
    case 43: opname="sw"; itype=1; break;
    case 42: opname="swx"; itype=1; break;
    case 41: opname="sh"; itype=1; break;
    case 40: opname="shx"; itype=1; break;
    case 4:  opname="beq"; itype=2; break;
    case 5:  opname="bne"; itype=2; break;
    case 1:  opname="bgezal"; itype=3; break;
    case 0:  return reasmR(code);
    default: return "error";
    }
    int rs=(code & 0x03E00000)>>21;
    int rt=(code & 0x001F0000)>>16;
    int immed=code & 0x0000FFFF;
    int dat=(short)immed;
    int dot=immed & 0x0000FFFF;
    int ofs=immed & 0x0000FFFF;
    if(itype==0) 
        return opname+ " " + regName[rt] + "," + regName[rs] + "," + to_string(dat);
    if(itype==1) 
        return opname+ " " + regName[rt] + "," + regName[dat] + "(" + regName[rs]+")";
    if(itype==2) 
        return opname+ " " + regName[rs] + "," + regName[rt] + "," + to_string(ofs);
    if(itype==3) 
        return opname+ " " + regName[rs] + "," + regName[ofs];
    if(itype==4) 
        return opname+ " " + regName[rt] + "," + regName[rs] + "," + to_string(dot);
    
    return "error";
}

Instr::Instr(int bin){
    string ir = reasm(bin);
}

Instr::Instr(string s){
    string ir = prepare(s);
    // cout << ir << endl;
    this->all = s;
    this->args = strSplit(ir,',');
}

Instr::~Instr(){
    
}

int Instr::toBin(){
    int res = translate(this->args);
    return 0;
}

string prepare(string s){
    while(s.length()>0 && s[0]==' '){
        s.erase(s.begin());
    }
    while(s.length()>0 && s[s.length()-1]==' '){
        s.erase(s.end()-1);
    }
    for(int i=0;i<(int)s.length()-1;i++){
        if(s[i]==' ' && s[i+1]==' '){
            s.erase(s.begin()+i);
        }
    }
    int first=1;
    for(int i=0;i<(int)s.length();i++){
        if(s[i]==' '){
            if(first){
                first=0;
            }else{
                s.erase(s.begin()+i);
                i--;
            }
        }
    }
    for(int i=0;i<(int)s.length();i++){
        if(s[i]==' '){
            s[i]=',';
        }
    }
    return s;
}

int funcNum(string op){
    if(op=="mfc0") return 0;
    if(op=="mtc0") return 0;
    if(op=="eret") return 24;

    if(op=="add") return 32;
    if(op=="addu") return 33;
    if(op=="sub") return 34;
    if(op=="subu") return 35;
    if(op=="and") return 36;
    if(op=="or") return 37;
    if(op=="xor") return 38;
    if(op=="nor") return 39;
    if(op=="slt") return 42;
    if(op=="sltu") return 43;
    if(op=="sll") return 0;
    if(op=="sllv") return 4;
    if(op=="srl") return 2;
    if(op=="srlv") return 6;
    if(op=="sra") return 3;
    if(op=="srav") return 7;
    if(op=="jr") return 8;
    if(op=="jalr") return 9;
    if(op=="syscall") return 12;

    return -1;
}

int translateR(int op, vector<string> instr){
    int res;
    int rs,rt,rd,sa,func;
    if(instr.size()==1 && instr[0]=="syscall"){
        return 12;
    }
    if(instr.size()==2 && instr[0]=="jr"){
        rs=regIndex[instr[1]];
        rt=rd=sa=0;
        func=8;
        res=op<<26|rs<<21|rt<<16|rd<<11|sa<<6|func;
        return res;
    }
    if(instr.size()==3 && instr[0]=="jalr"){
        rs=regIndex[instr[1]];
        rd=regIndex[instr[2]];
        rt=0;
        sa=0;
        func=9;
        res=op<<26|rs<<21|rt<<16|rd<<11|sa<<6|func;
        return res;
    }
    if(instr.size()!=4){
        return -1;
    }
    func=funcNum(instr[0]);
    if(func==0||func==4||func==2||func==6||func==3||func==7){
        sa = stoi(instr[3]);
        rt = 0;
    }else{
        rt = regIndex[instr[3]];
        sa = 0;
    }
    rs = regIndex[instr[2]];
    rd = regIndex[instr[1]];

    res = op<<26 | rs<<21 | rt<<16 | rd<<11 | sa<<6 | func;
    return res;
}

int translateI(int op, vector<string> instr){
    int res;
    int rs,rt,immed;
    if(instr.size()==3){
        if(instr[0]=="bgezal"){
            rs = regIndex[instr[1]];
            rt = 17;
            immed = stoi(instr[2]);
            immed = immed & 0xFFFF;
            res = op<<26 | rs<<21 | rt<<16 | immed;
            return res;
        }
        rt = regIndex[instr[1]];
        immed = stoi(instr[2]);
        if(instr[0] == "lui"){
            rs=0;
        }else{
            rs = regIndex[strInBrackets(instr[2])];
        }
        immed=immed & 0xFFFF;
        res = op<<26 | rs<<21 | rt<<16 | immed;
        return res;
    }
    if(instr.size() != 4){
        return -1;
    }
    rt = regIndex[instr[1]];
    rs = regIndex[instr[2]];
    immed = stoi(instr[3]);
    immed = immed & 0xFFFF;
    res = op<<26 | rs<<21 | rt<<16 | immed;
    return res;
}

int translateJ(int op, vector<string> instr){
    int res,addr;
    if(instr.size()!=2){
        return -1;
    }
    addr=stoi(instr[1]);
    res=op<<26 | ((addr) & 0x3FFFFFF);
    return res;
}

int translateC(int op, vector<string> instr){
    if(instr.size()==1 && instr[0]=="eret"){
        return 0x42000018;
    }
    if(instr.size() != 3){
        return -1;
    }
    int res;
    int rt,rc;
    rt = regIndex[instr[1]];
    rc = regIndex[instr[2]];
    res = op<<26 | rt<<16 | rc<<11;
    return res;
}

int isRIJC(string op){
    if(op=="add") return 0;
    if(op=="sub") return 0;
    if(op=="slt") return 0;
    if(op=="and") return 0;
    if(op=="or") return 0;
    if(op=="xor") return 0;
    if(op=="nor") return 0;
    if(op=="sll") return 0;
    if(op=="sllv") return 0;
    if(op=="srl") return 0;
    if(op=="srlv") return 0;
    if(op=="sra") return 0;
    if(op=="srav") return 0;
    if(op=="jr") return 0;
    if(op=="jalr") return 0;
    if(op=="syscall") return 0;

    if(op=="lui") return 1;
    if(op=="addi") return 1;
    if(op=="slti") return 1;
    if(op=="sltu") return 1;
    if(op=="sltiu") return 1;
    if(op=="andi") return 1;
    if(op=="ori") return 1;
    if(op=="xori") return 1;
    if(op=="lw") return 1;
    if(op=="lwx") return 1;
    if(op=="lh") return 1;
    if(op=="lhx") return 1;
    if(op=="lhu") return 1;
    if(op=="lhux") return 1;
    if(op=="sw") return 1;
    if(op=="swx") return 1;
    if(op=="sh") return 1;
    if(op=="shx") return 1;
    if(op=="beq") return 1;
    if(op=="bne") return 1;
    if(op=="bgezal") return 1;

    if(op=="j") return 2;
    if(op=="jal") return 2;

    if(op=="mfc0") return 3;
    if(op=="mtc0") return 3;
    if(op=="eret") return 3;

    return -1;
}

int opcode(string op){
    //C-type
    if(op=="mfc0") return 16;
    if(op=="mtc0") return 16;
    if(op=="eret") return 16;
    //J-type
    if(op=="j") return 2;
    if(op=="jal") return 3;
    //I-type
    if(op=="addi") return 8;
    if(op=="addiu") return 9;
    if(op=="andi") return 12;
    if(op=="ori") return 13;
    if(op=="xori") return 14;
    if(op=="lui") return 15;
    if(op=="lw") return 35;
    if(op=="lwx") return 34;
    if(op=="lh") return 33;
    if(op=="lhx") return 32;
    if(op=="lhu") return 37;
    if(op=="lhux") return 36;
    if(op=="sw") return 43;
    if(op=="swx") return 42;
    if(op=="sh") return 41;
    if(op=="shx") return 40;
    if(op=="beq") return 4;
    if(op=="bne") return 5;
    if(op=="bgezal") return 1;
    if(op=="slti") return 10;
    if(op=="sltiu") return 11;
    //R-type
    if(op=="add") return 0;
    if(op=="sub") return 0;
    if(op=="slt") return 0;
    if(op=="and") return 0;
    if(op=="or") return 0;
    if(op=="xor") return 0;
    if(op=="nor") return 0;
    if(op=="sll") return 0;
    if(op=="sllv") return 0;
    if(op=="srl") return 0;
    if(op=="srlv") return 0;
    if(op=="sra") return 0;
    if(op=="srav") return 0;
    if(op=="jr") return 0;
    if(op=="jalr") return 0;
    if(op=="syscall") return 0;

    return -1;
}

int translate(vector<string> opm){
    //instr=prepare(instr);
    //vector<string> opm=strSplit(instr,',');
    int rijc=isRIJC(opm[0]);
    int op=opcode(opm[0]);
    if(rijc==0){
        return translateR(op,opm);
    }
    else if(rijc==1){
        return translateI(op,opm);
    }
    else if(rijc==2){
        return translateJ(op,opm);
    }
    else if(rijc==3){
        return translateC(op,opm);
    }
    return -1;
}