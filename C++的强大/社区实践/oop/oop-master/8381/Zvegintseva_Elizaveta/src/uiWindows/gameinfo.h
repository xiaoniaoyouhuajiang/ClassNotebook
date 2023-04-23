#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <QDialog>
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class GameInfo;
}

class GameInfo : public QDialog
{
    friend class MainWindow;
    Q_OBJECT

public:
    explicit GameInfo(QWidget *parent = nullptr);
    ~GameInfo();
    MainWindow* ptr;
private:
    Ui::GameInfo *ui;
};

#endif // GAMEINFO_H
