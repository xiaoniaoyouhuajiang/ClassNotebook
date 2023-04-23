#include <QApplication>
#include <iostream>
#include "gamewindow.h"
#include "field.h"
#include "base.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    w.show();

    return a.exec();
}
