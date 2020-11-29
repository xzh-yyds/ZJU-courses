#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include "assembler.h"
#include "disassembler.h"
#include "tablemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    bool openActionCallback();
    bool saveActionCallback();
    bool CreateNewActionCallback();
    void CopyTextActionCallback();
    void PasteTextActionCallback();
    void CloseWinActionCallback();
    void compile();
    void discompile();

private:
    Ui::MainWindow *ui;
//    TableModel *model;
    bool maybeSave();
    Assembler *assembler;
    Disassembler *disassembler;
};

#endif // MAINWINDOW_H
