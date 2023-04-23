#include "addneutral.h"
#include "ui_addneutral.h"

AddNeutral::AddNeutral(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNeutral)
{
    ui->setupUi(this);
}

AddNeutral::~AddNeutral()
{
    delete ui;
}

void AddNeutral::on_addNeutral_accepted()
{
    ptr->facade->addNeutral(ui->posNeutralX->value(), ui->posNeutralY->value(), ui->typesOfNeutrals->currentIndex()+60);
    close();
}

void AddNeutral::on_addNeutral_rejected()
{
    close();
}
