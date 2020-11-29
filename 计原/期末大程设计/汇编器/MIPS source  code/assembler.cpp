#include "assembler.h"
#include <math.h>
#include <cmath>

Assembler::Assembler()
{
    KeyCode = QMap<QString, QString>({
        {"add",     "000000ssssstttttddddd00000100000"},
        {"addu",    "000000ssssstttttddddd00000100001"},
        {"and",     "000000ssssstttttddddd00000100100"},
        {"nor",     "000000ssssstttttddddd00000100111"},
        {"or",      "000000ssssstttttddddd00000100101"},
        {"sub",     "000000ssssstttttddddd00000100010"},
        {"subu",    "000000ssssstttttddddd00000100011"},
        {"xor",     "000000ssssstttttddddd00000100110"},
        {"slt",     "000000ssssstttttddddd00000101010"},
        {"sltu",    "000000ssssstttttddddd00000101011"},
        {"sllv",    "000000ssssstttttddddd00000000100"},
        {"srlv",    "000000ssssstttttddddd00000000110"},
        {"srav",    "000000ssssstttttddddd00000000111"},

        {"addi",    "001000ssssstttttiiiiiiiiiiiiiiii"},
        {"addiu",   "001001ssssstttttiiiiiiiiiiiiiiii"},
        {"andi",    "001100ssssstttttiiiiiiiiiiiiiiii"},
        {"ori",     "001101ssssstttttiiiiiiiiiiiiiiii"},
        {"xori",    "001110ssssstttttiiiiiiiiiiiiiiii"},
        {"slti",    "001010ssssstttttiiiiiiiiiiiiiiii"},
        {"sltiu",   "001001ssssstttttiiiiiiiiiiiiiiii"},

        {"sll",     "00000000000tttttdddddaaaaa000000"},
        {"srl",     "00000000000tttttdddddaaaaa000010"}, 
        {"sra",     "00000000000tttttdddddaaaaa000011"},
        
        {"beq",     "000100ssssstttttiiiiiiiiiiiiiiii"},
        {"bne",     "000101ssssstttttiiiiiiiiiiiiiiii"},

        {"j",       "000010iiiiiiiiiiiiiiiiiiiiiiiiii"},
        {"jal",     "000011iiiiiiiiiiiiiiiiiiiiiiiiii"},

        {"jr",      "000000sssss000000000000000001000"},

        {"lw",      "100011ssssstttttiiiiiiiiiiiiiiii"},
        {"lwx",     "100010ssssstttttiiiiiiiiiiiiiiii"},
        {"lh",      "100001ssssstttttiiiiiiiiiiiiiiii"},
        {"lhx",     "100000ssssstttttiiiiiiiiiiiiiiii"},
        {"lhu",     "100101ssssstttttiiiiiiiiiiiiiiii"},
        {"lhux",    "100100ssssstttttiiiiiiiiiiiiiiii"},
        {"sw",      "101011ssssstttttiiiiiiiiiiiiiiii"},
        {"swx",     "101010ssssstttttiiiiiiiiiiiiiiii"},
        {"sh",      "101001ssssstttttiiiiiiiiiiiiiiii"},
        {"shx",     "101000ssssstttttiiiiiiiiiiiiiiii"},
        
        {"jalr",    "000000sssss00000ddddd00000001001"},

        {"lui",     "00111100000tttttiiiiiiiiiiiiiiii"},
        
        {"bgezal",  "000001sssss10001iiiiiiiiiiiiiiii"}, //offest

        {"mfc0",    "01000000000tttttddddd00000000000"},
        {"mtc0",    "01000000100tttttddddd00000000000"},

        {"eret",    "01000010000000000000000000011000"},
        {"syscall", "00000000000000000000000000001100"},
    });

    Register = QMap<QString,QString>({
        {"$zero","00000"},
        {"$at","00001"},
        {"$v0","00010"},
        {"$v1","00011"},
        {"$a0","00100"},
        {"$a1","00101"},
        {"$a2","00110"},
        {"$a3","00111"},
        {"$t0","01000"},
        {"$t1","01001"},
        {"$t2","01010"},
        {"$t3","01011"},
        {"$t4","01100"},
        {"$t5","01101"},
        {"$t6","01110"},
        {"$t7","01111"},
        {"$s0","10000"},
        {"$s1","10001"},
        {"$s2","10010"},
        {"$s3","10011"},
        {"$s4","10100"},
        {"$s5","10101"},
        {"$s6","10110"},
        {"$s7","10111"},
        {"$t8","11000"},
        {"$t9","11001"},
        {"$k0","11010"},
        {"$k1","11011"},
        {"$gp","11100"},
        {"$sp","11101"},
        {"$fp","11110"},
        {"$ra","11111"}
     });
    STD_Instruction << "add" << "addu" << "and" << "nor" << "or" << "sub" << "subu" << "xor" << "slt" << "sltu" << "sllv" << "srlv" << "srav";
    TDA_Instruction << "sll" << "srl" << "sra";
    S___Instruction << "jr";
    STI_Instruction << "addi" << "addiu" << "andi" << "ori" << "xori" << "slti" << "sltiu";
    STII_Instruction << "sw" << "lw" << "lwx" << "lh" << "lhx" << "lhu" << "lhux" << "swx" <<"sh" << "shx";
    J_Instruction << "j" << "jal";
    BSTI_Instruction << "beq" << "bne";
    
    S_D_Instruction << "jalr";
    TI_Instruction << "lui";
    S_I_Instruction << "bgezal";
    TD_Instruction << "mfc0" << "mtc0";
    SYS_Instruction << "erec" << "syscall";
    Pseudo_Instruction << "push" << "pop" << "move" << "shi" << "shix" << "inc" << "dec" 
                       << "not" << "neg" << "abs" << "swap" << "beqz" << "bnez" << "beqi" 
                       << "bnei" << "blt" << "ble" << "bgt" << "bge" << "seq" << "sne";
 }

