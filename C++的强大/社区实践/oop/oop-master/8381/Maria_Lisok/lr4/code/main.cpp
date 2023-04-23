#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game *game = new Game(6, 15, 100);
    MainWindow w(nullptr, game);
    w.show();
    return a.exec();
}
