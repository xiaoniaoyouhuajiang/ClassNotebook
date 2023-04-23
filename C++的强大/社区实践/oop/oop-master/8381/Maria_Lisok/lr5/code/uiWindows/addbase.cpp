#include "addbase.h"
#include "ui_addbase.h"

AddBase::AddBase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBase)
{
    ui->setupUi(this);
}

AddBase::~AddBase()
{
    delete ui;
}

void AddBase::on_addBase_accepted()
{
    ptr->facade->addBase(ui->posBaseX->value(),ui->posBaseY->value(), ui->maxCountOfItems->value(), ui->health->value());
}
