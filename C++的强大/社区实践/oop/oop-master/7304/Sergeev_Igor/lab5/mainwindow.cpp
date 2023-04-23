#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller.h"
#include "loggincategories.h"
#include <exception>
#include <QDesktopServices>
#include "my_except.h"

#include <QtGui>
#include "graphwidget.h"
#include "node.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_nextNode_clicked()
{
    Controller::getInstance()->goNext(this->ui);
}

void MainWindow::on_prevNode_clicked()
{
    Controller::getInstance()->goBack(this->ui);
}

void MainWindow::on_initNode_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, QObject::tr("Open File"),"~/lab5", QObject::tr("Text files (*.txt)"));
    try{
        Controller::getInstance()->initNode(filename, this->ui);
    }
    catch (MyExcept & ex) {
        ui->status->setText(ex.get_action_error() + " " + ex.data_state);
        return;
    }
}

void MainWindow::on_newNode_clicked()
{
    Controller::getInstance()->makeNewNode(this->ui);
}

void MainWindow::on_changeNode_clicked()
{
    Controller::getInstance()->changeMyNode(this->ui);
}

void MainWindow::on_saveButton_clicked()
{
    Controller::getInstance()->saveInFile();
}

void MainWindow::on_swapButton_clicked()
{
    Controller::getInstance()->swapNode(this->ui);
}

void MainWindow::on_cacheSaveButton_clicked()
{
    Controller::getInstance()->saveInCache();
}

void MainWindow::on_newNextNode_clicked()
{
    Controller::getInstance()->makeNewNext(this->ui);
}

void MainWindow::on_newStart_clicked()
{
    Controller::getInstance()->initFirst(this->ui);
}

void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, QObject::tr("Open File"),"~/build-lab5-Desktop-Debug/save.txt", QObject::tr("Text files (save.txt)"));
    QDesktopServices::openUrl(QUrl(QUrl::fromLocalFile(filename)));
}

void MainWindow::on_openGraph_clicked()
{
    if (!widget){
        widget = new GraphWidget();
    }
    widget->show();
}