/*编译指令*/
QString Assembler::Compile(QString &CompileString)
{
    bool ok;
    int addr = 0;
    QChar comment = '#', labelI = ':', sep = '\n';
    QString label, thisvalidLine, InstructionLine;
    QStringList CompileList = CompileString.split(sep);
    QListIterator<QString> iterator(CompileList);
    resultList.clear();
    LabelAddr.clear();
    InstructionAddr.clear();

    while (iterator.hasNext())
    {
        QString thisLine  = iterator.next();
        
        // 检查是否有标签或注释
        int commentIndex = thisLine.indexOf(comment, 0);
        int labelIndex = thisLine.indexOf(labelI, 0);
        // 没有标签
        if(labelIndex == -1){
            thisvalidLine = thisLine.left(commentIndex); // 获取指令
        }
        // 有标签
        else{
            label = thisLine.left(labelIndex); // 获取标签
            LabelAddr.insert(label, QString::number(addr, 10)); // 保存标签地址
            thisvalidLine = GetSubstring(thisLine.left(commentIndex), labelIndex+1); // 获取指令
        }

        thisvalidLine.replace("(", " ");
        thisvalidLine.replace(")", "");
        thisvalidLine.replace(";", "");
        InstructionAddr.insert(thisvalidLine, addr); // 保存指令地址

        QStringList assembledLines = CompleteMachineCode(thisvalidLine);

        for(int i = 0;i<assembledLines.size();i++){
            // 输出指令地址+16进制的指令
            assembledLines[i] = QString("%1").arg(addr, 4, 10, QChar('0')) + ": " + QString("%1").arg(assembledLines[i].toLongLong(&ok, 2), 8, 16, QChar('0'));
            resultList.append(assembledLines[i]);
            addr += 4;
        }

        /*if (!assembledLine.isEmpty())
        {
            // 输出指令地址+16进制的指令
            assembledLine = QString("%1").arg(addr, 4, 10, QChar('0')) + ": " + QString("%1").arg(assembledLine.toLongLong(&ok, 2), 8, 16, QChar('0'));
            resultList.append(assembledLine);
        }*/
    }
    return Join_enter(resultList);
}

/*从字符串指定位置开始截取子串*/
QString Assembler::GetSubstring(QString input, int beginposition)
{
    int i;
    QString result = "";
    for(i = beginposition; i < input.length(); i++){
        result = result + input[i];
    }
    return result;
}

/*将offset转化成补码*/
QString Assembler::convertTocomplement(int offset){
    int i, Index = 0;
    QString Bin;
    offset = fabs(offset);
    Bin = QString("%1").arg(offset, 16, 2, QChar('0'));
    for(i = Bin.length() - 1; i >= 0; i--){
        if(Bin[i] == '1'){
            Index = i;
            break;
        }
    }
    for(i = 0; i < Index; i++){
        if(Bin[i] == '1'){
            Bin[i] = '0';
        }
        else{
            Bin[i] = '1';
        }
    }
    return Bin;
}

