#include "NewGameWindow.h"
#include "ui_NewGameWindow.h"
#include "Rules/Rule.h"

NewGameWindow::NewGameWindow(QWidget *parent) : QDialog(parent), ui(new Ui::NewGameWindow), width(30), height(30), playerCount(2), rule(RULE_ELIMINATION), accept(false) {
    ui->setupUi(this);

    ui->widthSpinBox->setMinimum(20);
    ui->widthSpinBox->setMaximum(200);

    ui->heightSpinBox->setMinimum(20);
    ui->heightSpinBox->setMaximum(200);

    ui->playerComboBox->addItem("2");
    ui->playerComboBox->addItem("3");
    ui->playerComboBox->addItem("4");

    ui->ruleComboBox->addItem("Elimination");
    ui->ruleComboBox->addItem("Speed");

    setWindowFlags(Qt::CustomizeWindowHint);
}

NewGameWindow::~NewGameWindow() {
    delete ui;
}

uint16_t NewGameWindow::getWidth() {
    return width;
}

uint16_t NewGameWindow::getHeight() {
    return height;
}

uint16_t NewGameWindow::getPlayerCount() {
    return playerCount;
}

uint16_t NewGameWindow::getRule() {
    return rule;
}

bool NewGameWindow::checkAccept() {
    return accept;
}

void NewGameWindow::on_closeButton_clicked() {
    accept = false;
    close();
}

void NewGameWindow::on_okButton_clicked() {
    width = ui->widthSpinBox->value();
    height = ui->heightSpinBox->value();

    if (ui->playerComboBox->currentText() == "2") {
        playerCount = 2;
    }
    else if (ui->playerComboBox->currentText() == "3") {
        playerCount = 3;
    }
    else {
        playerCount = 4;
    }

    if (ui->ruleComboBox->currentText() == "Elimination") {
        rule = RULE_ELIMINATION;
    }
    else {
        rule = RULE_SPEED;
    }

    accept = true;
    close();
}
