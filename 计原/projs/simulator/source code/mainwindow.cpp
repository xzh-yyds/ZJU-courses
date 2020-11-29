#include "mainwindow.h"
#include <QLabel>
#include <QTextEdit>
#include <QString>
#include <string>
#include <QPushButton>

extern int regs[32];
extern short memory[MEMSIZE];

string reg_name_table[32]={
    "$zero","  $at",
    "  $v0","  $v1",
    "  $a0","  $a1","  $a2","  $a3",
    "  $t0","  $t1","  $t2","  $t3","  $t4","  $t5","  $t6","  $t7",
    "  $s0","  $s1","  $s2","  $s3","  $s4","  $s5","  $s6","  $s7",
    "  $t8","  $t9",
    "  $k0","  $k1",
    "  $gp","  $sp","  $fp","  $ra"
};

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent){
    this->setWindowTitle("test");
    this->resize(1200,900);

    edit=new QTextEdit(this);
    edit->setGeometry(10,10,400,700);
    edit->setFont(QFont("Courier new",15,QFont::Bold));

    load=new QTextEdit(this);
    load->setReadOnly(true);
    load->setGeometry(420,10,370,700);
    load->setFont(QFont("Courier new",15,QFont::Bold));

    info=new QTextEdit(this);
    info->setReadOnly(true);
    info->setGeometry(800,10,390,700);
    info->setFont(QFont("Courier new",15,QFont::Bold));

    btn_load=new QPushButton(this);
    btn_load->setGeometry(160,720,100,50);
    btn_load->setText("Load");

    btn_execute=new QPushButton(this);
    btn_execute->setGeometry(500,720,100,50);
    btn_execute->setText("Execute");

    btn_run=new QPushButton(this);
    btn_run->setGeometry(610,720,100,50);
    btn_run->setText("Run");

    btn_memclear=new QPushButton(this);
    btn_memclear->setGeometry(720,720,100,50);
    btn_memclear->setText("Clear");

    btn_restart=new QPushButton(this);
    btn_restart->setGeometry(390,720,100,50);
    btn_restart->setText("Restart");

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::blue);

    instr_next=new QLabel(this);
    instr_next->setGeometry(405,800,400,50);
    instr_next->setFont(QFont("Courier new",15,QFont::Bold));
    instr_next->setPalette(pe);

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

    QLabel* status_title=new QLabel(this);
    status_title->setText("Registers Status");
    status_title->setFont(QFont("Courier new",15,QFont::Bold));
    status_title->setGeometry(870,15,300,40);

    pe.setColor(QPalette::WindowText,Qt::darkGray);

    for(int i=0;i<32;i++){
        reg_name[i]=new QLabel(this);
        reg_name[i]->setText(QString::fromStdString(reg_name_table[i]).append(": "));
        reg_name[i]->setFont(QFont("Courier new",12,QFont::Bold));
        reg_name[i]->setGeometry(810,50+i*20,80,40);
        reg_name[i]->setPalette(pe);
        //reg_name[i]->setAlignment(Qt::AlignRight);
    }

    for(int i=0;i<32;i++){
        reg_content[i]=new QLabel(this);
        reg_content[i]->setText("$"+QString("0x%1").arg(regs[i],8,16,QLatin1Char('0')));
        reg_content[i]->setGeometry(910,50+i*20,200,40);
        reg_content[i]->setFont(QFont("Courier new",12,QFont::Bold));
    }

    connect(btn_load,SIGNAL(released()),this,SLOT(instr_load()));
    connect(btn_execute,SIGNAL(released()),this,SLOT(instr_execute()));
    connect(btn_run,SIGNAL(released()),this,SLOT(instr_run()));
    connect(btn_restart,SIGNAL(released()),this,SLOT(instr_restart()));
    connect(btn_memclear,SIGNAL(released()),this,SLOT(mem_clear()));
}


MainWindow::~MainWindow(){

}