/*判断指令格式*/
int Assembler::Case_contained(QString& Op){
    int Case = -1;
    if(STD_Instruction.contains(Op)){
        Case = 0;
    }
    else if(TDA_Instruction.contains(Op)){
        Case = 1;
    }
    else if(S___Instruction.contains(Op)){
        Case = 2;
    }
    else if(STI_Instruction.contains(Op)){
        Case = 3;
    }
    else if(STII_Instruction.contains(Op)){
        Case = 4;
    }
    else if(J_Instruction.contains(Op)){
        Case = 5;
    }
    else if(BSTI_Instruction.contains(Op)){
        Case = 6;
    }
    else if(S_D_Instruction.contains(Op)){
        Case = 7;
    }
    else if(TI_Instruction.contains(Op)){
        Case = 8;
    }
    else if(S_I_Instruction.contains(Op)){
        Case = 9;
    }
    else if(TD_Instruction.contains(Op)){
        Case = 10;
    }
    else if(SYS_Instruction.contains(Op)){
        Case = 11;
    }
    else if(Pseudo_Instruction.contains(Op)){
        Case = 12;
    }
    return Case;
}

/*将指令按行存入列表*/
QStringList Assembler::Split_enter(QString &CompileString)
{
    QChar sep = '\n';
    QStringList my_stringlist = CompileString.split(sep);
    return my_stringlist;
}

/*给指令末尾加上换行符*/
QString Assembler::Join_enter(QStringList &AssembledStringList)
{
    AssembledString = AssembledStringList.join("\n");
    return AssembledString;
}

/*编译指令*/
QStringList Assembler::CompleteMachineCode(QString thisLine)
{
    int Case = -1;
    QString Op;
    QString machineCode;
    QStringList Result;
    if (thisLine.isEmpty()){
        return Result;
    }
    QStringList my_stringlist = thisLine.split(QRegExp("(\\s|,)"), QString::SkipEmptyParts);
    // 获取指令名称
    Op = my_stringlist.at(0);
    // 获取指令类型
    Case = Case_contained(Op);
    // 获得指令的机器码
    machineCode = KeyCode[my_stringlist.at(0)];
    switch(Case)
    {
        // 得到指令各部分的值
        case 0:
            change_d(my_stringlist.at(1), machineCode);
            change_s(my_stringlist.at(2), machineCode);
            change_t(my_stringlist.at(3), machineCode);
            Result << machineCode;
            break;
        case 1:
            change_d(my_stringlist.at(1), machineCode);
            change_t(my_stringlist.at(2), machineCode);
            change_a(my_stringlist.at(3), machineCode);
            Result << machineCode;
            break;
        case 2:
            change_s(my_stringlist.at(1), machineCode);
            Result << machineCode;
            break;
        case 3:
            change_t(my_stringlist.at(1), machineCode);
            change_s(my_stringlist.at(2), machineCode);
            change_i(my_stringlist.at(3), machineCode);
            Result << machineCode;
            break;
        case 4:
            change_t(my_stringlist.at(1), machineCode);
            change_s(my_stringlist.at(3), machineCode);
            change_i(my_stringlist.at(2), machineCode);
            Result << machineCode;
            break;
        case 5:
            change_target(my_stringlist.at(1), machineCode);
            Result << machineCode;
            break;
        case 6:
            change_t(my_stringlist.at(1), machineCode);
            change_s(my_stringlist.at(2), machineCode);
            change_labelori(thisLine, my_stringlist.at(3), machineCode);
            Result << machineCode;
            break;
        case 7:
            change_t(my_stringlist.at(1), machineCode);
            change_d(my_stringlist.at(2), machineCode);
            Result << machineCode;
            break;
        case 8:
            change_t(my_stringlist.at(1), machineCode);
            change_i(my_stringlist.at(2), machineCode);
            Result << machineCode;
            break;
        case 9:
            change_s(my_stringlist.at(1), machineCode);
            change_i(my_stringlist.at(2), machineCode);
            Result << machineCode;
            break;
        case 10:
            change_t(my_stringlist.at(1), machineCode);
            change_d(my_stringlist.at(2), machineCode);
            Result << machineCode;
            break;
        case 11:
            Result << machineCode;
            break;
        case 12:
            Result = CompilePseudo(my_stringlist, thisLine);
            break;
    }
    return Result;
}

