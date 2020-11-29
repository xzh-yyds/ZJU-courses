#include "sim.h"
#include <sstream>

void errorHint(string msg){
    cout << "Error: " << msg << endl;
}

void inputHint(){
    cout << "Type in: ";
    cout << " 0:load data";
    cout << "  1:run";
    cout << "  2:step";
    cout << "  3:status";
    cout << "  4:again";
    cout << "  5:exit" << endl;
}

void Hint(string msg) {
    cout << "Message: " << msg << endl;
}

Sim::Sim() {
    memset(Memory, 0, sizeof(Memory));
    memset(regs, 0, sizeof(regs));
    PC = 0;
    entry = 0;
}

Sim::~Sim() {

}

void Sim::Start() {
    int cmd = -1;
    inputHint();
    cin >> cmd;
    while (cmd != CMD_EXIT) {
        if (cmd == CMD_LDINS) {
            int mode = 0;
            cout << "Data type: 0:Bin  1:Instruction" << endl;
            cin >> mode;
            int pos = 0;
            cout << "Position: ";
            cin >> pos;
            if (mode == 0) {
                vector<unsigned char> bin8s;
                string line;
                cout << "Hexadecimal int8s end with \"#\": " << endl;
                getline(cin, line);
                while (line != "#") {
                    if (line != "") {
                        unsigned char bin = hexstr2int8(line);
                        bin8s.push_back(bin);
                    }
                    getline(cin, line);
                }
                LoadBin(bin8s, pos);
                Hint("Successfully loaded!");
            } 
            else if (mode == 1) {
                vector<int> bin32s;
                string line;
                cout << "Instructions end with \"#\": " << endl;
                getline(cin, line);
                vector<string> codes;// = strSplit(line, '\n');
                while (line != "#") {
                    if (line != "")
                        codes.push_back(line);
                    getline(cin, line);
                }
                //if (codes.back() == "#") codes.pop_back();
                vector<Instr> irs = MultiTranslate(codes);
                bin32s = Instrs2Bin32s(irs);
                LoadInstr(bin32s, pos);
                Hint("Successfully loaded!");
            }
            else {
                Hint("Illegal input.");
            }
        } 
        else if (cmd == CMD_RUN) {
            cout << "->run" << endl;
            Run();
            ShowStatus();
        }
        else if (cmd == CMD_STEP) {
            cout << "->step" << endl;
            Step();
            ShowStatus();
        }
        else if (cmd == CMD_STATUS) {
            ShowStatus();
        }
        else if (cmd == CMD_AGAIN) {
            Again();
            Hint("PC has been reset successfully!");
        }
        else {
            Hint("Illegal input! Try again.");
        }
        inputHint();
        cin >> cmd;
    }
    ShutDown();
}

void Sim::LoadInstr(vector<int> bin32s, int ofs) {
    int base = ofs;
    //this->entry = base;
    char* p = (char*)Memory + base;
    int b0, b1, b2, b3;

    for (int i = 0; i < (int)bin32s.size(); i++) {
        int bin32 = bin32s[i];
        b3 = (bin32 & 0xFF000000)>>24;
        b2 = (bin32 & 0x00FF0000)>>16;
        b1 = (bin32 & 0x0000FF00)>>8;
        b0 = (bin32 & 0x000000FF);
        *(int*)p = b0 << 24 | b1 << 16 | b2 << 8 | b3;
        p = p + 4;
    }
    //this->PC = this->entry;
}

void Sim::LoadBin(vector<unsigned char> bin8s, int ofs) {
    int base = ofs;
    //this->entry = base;
    unsigned char* p = Memory + base;
    //int b0, b1, b2, b3;

    for (int i = 0; i < (int)bin8s.size(); i++) {
        *p = bin8s[i];
        p = p + 1;
    }
    //this->PC = this->entry;
}

Instr Sim::FetchInstr() {
    int* addr = (int*)(Memory + PC);
    int bin32 = *addr;
    PC = PC + sizeof(word);
    int b0, b1, b2, b3;
    b3 = (bin32 & 0xFF000000)>>24;
    b2 = (bin32 & 0x00FF0000)>>16;
    b1 = (bin32 & 0x0000FF00)>>8;
    b0 = (bin32 & 0x000000FF);
    int ir = b0 << 24 | b1 << 16 | b2 << 8 | b3;
    return Instr(ir);
}

