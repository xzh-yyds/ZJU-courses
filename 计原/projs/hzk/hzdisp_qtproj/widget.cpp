#include "widget.h"
#include "ui_widget.h"
#include <QCoreApplication>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    myButton=new QPushButton("Hello",this);
    btn_larger=new QPushButton("larger",this);
    btn_smaller=new QPushButton("smaller",this);
    btn_italic=new QPushButton("italic: off",this);
    btn_rotate=new QPushButton("rotate",this);
    btn_color=new QPushButton("color",this);

    myButton->setGeometry(600,150,100,40);
    btn_smaller->setGeometry(600,200,100,40);
    btn_larger->setGeometry(600,250,100,40);
    btn_italic->setGeometry(600,300,100,40);
    btn_rotate->setGeometry(600,350,100,40);
    btn_color->setGeometry(600,400,100,40);

    input=new QLineEdit(this);
    input->setGeometry(600,50,100,40);
    connect(myButton, SIGNAL(released()), this, SLOT(handleButton()));
    connect(btn_larger, SIGNAL(released()), this, SLOT(hzLarger()));
    connect(btn_smaller, SIGNAL(released()), this, SLOT(hzSmaller()));
    connect(btn_italic, SIGNAL(released()), this, SLOT(hzItalic()));
    connect(btn_rotate, SIGNAL(released()), this, SLOT(hzRotate()));
    connect(btn_color, SIGNAL(released()), this, SLOT(hzColor()));
}

Widget::~Widget()
{
    delete ui;
}