QStringList Assembler::CompilePseudo(QStringList& my_stringlist, QString thisLine){
    QString Op = my_stringlist.at(0);
    QString machineCode;
    QStringList Result;

    if (Op == "push"){ // push $r1
        // addi $sp, $sp, -2
        machineCode = KeyCode["addi"];
        change_t("$sp", machineCode);
        change_s("$sp", machineCode);
        change_i("-2", machineCode);
        Result << machineCode;
        // sw $r1, 0($sp)
        machineCode = KeyCode["sw"];
        change_t(my_stringlist.at(1), machineCode);
        change_s("$sp", machineCode);
        change_i("0", machineCode);
        Result << machineCode;
    }
    else if (Op == "pop"){ // pop $r1
        // lw $r1, 0($sp)
        machineCode = KeyCode["lw"];
        change_t(my_stringlist.at(1), machineCode);
        change_s("$sp", machineCode);
        change_i("0", machineCode);
        Result << machineCode;
        // addi $sp, $sp, 2
        machineCode = KeyCode["addi"];
        change_t("$sp", machineCode);
        change_s("$sp", machineCode);
        change_i("2", machineCode);
        Result << machineCode;
    }
    else if (Op == "move"){ // move $r1, $r2
        // or $r1, $r2, $zero
        machineCode = KeyCode["or"];
        change_d(my_stringlist.at(1), machineCode);
        change_s(my_stringlist.at(2), machineCode);
        change_t("$zero", machineCode);
        Result << machineCode;
    }
    else if (Op == "shi"){ // shi $r1,$r2,$r3
        // addi $at, $zero, $r1
        machineCode = KeyCode["addi"];
        change_t("$at", machineCode);
        change_s("$zero", machineCode);
        change_i(my_stringlist.at(1), machineCode);
        Result << machineCode;
        // sh $at,$r2($r3)
        machineCode = KeyCode["sh"];
        change_t("$at", machineCode);
        change_s(my_stringlist.at(2), machineCode);
        change_i(my_stringlist.at(3), machineCode);
        Result << machineCode;
    }
    else if (Op == "shix"){
        // addi $at, $zero, $r1
        machineCode = KeyCode["addi"];
        change_t("$at", machineCode);
        change_s("$zero", machineCode);
        change_i(my_stringlist.at(1), machineCode);
        Result << machineCode;
        // shx $at,$r2($r3)
        machineCode = KeyCode["shx"];
        change_t("$at", machineCode);
        change_s(my_stringlist.at(2), machineCode);
        change_i(my_stringlist.at(3), machineCode);
        Result << machineCode;
    }
    else if (Op == "inc"){ // inc $r1
        // addi $r1,$r1,1
        machineCode = KeyCode["addi"];
        change_t(my_stringlist.at(1), machineCode);
        change_s(my_stringlist.at(1), machineCode);
        change_i("1", machineCode);
        Result << machineCode;
    }
    else if (Op == "dec"){
         // addi $r1,$r1,-1
        machineCode = KeyCode["addi"];
        change_t(my_stringlist.at(1), machineCode);
        change_s(my_stringlist.at(1), machineCode);
        change_i("-1", machineCode);
        Result << machineCode;
    }
    else if (Op == "not"){ // not $r1,$r2
        // nor $r1,$r2,$r2
        machineCode = KeyCode["nor"];
        change_d(my_stringlist.at(1), machineCode);
        change_s(my_stringlist.at(2), machineCode);
        change_t(my_stringlist.at(2), machineCode);
        Result << machineCode;
    }
    else if (Op == "neg"){ //neg $r1,$r2
        // sub $r1,$zero,$r2
        machineCode = KeyCode["sub"];
        change_d(my_stringlist.at(1), machineCode);
        change_s("$zero", machineCode);
        change_t(my_stringlist.at(2), machineCode);
        Result << machineCode;
    }
    else if (Op == "abs"){ // abs $r1,$r2
        // sra $at,$r2,31
        machineCode = KeyCode["sra"];
        change_d("$at", machineCode);
        change_t(my_stringlist.at(2), machineCode);
        change_a("31", machineCode);
        Result << machineCode;
        // xor $r1,$r2,$at
        machineCode = KeyCode["xor"];
        change_d(my_stringlist.at(1), machineCode);
        change_s(my_stringlist.at(2), machineCode);
        change_t("$at", machineCode);
        Result << machineCode;
        // sub $r1,$r1,$at
        machineCode = KeyCode["sub"];
        change_d(my_stringlist.at(1), machineCode);
        change_s(my_stringlist.at(1), machineCode);
        change_t("$at", machineCode);
        Result << machineCode;
    }
    else if (Op == "swap"){ // swap $r1,$r2
        // xor $r1,$r1,$r2
        machineCode = KeyCode["xor"];
        change_d(my_stringlist.at(1), machineCode);
        change_s(my_stringlist.at(1), machineCode);
        change_t(my_stringlist.at(2), machineCode);
        Result << machineCode;
        // xor $r2,$r1,$r2
        machineCode = KeyCode["xor"];
        change_d(my_stringlist.at(2), machineCode);
        change_s(my_stringlist.at(1), machineCode);
        change_t(my_stringlist.at(2), machineCode);
        Result << machineCode;
        // xor $r1,$r1,$r2
        machineCode = KeyCode["xor"];
        change_d(my_stringlist.at(1), machineCode);
        change_s(my_stringlist.at(1), machineCode);
        change_t(my_stringlist.at(2), machineCode);
        Result << machineCode;
    }
    else if (Op == "beqz"){ // beqz $r1,$r2
        // beq $r1,$zero,$r2
        machineCode = KeyCode["beq"];
        change_t(my_stringlist.at(1), machineCode);
        change_s("$zero", machineCode);
        change_labelori(thisLine, my_stringlist.at(2), machineCode);
        Result << machineCode;
    }
    else if (Op == "bnez"){ // bnez $r1, $r2
        // bne $r1,$zero,$r2
        machineCode = KeyCode["bne"];
        change_t(my_stringlist.at(1), machineCode);
        change_s("$zero", machineCode);
        change_labelori(thisLine, my_stringlist.at(2), machineCode);
        Result << machineCode;
    }
    else if (Op == "beqi"){ // beqi $r1,$r2,$r3
        // addi $at,$zero,$r2
        machineCode = KeyCode["addi"];
        change_t("$at", machineCode);
        change_s("$zero", machineCode);
        change_i(my_stringlist.at(2), machineCode);
        Result << machineCode;
        // beq $at,$r1,$r3
        machineCode = KeyCode["beq"];
        change_t("$at", machineCode);
        change_s(my_stringlist.at(1), machineCode);
        change_labelori(thisLine, my_stringlist.at(3), machineCode);
        Result << machineCode;
    }
    else if (Op == "bnei"){
        // addi $at,$zero,$r2
        machineCode = KeyCode["addi"];
        change_t("$at", machineCode);
        change_s("$zero", machineCode);
        change_i(my_stringlist.at(2), machineCode);
        Result << machineCode;
        // bne $at,$r1,$r3
        machineCode = KeyCode["bne"];
        change_t("$at", machineCode);
        change_s(my_stringlist.at(1), machineCode);
        change_labelori(thisLine, my_stringlist.at(3), machineCode);
        Result << machineCode;
    }
    else if (Op == "blt"){ // blt $r1,$r2,$r3
        // slt $at,$r1,$r2
        machineCode = KeyCode["slt"];
        change_d("$at", machineCode);
        change_s(my_stringlist.at(1), machineCode);
        change_t(my_stringlist.at(2), machineCode);
        Result << machineCode;
        // bne $at,$zero,$r3
        machineCode = KeyCode["bne"];
        change_t("$at", machineCode);
        change_s("$zero", machineCode);
        change_labelori(thisLine, my_stringlist.at(3), machineCode);
        Result << machineCode;
    }
    else if (Op == "ble"){
        // slt $at,$r2,$r1
        machineCode = KeyCode["slt"];
        change_d("$at", machineCode);
        change_s(my_stringlist.at(2), machineCode);
        change_t(my_stringlist.at(1), machineCode);
        Result << machineCode;
        // beq $at,$zero,$r3
        machineCode = KeyCode["beq"];
        change_t("$at", machineCode);
        change_s("$zero", machineCode);
        change_labelori(thisLine, my_stringlist.at(3), machineCode);
        Result << machineCode;
    }
    else if (Op == "bgt"){
        // slt $at,$r2,$r1
        machineCode = KeyCode["slt"];
        change_d("$at", machineCode);
        change_s(my_stringlist.at(2), machineCode);
        change_t(my_stringlist.at(1), machineCode);
        Result << machineCode;
        // bne $at,$zero,$r3
        machineCode = KeyCode["bne"];
        change_t("$at", machineCode);
        change_s("$zero", machineCode);
        change_labelori(thisLine, my_stringlist.at(3), machineCode);
        Result << machineCode;
    }
    else if (Op == "bge"){
        // slt $at,$r1,$r2
        machineCode = KeyCode["slt"];
        change_d("$at", machineCode);
        change_s(my_stringlist.at(1), machineCode);
        change_t(my_stringlist.at(2), machineCode);
        Result << machineCode;
        // beq $at,$zero,$r3
        machineCode = KeyCode["beq"];
        change_t("$at", machineCode);
        change_s("$zero", machineCode);
        change_labelori(thisLine, my_stringlist.at(3), machineCode);
        Result << machineCode;
    }
    else if (Op == "seq"){ // seq $r1,$r2,$r3
        // sub $r1,$r2,$r3
        machineCode = KeyCode["sub"];
        change_d(my_stringlist.at(1), machineCode);
        change_s(my_stringlist.at(1), machineCode);
        change_t(my_stringlist.at(3), machineCode);
        Result << machineCode;
        // sltiu $r1,$r2,1
        machineCode = KeyCode["sltiu"];
        change_t(my_stringlist.at(1), machineCode);
        change_s(my_stringlist.at(2), machineCode);
        change_i("1", machineCode);
        Result << machineCode;
    }
    else if (Op == "sne"){
        // sub $r1,$r2,$r3
        machineCode = KeyCode["sub"];
        change_d(my_stringlist.at(1), machineCode);
        change_s(my_stringlist.at(1), machineCode);
        change_t(my_stringlist.at(3), machineCode);
        Result << machineCode;
        // sltu $r1,$r2,$r1
        machineCode = KeyCode["sltu"];
        change_d(my_stringlist.at(1), machineCode);
        change_s("$zero", machineCode);
        change_t(my_stringlist.at(1), machineCode);
        Result << machineCode;
    }

    return Result;
}

