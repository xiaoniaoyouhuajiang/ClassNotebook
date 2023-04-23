#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Game *game)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    facade = new Facade(ui, game);
    vector<string> neutrals = {"helmet", "mittens", "sabaton", "bandage", "powerpotion", "covid 19", "covid 37", "sword", "hatchet"};
    for(string buf : neutrals)
        ui->typesOfNeutrals->addItem(QString::fromStdString(buf));
    vector<string> units = {"archer", "shaman", "knigth", "rider", "swardman", "ork"};
    for(string buf : units)
        ui->typesOfUnits->addItem(QString::fromStdString(buf));

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_gameInfoButton_clicked()
{
    ui->logWindow->clear();
    facade->getGameInfo();
}

void MainWindow::on_addNeutralButton_clicked()
{
    facade->addNeutral(ui->posNeutralX->value(), ui->posNeutralY->value(), ui->typesOfNeutrals->currentIndex()+60);
}

void MainWindow::on_addUnitButton_clicked()
{
    facade->addUnit(ui->baseNum->value(), ui->typesOfUnits->currentIndex()+20);
}

void MainWindow::on_baseInfoButton_clicked()
{
    ui->infoWindow->clear();
    facade->getBaseInfo(ui->baseNum->value());
}

void MainWindow::on_addBaseButton_clicked()
{
    facade->addBase(ui->posBaseX->value(),ui->posBaseY->value(), ui->maxCountOfItems->value(), ui->health->value());
}

void MainWindow::on_moveButton_clicked()
{
    facade->moveUnit(ui->fromX->value(), ui->fromY->value(), ui->stepX->value(), ui->stepY->value());
}

void MainWindow::on_attackButton_clicked()
{
    facade->attackUnit(ui->fromX->value(), ui->fromY->value(), ui->stepX->value(), ui->stepY->value());
}

void MainWindow::on_unitInfoButton_clicked()
{
    ui->infoWindow->clear();
    facade->getUnitInfo(ui->posForInfoX->value(), ui->posForInfoY->value());
}

void MainWindow::on_landInfoButton_clicked()
{
    ui->infoWindow->clear();
    facade->getLandscapeInfo(ui->posForInfoX->value(), ui->posForInfoY->value());
}

void MainWindow::on_neutralInfoButton_clicked()
{
    ui->infoWindow->clear();
    facade->getNeutralInfo(ui->posForInfoX->value(), ui->posForInfoY->value());
}
