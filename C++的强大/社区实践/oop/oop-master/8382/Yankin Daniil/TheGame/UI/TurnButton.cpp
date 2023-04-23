#include "TurnButton.h"
#include "ui_TurnButton.h"
#include "Game/Game.h"
#include "Command/Command.h"


TurnButton::TurnButton(QWidget *parent) : QWidget(parent), ui(new Ui::TurnButton) {
    ui->setupUi(this);

    QRegion mask(ui->turnButton->x(), ui->turnButton->y(), ui->turnButton->width()*2, ui->turnButton->height()*2, QRegion::Ellipse);
    ui->turnButton->setMask(mask);

    //QRegion* region = new QRegion(*(new QRect(ui->turnButton->x()+5,ui->turnButton->y()+5,190,190)),QRegion::Ellipse);
    //ui->turnButton->setMask(*region);
}

TurnButton::~TurnButton() {
    delete ui;
}


void TurnButton::on_turnButton_clicked() {
    UiCommand command(UI_TURN);
    command.execute();
}
