#pragma once
#include "creategamewindow.h"
#include "ui_creategamewindow.h"
#include "mainwindow.h"

CreateGameWindow::CreateGameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateGameWindow)
{
    ui->setupUi(this);
    QObject::connect(this, &CreateGameWindow::signalSetTableHW, dynamic_cast<MainWindow *>(parent), &MainWindow::slotSetTableHW);
}

CreateGameWindow::~CreateGameWindow()
{
    delete ui;
}

void CreateGameWindow::on_pushButton_clicked()
{
    emit(this->signalSetTableHW(ui->lineEdit->text().toInt(), ui->lineEdit_2->text().toInt()));
    hide();
}
