#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include <iostream>

//bool fieldFlag = true;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();
    return 0;
}
