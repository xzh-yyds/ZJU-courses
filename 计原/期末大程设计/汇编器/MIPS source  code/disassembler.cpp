#include "disassembler.h"
#include <math.h>
#include <cmath>

Disassembler::Disassembler()
{
    KeyOp = QMap<QString, QString>({
        {"000000100000",     "add"},
        {"000000100001",    "addu"},
        {"000000100100",     "and"},
        {"000000100111",     "nor"},
        {"000000100101",      "or"},
        {"000000100010",     "sub"},
        {"000000100011",    "subu"},
        {"000000100110",     "xor"},
        {"000000101010",     "slt"},
        {"000000101011",    "sltu"},
        {"000000000100",    "sllv"},
        {"000000000110",    "srlv"},
        {"000000000111",    "srav"},

        {"000000000000",     "sll"},
        {"000000000010",     "srl"},
        {"000000000011",     "sra"},

        {"000000001000",      "jr"},

        {"001000",          "addi"},
        {"001001",         "addiu"},
        {"001100",          "andi"},
        {"001101",           "ori"},
        {"001110",          "xori"},
        {"001010",          "slti"},
        {"001001",         "sltiu"},
          
        {"000100",           "beq"},
        {"000101",           "bne"},

        {"000010",             "j"},
        {"000011",           "jal"},

        {"100011",            "lw"},
        {"100010",           "lwx"},
        {"100001",            "lh"},
        {"100000",           "lhx"},
        {"100101",           "lhu"},
        {"100100",          "lhux"},
        {"101011",            "sw"},
        {"101010",           "swx"},
        {"101001",            "sh"},
        {"101000",           "shx"},

        {"000000001001",    "jalr"},

        {"001111",           "lui"},

        {"000001",        "bgezal"},

        {"010000",       "mfc/mtc"},

        {"010000011000",    "erec"},
        {"000000001100", "syscall"},
    });

    Reg = QMap<QString,QString>({
        {"00000","$zero"},
        {"00001","$at"},
        {"00010","$v0"},
        {"00011","$v1"},
        {"00100","$a0"},
        {"00101","$a1"},
        {"00110","$a2"},
        {"00111","$a3"},
        {"01000","$t0"},
        {"01001","$t1"},
        {"01010","$t2"},
        {"01011","$t3"},
        {"01100","$t4"},
        {"01101","$t5"},
        {"01110","$t6"},
        {"01111","$t7"},
        {"10000","$s0"},
        {"10001","$s1"},
        {"10010","$s2"},
        {"10011","$s3"},
        {"10100","$s4"},
        {"10101","$s5"},
        {"10110","$s6"},
        {"10111","$s7"},
        {"11000","$t8"},
        {"11001","$t9"},

        {"11010","$k0"},
        {"11011","$k1"},
        {"11100","$gp"},
        {"11101","$sp"},
        {"11110","$fp"},
        {"11111","$ra"}
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
}

/*反汇编*/
QString Disassembler::Discompile(QString &CompileString)
{
    bool ok;
    QString validthisline;
    MipsresultList.clear();
    QStringList listOfCompileString = Addn(CompileString);
    QListIterator<QString> itr(listOfCompileString);

    while (itr.hasNext())
    {
        QString thisLine = itr.next();
        // 除去注释
        QChar commentBegin = '#';
        int commentIndex = thisLine.indexOf(commentBegin, 0);
        validthisline = thisLine.left(commentIndex);

        // 将16进制的指令转成二进制
        validthisline = QString("%1").arg(validthisline.toLongLong(&ok, 16), 32, 2, QChar('0'));

        // 反汇编
        QString disassembledLine = InstructionToMipsCode(validthisline);
        if (!disassembledLine.isEmpty())
        {
            MipsresultList.append(disassembledLine);
        }
    }
    return Join_e(MipsresultList);
}

/*从字符串指定位置开始截取子串*/
QString Disassembler::GetSubString(QString input, int beginposition, int endposition)
{
    int i;
    QString result = "";
    for(i = beginposition; i < endposition; i++){
        result = result + input[i];
    }
    return result;
}

/*将补码转成原码*/
QString Disassembler::convertToFabs(QString Bin){
    int i, Index = 0;
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

/*将二进制原码转成十进制*/
QString Disassembler::convertBinToD(QString BinString){
    bool ok;
    int D;
    QString resultstring;
    if(BinString[0] == '0'){
        D = BinString.toInt(&ok, 2);
        resultstring = QString::number(D, 10);
    }
    else{
        QString BinStringFabs = convertToFabs(BinString);
        D = BinStringFabs.toInt(&ok, 2);
        resultstring = "-" + QString::number(D, 10);
    }
    return resultstring;
}

/*将二进制原码转成十进制再乘4*/
QString Disassembler::convertBinToDFour(QString BinString){
    bool ok;
    int D;
    QString resultstring;
    if(BinString[0] == '0'){
        D = BinString.toInt(&ok, 2) * 4;
        resultstring = QString::number(D, 10);
    }
    else{
        QString BinStringFabs = convertToFabs(BinString);
        D = BinStringFabs.toInt(&ok, 2) * 4;
        resultstring = "-" + QString::number(D, 10);
    }
    return resultstring;
}

/*将指令按行存入列表*/
QStringList Disassembler::Addn(QString &CompileString)
{
    QChar sep = '\n';
    QStringList my_stringlist = CompileString.split(sep);
    return my_stringlist;
}

/*给每条指令添加换行符*/
QString Disassembler::Join_e(QStringList &DisassembledStringList)
{
    DisassembledString = DisassembledStringList.join("\n");
    return DisassembledString;
}

/*判断指令类型*/
int Disassembler::Cases_contained(QString& Op){
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
    return Case;
}

/*反编译操作码*/
QString Disassembler::InstructionToMipsCode(QString thisLine)
{
    int Case;
    QString MipsCode;
    QString SubString;
    if (thisLine.isEmpty()){
        return "";
    }

    // 读取[0-5]位置的6位OpCode
    SubString = GetSubString(thisLine, 0, 6);
    // 如果有专有的OpCode
    if(KeyOp.find(SubString) != KeyOp.end()){
        MipsCode = KeyOp[SubString];
        Case = Cases_contained(MipsCode);
        switch(Case)
        {
            case 3:
                MipsCode = MipsCode + " " + Reg[GetSubString(thisLine, 11, 16)];
                MipsCode = MipsCode + " " + Reg[GetSubString(thisLine, 6, 11)];
                MipsCode = MipsCode + " " + convertBinToD(GetSubString(thisLine, 16, 32)) + ";";
                break;
            case 4:
                MipsCode = MipsCode + " " + Reg[GetSubString(thisLine, 11, 16)];
                MipsCode = MipsCode + " " + convertBinToD(GetSubString(thisLine, 16, 32)) + "(";
                MipsCode = MipsCode + Reg[GetSubString(thisLine, 6, 11)] + ")" +";";
                break;
            case 5:
                MipsCode = MipsCode + " " + convertBinToDFour(GetSubString(thisLine, 6, 32)) + ";";
                break;
            case 6:
                MipsCode = MipsCode + " " + Reg[GetSubString(thisLine, 11, 16)];
                MipsCode = MipsCode + " " + Reg[GetSubString(thisLine, 6, 11)];
                MipsCode = MipsCode + " " + convertBinToDFour(GetSubString(thisLine, 16, 32)) + ";";
                break;
            case 8:
                MipsCode = MipsCode + " " + Reg[GetSubString(thisLine, 11, 16)];
                MipsCode = MipsCode + " " + convertBinToD(GetSubString(thisLine, 16, 32)) + ";";
                break;
            case 9:
                MipsCode = MipsCode + " " + Reg[GetSubString(thisLine, 6, 11)];
                MipsCode = MipsCode + " " + convertBinToDFour(GetSubString(thisLine, 16, 32)) + ";";
                break;
            case 10:
                SubString = GetSubString(thisLine, 6, 11);
                if(SubString == "00000"){
                    MipsCode = "mfc0";
                }
                else if(SubString == "00100"){
                    MipsCode = "mtc0";
                }
                MipsCode = MipsCode + " " + Reg[GetSubString(thisLine, 11, 16)];
                MipsCode = MipsCode + " " + Reg[GetSubString(thisLine, 16, 21)] + ";";
                break;
        }
    }
    // 读取[0-5]位置的6位OpCode和[26-31]位置的func
    else{
        SubString = GetSubString(thisLine, 0, 6) + GetSubString(thisLine, 26, 32);
        MipsCode = KeyOp[SubString];
        Case = Cases_contained(MipsCode);
        switch(Case)
        {
            case 0:
                MipsCode = MipsCode + " " + Reg[GetSubString(thisLine, 16, 21)];
                MipsCode = MipsCode + " " + Reg[GetSubString(thisLine, 6, 11)];
                MipsCode = MipsCode + " " + Reg[GetSubString(thisLine, 11, 16)] +";";
                break;
            case 1:
                MipsCode = MipsCode + " " + Reg[GetSubString(thisLine, 16, 21)];
                MipsCode = MipsCode + " " + Reg[GetSubString(thisLine, 11, 16)];
                MipsCode = MipsCode + " " + Reg[GetSubString(thisLine, 21, 26)] + ";";
                break;
            case 2:
                MipsCode = MipsCode + " " + Reg[GetSubString(thisLine, 6, 11)] + ";";
                break;
            case 7:
                MipsCode = MipsCode + " " + Reg[GetSubString(thisLine, 6, 11)];
                MipsCode = MipsCode + " " + Reg[GetSubString(thisLine, 16, 21)] + ";";
                break;
            case 11:
                if(MipsCode == "010000011000") MipsCode ="erec;";
                else MipsCode = "syscall;";
                break;
        }
    }
    return MipsCode;
}
