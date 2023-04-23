#include "attack.h"
#include "ui_attack.h"

Attack::Attack(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Attack)
{
    ui->setupUi(this);
}

Attack::~Attack()
{
    delete ui;
}

void Attack::on_attackButton_accepted()
{
    ptr->facade->attackUnit(ui->fromX->value(), ui->fromY->value(), ui->stepX->value(), ui->stepY->value());
}
