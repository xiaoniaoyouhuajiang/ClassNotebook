#include "baseinfo.h"
#include "ui_baseinfo.h"

BaseInfo::BaseInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BaseInfo)
{
    ui->setupUi(this);
}

BaseInfo::~BaseInfo()
{
    delete ui;
}


void BaseInfo::on_baseInfoButton_clicked()
{
    ui->infoBaseWindow->clear();
    ui->infoBaseWindow->append(QString::fromStdString(ptr->facade->getBaseInfo(ui->baseNum->value())));
}
