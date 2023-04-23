#include "addunit.h"
#include "ui_addunit.h"

AddUnit::AddUnit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUnit)
{
    ui->setupUi(this);

}

AddUnit::~AddUnit()
{
    delete ui;
}

void AddUnit::on_addUnit_accepted()
{
    ptr->facade->addUnit(ui->baseNum->value(), ui->typesOfUnit->currentIndex()+20);
}
