#include"sim.h"
#include<iostream>
#include<vector>
#include<string>
#include<map>
using namespace std;

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

int regs[32];
short memory[MEMSIZE];
int PC=0;
map<string,int> reg2ind;
map<int,string> ind2reg;

Instruction::Instruction(string instr){
    string instr_processed=prepare(instr);
    cout<<instr_processed<<endl;
    all=instr;
    opms=strSplit(instr_processed,',');
}
Instruction::Instruction(){

}
Instruction::~Instruction(){

}

//vector<Instruction> instrs;

vector<Label> labels;

void initial(){
    for(int i=0;i<32;i++){
        regs[i]=0;
    }
    for(int i=0;i<MEMSIZE;i++){
        memory[i]=0;
    }
    PC=0;
}

void regsInitial(){
    for(int i=0;i<32;i++){
        regs[i]=0;
    }
}

void memInitial(){
    for(int i=0;i<MEMSIZE;i++){
        memory[i]=0;
    }
}

void instrLoad(vector<Instruction> instrs){
    int base=0x00000000;
    for(int i=0;i<(int)instrs.size();i++){
        int translate_res=translate(instrs[i].all);
        int j=2*i;
        memory[base+j]=(short)(0x0000FFFF & translate_res>>16);
        memory[base+j+1]=(short)(0x0000FFFF & translate_res);
    }
}

