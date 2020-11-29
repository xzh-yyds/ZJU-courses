#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include "sim.h"

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *e);

private slots:
    void instr_load();
    void instr_execute();
    void instr_run();
    void mem_clear();
    void instr_restart();
    void lineHighlight();

private:
    QTextEdit *edit;
    QTextEdit *load;
    QTextEdit *info;
    QPushButton* btn_load;
    QPushButton* btn_execute;
    QPushButton* btn_run;
    QPushButton* btn_restart;
    QPushButton* btn_memclear;
    QLabel* reg_name[32];
    QLabel* reg_content[32];
    QLabel* instr_next;

};
#endif // MAINWINDOW_H
