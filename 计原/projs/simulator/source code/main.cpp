#include "mainwindow.h"

#include <QApplication>
#include <QString>
#include <string>
#include <QPainter>
#include "sim.h"

extern int regs[32];
extern short memory[MEMSIZE];
extern int PC;
extern map<string,int> reg2ind;
extern map<int,string> ind2reg;

vector<Instruction> instrs;
int cur_instr_index=0;

void MainWindow::instr_load(){
    QString content=edit->toPlainText();
    QStringList strlist=content.split('\n');

    vector<string> strs;
    instrs.clear();
    for(int i=0;i<strlist.size();i++){
        strs.push_back(strlist[i].toStdString());
    }
    for(int i=0;i<strs.size();i++){
        Instruction instr(strs[i]);
        instrs.push_back(instr);
    }
    instrLoad(instrs);

    QString memtext;
    QString addr;
    QString mem;
    QString line;
    for(int i=0;i<MEMSIZE;i++){
        addr=QString("0x%1").arg(i,4,16,QLatin1Char('0'));
        mem=QString("0x%1").arg((unsigned short)memory[i],4,16,QLatin1Char('0'));
        line=addr;
        line.append(": ");
        line.append(mem);
        line.append('\n');
        memtext.append(line);
    }
    load->setText(memtext);

    PC=0;
    int next_ir_code=(unsigned short)memory[PC];
    next_ir_code<<=16;
    next_ir_code|=(unsigned short)memory[PC+1];
    instr_next->setText(QString::fromStdString(reasm(next_ir_code)));
}

void MainWindow::instr_execute(){
    int ir_code=(unsigned short)memory[PC];
    ir_code<<=16;
    ir_code|=(unsigned short)memory[PC+1];
    Instruction ir(reasm(ir_code));
    PC+=2;
    execute(ir);

    for(int i=0;i<32;i++){
        reg_content[i]->setText("$"+QString("0x%2").arg(regs[i],8,16,QLatin1Char('0')));
    }

    int next_ir_code=(unsigned short)memory[PC];
    next_ir_code<<=16;
    next_ir_code|=(unsigned short)memory[PC+1];
    instr_next->setText(QString::fromStdString(reasm(next_ir_code)));
    update();
}
void MainWindow::instr_restart(){
    regsInitial();
    PC=0;
    for(int i=0;i<32;i++){
        reg_content[i]->setText("$"+QString("0x%2").arg(regs[i],8,16,QLatin1Char('0')));
    }
}
void MainWindow::mem_clear(){
    regsInitial();
    memInitial();

    for(int i=0;i<32;i++){
        reg_content[i]->setText("$"+QString("0x%2").arg(regs[i],8,16,QLatin1Char('0')));
    }

    QString memtext;
    QString addr;
    QString mem;
    QString line;
    for(int i=0;i<MEMSIZE;i++){
        addr=QString("0x%1").arg(i,4,16,QLatin1Char('0'));
        mem=QString("0x%1").arg((unsigned short)memory[i],4,16,QLatin1Char('0'));
        line=addr;
        line.append(": ");
        line.append(mem);
        line.append('\n');
        memtext.append(line);
    }
    load->setText(memtext);

    PC=0;
}
void MainWindow::instr_run(){
    while(PC<2*instrs.size()){
        instr_execute();
    }
    update();
}

void MainWindow::paintEvent(QPaintEvent *ev){
    QPainter p(this);
    p.setPen(QPen(Qt::blue,4));
    int lineheight=30;
    p.drawLine(410,10+cur_instr_index*lineheight,420,10+cur_instr_index*lineheight);
}

void MainWindow::lineHighlight(){
    QColor line_color=QColor(Qt::gray).lighter(150);
}

int main(int argc, char *argv[]){
    initial();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
