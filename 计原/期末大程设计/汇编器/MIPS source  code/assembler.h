#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <QString>
#include <QVector>
#include <QMap>
#include <qmap.h>
#include <QDebug>
#include <QRegExp>

class Assembler{
public:
    Assembler();
    // 编译指令
    QString Compile(QString& stringNeedCompile);
    QStringList CompleteMachineCode(QString thisLine);
    QStringList CompilePseudo(QStringList& stringList, QString thisLine);
    int Case_contained(QString& Op);
    
    // 处理字符串
    QStringList Split_enter(QString& stringNeedCompile);
    QString Join_enter(QStringList& rawAssembledStringList);
    QString GetSubstring(QString input, int beginposition);
    // 将数字转化成补码
    QString convertTocomplement(int offset);
    // 在机器码的指定位置填入数字
    void change_s(const QString& rs, QString& to_machinecode);
    void change_t(const QString& rt, QString& to_machinecode);
    void change_d(const QString& rd, QString& to_machinecode);
    void change_a(const QString& sa, QString& to_machinecode);
    void change_i(const QString& imm, QString& to_machinecode);
    void change_labelori(QString& thisLine, const QString& label, QString& to_machinecode);
    void change_target(const QString& target, QString& to_machinecode);

private:
    QString AssembledString;
    QMap<QString, QString> KeyCode;
    QMap<QString, QString> Register;
    QMap<QString, QString> LabelAddr;
    QMap<QString, int> InstructionAddr;

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
    QStringList Pseudo_Instruction;
    // 编译的机器码结果
    QStringList resultList;
};

#endif // ASSEMBLER_H
