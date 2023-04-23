#include "PlayerWidget.h"
#include "ui_PlayerWidget.h"
#include "Player/Player.h"

PlayerWidget::PlayerWidget(QWidget *parent) : QWidget(parent), ui(new Ui::PlayerWidget) {
    ui->setupUi(this);
}

PlayerWidget::~PlayerWidget() {
    delete ui;
}

void PlayerWidget::setPlayer(uint16_t playerId) {
    switch(playerId) {
    case PLAYER_BLUE:
        ui->playerLabel->setText("BLUE");
        break;
    case PLAYER_RED:
        ui->playerLabel->setText("RED");
        break;
    case PLAYER_GREEN:
        ui->playerLabel->setText("GREEN");
        break;
    case PLAYER_ORANGE:
        ui->playerLabel->setText("ORANGE");
        break;
    }
}
