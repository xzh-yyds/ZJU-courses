#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <QString>
#include <QVector>
#include <QMap>
#include <qmap.h>
#include <QDebug>

class Disassembler{
public:
    Disassembler();
    // 翻译机器码
    QString Discompile(QString& stringNeedCompile);
    QString InstructionToMipsCode(QString currentLine);
    int Cases_contained(QString& Op);
    // 处理字符串
    QStringList Addn(QString& stringNeedCompile);
    QString Join_e(QStringList& rawAssembledStringList);
    QString GetSubString(QString input, int beginposition, int endposition);
    // 将二进制数转成十进制
    QString convertToFabs(QString Bin);
    QString convertBinToD(QString);
    QString convertBinToDFour(QString BinString);
private:
    QString DisassembledString;

    QMap<QString, QString> KeyOp;
    QMap<QString, QString> Reg;

    // 分别存储不同类型的指令
    QStringList STD_Instruction;
    QStringList TDA_Instruction;
    QStringList S___Instruction;
    QStringList STI_Instruction;
    QStringList STII_Instruction;
    QStringList BSTI_Instruction;
    QStringList J_Instruction;
    QStringList S_D_Instruction;
    QStringList TI_Instruction;
    QStringList S_I_Instruction;
    QStringList TD_Instruction;
    QStringList SYS_Instruction;
    // 翻译的指令结果
    QStringList MipsresultList;
};

#endif // DISASSEMBLER_H
