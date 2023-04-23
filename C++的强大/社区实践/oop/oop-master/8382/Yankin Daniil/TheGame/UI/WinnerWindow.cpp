#include "WinnerWindow.h"
#include "ui_WinnerWindow.h"
#include "Player/Player.h"

WinnerWindow::WinnerWindow(std::vector<uint16_t>& winners, QWidget *parent) : QDialog(parent), ui(new Ui::WinnerWindow) {
    ui->setupUi(this);

    std::string message;
    for (auto winner = winners.begin(); winner != winners.end(); winner++) {
        std::string name;
        switch (*winner) {
        case PLAYER_BLUE:
            name = "BLUE";
            break;
        case PLAYER_RED:
            name = "RED";
            break;
        case PLAYER_GREEN:
            name = "GREEN";
            break;
        case PLAYER_ORANGE:
            name = "ORANGE";
            break;
        }

        message += name + " ";
        if (winner + 1 != winners.end()) {
            message += "and ";
        }
    }
    message += "won!";

    ui->message->setText(QString(message.data()));
}

WinnerWindow::~WinnerWindow() {
    delete ui;
}

void WinnerWindow::on_okButton_clicked() {
    close();
}
