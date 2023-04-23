#include "move.h"
#include "ui_move.h"

Move::Move(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::move)
{
    ui->setupUi(this);
}

Move::~Move()
{
    delete ui;
}

void Move::on_moveButton_accepted()
{
    ptr->facade->moveUnit(ui->fromX->value(), ui->fromY->value(), ui->stepX->value(), ui->stepY->value());
}
