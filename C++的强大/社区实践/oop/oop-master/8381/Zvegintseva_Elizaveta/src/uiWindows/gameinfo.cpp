#include "gameinfo.h"
#include "ui_gameinfo.h"

GameInfo::GameInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameInfo)
{
    ui->setupUi(this);
    ui->gameInfoWindow->clear();
    //ui->gameInfoWindow->append(QString::fromStdString(ptr->facade->getGameInfo()));
}

GameInfo::~GameInfo()
{
    delete ui;
}
