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
	for(int i=0;i<s.length()-1;i++){
		if(s[i]==' ' && s[i+1]==' '){
			s.erase(s.begin()+i);
		}
	}
	int first=1;
	for(int i=0;i<s.length();i++){
		if(s[i]==' '){
			if(first){
				first=0;
			}else{
				s.erase(s.begin()+i);
				i--;
			}
		}
	}
	for(int i=0;i<s.length();i++){
		if(s[i]==' '){
			s[i]=',';
		}
	}
	return s;
}

int regs[32];
int memory[1<<20];
int PC=0;
map<string,int> reg2ind;
map<int,string> ind2reg;

Instruction::Instruction(string instr){
	string instr_processed=prepare(instr);
	cout<<instr_processed<<endl;
	opms=strSplit(instr_processed,',');		
}
Instruction::Instruction(){
	
}
Instruction::~Instruction(){

}

vector<Instruction> instrs;

vector<Label> labels;

void initial(){

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
		executeJ(instr);
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

	}else if(instr.opms[0]=="jalr"){

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
	int rt,dat,rs;
	rt=regIndex(instr.opms[1]);
	dat=stoi(instr.opms[2]);
	rs=regIndex(strInBrackets(instr.opms[2]));
	if(instr.opms[0]=="lui"){
		regs[rt]=dat<<16;
	}else if(instr.opms[0]=="lw"){
		regs[rt]=memory[regs[rs]+dat];
	}else if(instr.opms[0]=="lwx"){
		regs[rt]=memory[regs[rs]+dat];
	}else if(instr.opms[0]=="lh"){

	}else if(instr.opms[0]=="lhx"){

	}else if(instr.opms[0]=="lhu"){

	}else if(instr.opms[0]=="lhux"){

	}else if(instr.opms[0]=="sw"){

	}else if(instr.opms[0]=="swx"){

	}else if(instr.opms[0]=="sh"){

	}else if(instr.opms[0]=="shx"){

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

	else if(op=="j"){
		return 6;
	}else if(op=="jal"){
		return 6;
	}

	else if(op=="mfc0"){
		return 7;
	}else if(op=="mtc0"){
		return 7;
	}else if(op=="eret"){
		return 7;
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