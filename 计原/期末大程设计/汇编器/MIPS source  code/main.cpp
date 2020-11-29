#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <QDebug>
#include <QSplashScreen>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