Instr Sim::GetNextInstr() {
    int* addr = (int*)(Memory + PC);
    int bin32 = *addr;
    int b0, b1, b2, b3;

    b3 = (bin32 & 0xFF000000) >> 24;
    b2 = (bin32 & 0x00FF0000) >> 16;
    b1 = (bin32 & 0x0000FF00) >> 8;
    b0 = (bin32 & 0x000000FF);
    int ir = b0 << 24 | b1 << 16 | b2 << 8 | b3;
    return Instr(ir);
}

void Sim::Step() {
    Instr ins = FetchInstr();
    if (ins.toBin() == 0) {
        cout << "End!" << endl;
        return;
    }
    Execute(ins);
}

void Sim::Run() {
    Instr ir = FetchInstr();
    while (ir.toBin() != 0) {
        Execute(ir);
        ir = FetchInstr();
    }
    cout << "Finished" << endl;
}

void Sim::PrintRegs() {
    for (int i = 0; i < REG_NUM / 4; i++) {
        printf("%5s: 0x%08X  ", regName[i].c_str(), regs[i]);
        printf("%5s: 0x%08X  ", regName[i + 8].c_str(), regs[i + 8]);
        printf("%5s: 0x%08X  ", regName[i + 16].c_str(), regs[i + 16]);
        printf("%5s: 0x%08X", regName[i + 24].c_str(), regs[i + 24]);
        cout << endl;
    }
    // cout << endl;
}

void Sim::ShowStatus() {
    PrintRegs();
    string next_ir = GetNextInstr().all;
    cout << "The next instruction: " << next_ir << endl;
}

void Sim::Again() {
    this->PC = this->entry;
}

void Sim::ShutDown() {
    cout << "Bye~" << endl;
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
        break;
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
    dat = stoi(ir.args[3]);
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
            PC += ofs<<2;
        }
    }
    else if(ir.args[0] == "bne"){
        if(regs[rt] != regs[rs]){
            int off = ofs << 2;
            PC = PC + off;
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

int RIJC(string op) {
    if (op == "add") {
        return RIJC_R1;
    } 
    else if (op == "sub") {
        return RIJC_R1;
    } 
    else if (op == "slt") {
        return RIJC_R1;
    } 
    else if (op == "sltu") {
        return RIJC_R1;
    } 
    else if (op == "and") {
        return RIJC_R1;
    } 
    else if (op == "or") {
        return RIJC_R1;
    } 
    else if (op == "xor") {
        return RIJC_R1;
    } 
    else if (op == "nor") {
        return RIJC_R1;
    } 
    else if (op == "sllv") {
        return RIJC_R1;
    } 
    else if (op == "srlv") {
        return RIJC_R1;
    } 
    else if (op == "srav") {
        return RIJC_R1;
    }

    else if (op == "sll") {
        return RIJC_R2;
    } else if (op == "srl") {
        return RIJC_R2;
    } else if (op == "sra") {
        return RIJC_R2;
    }

    else if (op == "jr") {
        return RIJC_R3;
    } else if (op == "jalr") {
        return RIJC_R3;
    } else if (op == "syscall") {
        return RIJC_R3;
    }

    else if (op == "addi") {
        return RIJC_I1;
    } else if (op == "slti") {
        return RIJC_I1;
    } else if (op == "sltiu") {
        return RIJC_I1;
    } else if (op == "andi") {
        return RIJC_I1;
    } else if (op == "ori") {
        return RIJC_I1;
    } else if (op == "xori") {
        return RIJC_I1;
    }

    else if (op == "lui") {
        return RIJC_I2;
    } else if (op == "lw") {
        return RIJC_I2;
    } else if (op == "lwx") {
        return RIJC_I2;
    } else if (op == "lh") {
        return RIJC_I2;
    } else if (op == "lhx") {
        return RIJC_I2;
    } else if (op == "lhux") {
        return RIJC_I2;
    } else if (op == "sw") {
        return RIJC_I2;
    } else if (op == "swx") {
        return RIJC_I2;
    } else if (op == "sh") {
        return RIJC_I2;
    } else if (op == "shx") {
        return RIJC_I2;
    }

    else if (op == "beq") {
        return RIJC_I3;
    } else if (op == "bne") {
        return RIJC_I3;
    }

    else if (op == "j") {
        return RIJC_J;
    } else if (op == "jal") {
        return RIJC_J;
    }

    else if (op == "mfc0") {
        return RIJC_C;
    } else if (op == "mtc0") {
        return RIJC_C;
    } else if (op == "eret") {
        return RIJC_C;
    }

    return -1;
}

unsigned char hexstr2int8(string s) {
    int bin32 = 0;
    stringstream ss;
    ss << s;
    ss >> hex >> bin32;
    unsigned char res = bin32;
    return res;
}