void execute(Instruction instr){
    int type=RIJC(instr.opms[0]);
    if(type==1){
        executeR1(instr);
    }else if(type==2){
        executeR2(instr);
    }else if(type==3){
        executeR3(instr);
    }else if(type==4){
        executeI1(instr);
    }else if(type==5){
        executeI2(instr);
    }else if(type==6){
        executeI3(instr);
    }else if(type==7){
        executeJ(instr);
    }else if(type==8){
        executeC(instr);
    }
}
void executeR1(Instruction instr){
    int rd,rs,rt;
    rd=regIndex(instr.opms[1]);
    rs=regIndex(instr.opms[2]);
    rt=regIndex(instr.opms[3]);
    if(instr.opms[0]=="add"){
        regs[rd]=regs[rs]+regs[rt];
    }else if(instr.opms[0]=="sub"){
        regs[rd]=regs[rs]-regs[rt];
    }else if(instr.opms[0]=="slt"){
        regs[rd]=(regs[rs]<regs[rt])?1:0;
    }else if(instr.opms[0]=="sltu"){
        regs[rd]=((unsigned)regs[rs]<(unsigned)regs[rt])?1:0;
    }else if(instr.opms[0]=="and"){
        regs[rd]=regs[rs]&regs[rt];
    }else if(instr.opms[0]=="or"){
        regs[rd]=regs[rs]|regs[rt];
    }else if(instr.opms[0]=="xor"){
        regs[rd]=regs[rs]^regs[rt];
    }else if(instr.opms[0]=="nor"){
        regs[rd]=~(regs[rs]|regs[rt]);
    }else if(instr.opms[0]=="sllv"){
        regs[rd]=regs[rs]<<regs[rt];
    }else if(instr.opms[0]=="srlv"){
        regs[rd]=(unsigned)regs[rs]>>regs[rt];
    }else if(instr.opms[0]=="srav"){
        regs[rd]=regs[rs]>>regs[rt];
    }
}
void executeR2(Instruction instr){
    int rd,rs,sa;
    rd=regIndex(instr.opms[1]);
    rs=regIndex(instr.opms[2]);
    sa=stoi(instr.opms[3]);
    if(instr.opms[0]=="sll"){
        regs[rd]=regs[rs]<<sa;
    }else if(instr.opms[0]=="srl"){
        regs[rd]=(unsigned)regs[rs]>>sa;
    }else if(instr.opms[0]=="sra"){
        regs[rd]=regs[rs]>>sa;
    }
}
void executeR3(Instruction instr){
    if(instr.opms[0]=="jr"){
        int rs=regIndex(instr.opms[1]);
        PC=regs[rs];
    }else if(instr.opms[0]=="jalr"){
        int rs=regIndex(instr.opms[1]);
        int rd=regIndex(instr.opms[2]);
        regs[rd]=PC;
        PC=regs[rs];
    }else if(instr.opms[0]=="syscall"){

    }
}
void executeI1(Instruction instr){
    int rt,rs,dat=0;
    unsigned dot=0;
    rt=regIndex(instr.opms[1]);
    rs=regIndex(instr.opms[2]);
    if(instr.opms[0]=="addi"){
        dat=stoi(instr.opms[3]);
        regs[rt]=regs[rs]+dat;
    }else if(instr.opms[0]=="slti"){
        dat=stoi(instr.opms[3]);
        regs[rt]=(regs[rs]<dat)?1:0;
    }else if(instr.opms[0]=="sltiu"){
        dat=stoi(instr.opms[3]);
        regs[rt]=((unsigned)regs[rs]<(unsigned)dat)?1:0;
    }else if(instr.opms[0]=="andi"){
        dot=stoul(instr.opms[3]);
        regs[rt]=regs[rs]&dot;
    }else if(instr.opms[0]=="ori"){
        dot=stoul(instr.opms[3]);
        regs[rt]=regs[rs]|dot;
    }else if(instr.opms[0]=="xori"){
        dot=stoul(instr.opms[3]);
        regs[rt]=regs[rs]^dot;
    }
}
void executeI2(Instruction instr){
    if(instr.opms.size()<3){
        return;
    }
    int rt,dat,rs;
    int high=0,low=0;
    rt=regIndex(instr.opms[1]);
    dat=stoi(instr.opms[2]);
    rs=regIndex(strInBrackets(instr.opms[2]));
    if(instr.opms[0]=="lui"){
        regs[rt]=dat<<16;
    }else if(instr.opms[0]=="lw"){
        high=memory[regs[rs]+dat];
        low=memory[regs[rs]+dat+1];
        regs[rt]=high<<16|low;
    }else if(instr.opms[0]=="lwx"){
        high=memory[regs[rs]+dat+1];
        low=memory[regs[rs]+dat];
        regs[rt]=high<<16|low;
    }else if(instr.opms[0]=="lh"){
        regs[rt]=memory[regs[rs]+dat];
        if(regs[rt]&0x00008000){
            regs[rt]|=0xFFFF0000;
        }
    }else if(instr.opms[0]=="lhx"){
        regs[rt]=memory[regs[rs]+dat];
        if(regs[rt]&0x00008000){
            regs[rt]|=0xFFFF0000;
        }
    }else if(instr.opms[0]=="lhu"){
        regs[rt]=memory[regs[rs]+dat];
    }else if(instr.opms[0]=="lhux"){
        regs[rt]=memory[regs[rs]+dat];
    }else if(instr.opms[0]=="sw"){
        high=regs[rt]>>16 & 0x0000FFFF;
        low=regs[rt] & 0x0000FFFF;
        memory[regs[rs]+dat]=(short)high;
        memory[regs[rs]+dat+1]=(short)low;
    }else if(instr.opms[0]=="swx"){
        high=regs[rt]>>16 & 0x0000FFFF;
        low=regs[rt] & 0x0000FFFF;
        memory[regs[rs]+dat+1]=(short)high;
        memory[regs[rs]+dat]=(short)low;
    }else if(instr.opms[0]=="sh"){
        memory[regs[rs]+dat]=(short)(regs[rt]&0x0000FFFF);
    }else if(instr.opms[0]=="shx"){
        short l=(short)(regs[rt]&0x0000FF00>>8);
        short h=(short)(regs[rt]&0x000000FF<<8);
        memory[regs[rs]+dat]=h|l;
    }
}
void executeI3(Instruction instr){
    if(instr.opms.size()<4){
        return;
    }
    int rs,rt,ofs;
    rs=regIndex(instr.opms[1]);
    rt=regIndex(instr.opms[2]);
    ofs=stoi(instr.opms[3]);
    if(instr.opms[0]=="beq"){
        if(regs[rt]==regs[rs]){
            PC=PC+ofs;
        }
    }else if(instr.opms[0]=="bne"){
        if(regs[rt]!=regs[rs]){
            PC=PC+ofs;
        }
    }
}
void executeJ(Instruction instr){
    int addr=stoi(instr.opms[1]);
    if(instr.opms[0]=="j"){
        PC=(PC&0xF8000000)|addr;
    }else if(instr.opms[0]=="jal"){
        regs[31]=PC;
        PC=(PC&0xF8000000)+addr;
    }
}
void executeC(Instruction instr){
    if(instr.opms.size()==3){
        int rt=reg2ind[instr.opms[1]];
        int rc=reg2ind[instr.opms[2]];
        if(instr.opms[0]=="mfc0"){
            regs[rt]=regs[rc];
        }else if(instr.opms[0]=="mtc0"){
            regs[rc]=regs[rt];
        }
    }else if(instr.opms.size()==1){
        if(instr.opms[0]=="eret"){

        }
    }
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

int regIndex(string regName){
    if(regName=="$zero") return 0;
    if(regName=="$at") return 1;

    if(regName=="$v0") return 2;
    if(regName=="$v1") return 3;

    if(regName=="$a0") return 4;
    if(regName=="$a1") return 5;
    if(regName=="$a2") return 6;
    if(regName=="$a3") return 7;

    if(regName=="$t0") return 8;
    if(regName=="$t1") return 9;
    if(regName=="$t2") return 10;
    if(regName=="$t3") return 11;
    if(regName=="$t4") return 12;
    if(regName=="$t5") return 13;
    if(regName=="$t6") return 14;
    if(regName=="$t7") return 15;

    if(regName=="$s0") return 16;
    if(regName=="$s1") return 17;
    if(regName=="$s2") return 18;
    if(regName=="$s3") return 19;
    if(regName=="$s4") return 20;
    if(regName=="$s5") return 21;
    if(regName=="$s6") return 22;
    if(regName=="$s7") return 23;

    if(regName=="$t8") return 24;
    if(regName=="$t9") return 25;

    if(regName=="$k0") return 26;
    if(regName=="$k1") return 27;

    if(regName=="$gp") return 28;
    if(regName=="$sp") return 29;
    if(regName=="$fp") return 30;
    if(regName=="$ra") return 31;

    return -1;
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

int str2num(string s){
    int res;
    char *str=new char[s.length()+1];
    for(int i=0;i<s.length();i++){
        str[i]=s[i];
    }
    str[s.length()]='\0';
    sscanf(str,"%d",&res);
    return res;
}

int translateR(int op, vector<string> instr){
    int res;
    int rs,rt,rd,sa,func;
    if(instr.size()==1 && instr[0]=="syscall"){
        return 12;
    }
    if(instr.size()==2 && instr[0]=="jr"){
        rs=regIndex(instr[1]);
        rt=rd=sa=0;
        func=8;
        res=op<<26|rs<<21|rt<<16|rd<<11|sa<<6|func;
        return res;
    }
    if(instr.size()==3 && instr[0]=="jalr"){
        rs=regIndex(instr[1]);
        rd=regIndex(instr[2]);
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
        sa=str2num(instr[3]);
        rt=0;
    }else{
        rt=regIndex(instr[3]);
        sa=0;
    }
    rs=regIndex(instr[2]);
    rd=regIndex(instr[1]);

    res=op<<26|rs<<21|rt<<16|rd<<11|sa<<6|func;
    return res;
}
int translateI(int op, vector<string> instr){
    int res;
    int rs,rt,immed;
    if(instr.size()==3){
        if(instr[0]=="bgezal"){
            rs=regIndex(instr[1]);
            rt=17;
            immed=str2num(instr[2]);
            immed=immed & 0xFFFF;
            res=op<<26|rs<<21|rt<<16|immed;
            return res;
        }
        rt=regIndex(instr[1]);
        immed=str2num(instr[2]);
        if(instr[0]=="lui"){
            rs=0;
        }else{
            rs=regIndex(strInBrackets(instr[2]));
        }
        immed=immed & 0xFFFF;
        res=op<<26|rs<<21|rt<<16|immed;
        return res;
    }
    if(instr.size()!=4){
        return -1;
    }
    rt=regIndex(instr[1]);
    rs=regIndex(instr[2]);
    immed=str2num(instr[3]);
    immed=immed & 0xFFFF;
    res=op<<26|rs<<21|rt<<16|immed;
    return res;
}
int translateJ(int op, vector<string> instr){
    int res,addr;
    if(instr.size()!=2){
        return -1;
    }
    addr=str2num(instr[1]);
    res=op<<26 | ((addr) & 0x3FFFFFF);
    return res;
}
int translateC(int op, vector<string> instr){
    if(instr.size()==1 && instr[0]=="eret"){
        return 0x42000018;
    }
    if(instr.size()!=3){
        return -1;
    }
    int res;
    int rt,rc;
    rt=regIndex(instr[1]);
    rc=regIndex(instr[2]);
    res=op<<26|rt<<16|rc<<11;
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
int translate(string instr){
    instr=prepare(instr);
    vector<string> opm=strSplit(instr,',');
    int rijc=isRIJC(opm[0]);
    int op=opcode(opm[0]);
    if(rijc==0){
        return translateR(op,opm);
    }else if(rijc==1){
        return translateI(op,opm);
    }else if(rijc==2){
        return translateJ(op,opm);
    }else if(rijc==3){
        return translateC(op,opm);
    }
    return -1;
}

// reasm
string regName(int num){
    if(num==0) return "$zero";
    if(num==1) return "$at";

    if(num==2) return "$v0";
    if(num==3) return "$v1";

    if(num==4) return "$a0";
    if(num==5) return "$a1";
    if(num==6) return "$a2";
    if(num==7) return "$a3";

    if(num==8) return "$t0";
    if(num==9) return "$t1";
    if(num==10) return "$t2";
    if(num==11) return "$t3";
    if(num==12) return "$t4";
    if(num==13) return "$t5";
    if(num==14) return "$t6";
    if(num==15) return "$t7";

    if(num==16) return "$s0";
    if(num==17) return "$s1";
    if(num==18) return "$s2";
    if(num==19) return "$s3";
    if(num==20) return "$s4";
    if(num==21) return "$s5";
    if(num==22) return "$s6";
    if(num==23) return "$s7";

    if(num==24) return "$t8";
    if(num==25) return "$t9";

    if(num==26) return "$k0";
    if(num==27) return "$k1";

    if(num==28) return "$gp";
    if(num==29) return "$sp";
    if(num==30) return "$fp";
    if(num==31) return "$ra";

    return "";
}
string num2str(int num){
    char s[20];
    sprintf(s,"%d",num);
    string str(s);
    return str;
}
string reasmC(int code){
    int func=code & 0x0000003F;
    if(func==24) return "eret";
    int rt=(code & 0x001F0000)>>16;
    int rc=(code & 0x0000F800)>>11;
    int rs=(code & 0x03E00000)>>21;
    string regrt=regName(rt);
    string regrc=regName(rc);
    if(rs==4) return "mtc0 "+regrt+","+regrc;
    if(rs==0) return "mfc0 "+regrt+","+regrc;
    return "error";
}
string reasmJ(int code){
    int op=(code & 0xFC000000)>>26;
    int addr=(code & 0x03FFFFFF);
    if(op==2) return "j "+num2str(addr);
    if(op==3) return "jal "+num2str(addr);
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
    if(rtype==1) return opname+" "+regName(rd)+","+regName(rs)+","+regName(sa);
    if(rtype==2) return opname+" "+regName(rs);
    if(rtype==3) return opname+" "+regName(rs)+","+regName(rd);
    if(rtype==0) return opname+" "+regName(rd)+","+regName(rs)+","+regName(rt);
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
    if(itype==0) return opname+" "+regName(rt)+","+regName(rs)+","+num2str(dat);
    if(itype==1) return opname+" "+regName(rt)+","+regName(dat)+"("+regName(rs)+")";
    if(itype==2) return opname+" "+regName(rs)+","+regName(rt)+","+num2str(ofs);
    if(itype==3) return opname+" "+regName(rs)+","+regName(ofs);
    if(itype==4) return opname+" "+regName(rt)+","+regName(rs)+","+num2str(dot);
    return "error";
}