/*将指令的指定部分填入指定寄存器的编号*/
void Assembler::change_s(const QString& rs, QString& to_machinecode)
{
    QString RegSCode = Register[rs];
    to_machinecode.replace(6, 5, RegSCode);
}

void Assembler::change_t(const QString& rt, QString& to_machinecode)
{
    QString RegTCode = Register[rt];
    to_machinecode.replace(11, 5, RegTCode);
}

void Assembler::change_d(const QString& rd, QString& to_machinecode)
{
    QString RegDCode = Register[rd];
    to_machinecode.replace(16, 5, RegDCode);
}

void Assembler::change_a(const QString& sa, QString& to_machinecode)
{
    QString RegACode = Register[sa];
    to_machinecode.replace(21, 5, RegACode);
}

void Assembler::change_labelori(QString& thisLine, const QString& label, QString& to_machinecode){
    bool ok;
    int offset, PC;
    QString labelcode;
    QString ImmediateCode;
    offset = label.toInt(&ok, 10);

    // label 是整数
    if(ok == true){
        offset = offset / 4;
        if(offset > 0){
            ImmediateCode = QString("%1").arg(offset, 16, 2, QChar('0'));
        }
        else{
            ImmediateCode = convertTocomplement(offset);
        }
        to_machinecode.replace(16, 16, ImmediateCode);
    }
    // label是标签
    else{
        int label_addr = LabelAddr[label].toInt(&ok, 16);
        PC = InstructionAddr[thisLine];
        offset = (label_addr - 4 - PC) / 4;
        if(offset > 0){
            labelcode = QString("%1").arg(offset, 16, 2, QChar('0'));
        }
        else{
            labelcode = convertTocomplement(offset);
        }
        to_machinecode.replace(16, 16, labelcode);
    }
}

/*立即数*/
void Assembler::change_i(const QString& imm, QString& to_machinecode)
{
    QString ImmediateCode;
    int offset = imm.toInt();
    if(offset > 0){
        ImmediateCode = QString("%1").arg(offset, 16, 2, QChar('0'));
    }
    else{
        ImmediateCode = convertTocomplement(offset);
    }
    to_machinecode.replace(16, 16, ImmediateCode);
}

void Assembler::change_target(const QString& target, QString& to_machinecode)
{
    bool ok;
    QString TargetCode;
    long long resultint = target.toLongLong(&ok, 10);
    if(ok == true){
        resultint = resultint / 4;
        TargetCode = QString("%1").arg(resultint, 26, 2, QChar('0'));
    }
    else{
        resultint = LabelAddr[target].toLongLong(&ok, 10) / 4;
        TargetCode = QString("%1").arg(resultint, 26, 2, QChar('0'));
    }
    to_machinecode.replace(6, 26, TargetCode);
}
