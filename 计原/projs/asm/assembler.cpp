#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<cstdlib>
#define max_instr_len 100
#define D(x) cout<<#x<<": "<<x<<endl
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

int regNum(string regName){
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
int regNum2(string regName){
	return -1;
}

int shamtNum(string op){
	if(op=="add") return 0;
	if(op=="sub") return 0;
	if(op=="slt") return 0;
	if(op=="sltu") return 0;
	if(op=="and") return 0;
	if(op=="or") return 0;
	if(op=="xor") return 0;
	if(op=="nor") return 0;
	if(op=="sll") return -1;
	if(op=="sllv") return 0;
	if(op=="srl") return -1;
	if(op=="srlv") return 0;
	if(op=="sra") return -1;
	if(op=="srav") return 0;
	if(op=="syscall") return 0;
	return -1;
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
	char str[s.length()+1];
	for(int i=0;i<s.length();i++){
		str[i]=s[i];
	}
	str[s.length()]='\0';
	sscanf(str,"%d",&res);
	return res;
}

string strInBracks(string s){
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

int translateR(int op, vector<string> instr){
	int res;
	int rs,rt,rd,sa,func;
	if(instr.size()==1 && instr[0]=="syscall"){
		return 12;
	}
	if(instr.size()==2 && instr[0]=="jr"){
		rs=regNum(instr[1]);
		rt=rd=sa=0;
		func=8;
		res=op<<26|rs<<21|rt<<16|rd<<11|sa<<6|func;
		return res;
	}
	if(instr.size()==3 && instr[0]=="jalr"){
		rs=regNum(instr[1]);
		rd=regNum(instr[2]);
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
		rt=regNum(instr[3]);
		sa=0;
	}
	rs=regNum(instr[2]);
	rd=regNum(instr[1]);
	
	res=op<<26|rs<<21|rt<<16|rd<<11|sa<<6|func;
	return res;
}
int translateI(int op, vector<string> instr){
	int res;
	int rs,rt,immed;
	if(instr.size()==3){
		if(instr[0]=="bgezal"){
			rs=regNum(instr[1]);
			rt==17;
			immed=str2num(instr[2]);
			immed=immed & 0xFFFF;
			res=op<<26|rs<<21|rt<<16|immed;
			return res;
		}
		rt=regNum(instr[1]);
		immed=str2num(instr[2]);
		if(instr[0]=="lui"){
			rs=0;
		}else{
			rs=regNum(strInBracks(instr[2]));
		}
		immed=immed & 0xFFFF;
		res=op<<26|rs<<21|rt<<16|immed;
		return res;
	}
	if(instr.size()!=4){
		return -1;
	}
	rt=regNum(instr[1]);
	rs=regNum(instr[2]);
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
	rt=regNum(instr[1]);
	rc=regNum2(instr[2]);
	res=op<<26|rt<<16|rc<<11;
	return res;
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

void printInBin(unsigned n){
	int bin[32];
	for(int i=31;i>=0;i--){
		bin[i]=n%2;
		n/=2;
	}
	for(int i=0;i<32;i++){
		cout<<bin[i];
		if((i+1)%4==0){
			cout<<' ';
		}
	}
}

void process(string instr){
	string instr_processed=prepare(instr);
	cout<<instr_processed<<endl;
	vector<string> opms=strSplit(instr_processed,',');
	for(int i=0;i<opms.size();i++){
		cout<<"opm"<<i<<": "<<opms[i]<<endl;
	}
	int res=translate(instr);
	printf("res in hex: 0x%08X\n",res);
	printf("res in dec: %d\n",res);
	cout<<"res in bin: ";
	printInBin(res);
	cout<<endl;
}

int main(){
	string instr=" addi  $sp ,$sp, -6  ";
	char str[max_instr_len];
	while(gets(str) && strcmp(str,"")){
		string instr(str,strlen(str));
		process(instr);
	}

	system("pause");
	return 0;
}