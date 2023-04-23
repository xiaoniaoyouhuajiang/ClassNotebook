#include "BaseWidget.h"
#include "ui_BaseWidget.h"
#include "Base/Base.h"
#include "Command/Command.h"


BaseWidget::BaseWidget(QWidget *parent) : QWidget(parent), ui(new Ui::BaseWidget) {
    ui->setupUi(this);
}

BaseWidget::~BaseWidget() {
    delete ui;
}


void BaseWidget::on_swordsmanButton_clicked() {
    UiCommand command(UI_PRODUCE, nullptr, UNIT_SWORDSMAN);
    command.execute();
}

void BaseWidget::on_pikemanButton_clicked() {
    UiCommand command(UI_PRODUCE, nullptr, UNIT_PIKEMAN);
    command.execute();
}

void BaseWidget::on_shockCavalryButton_clicked() {
    UiCommand command(UI_PRODUCE, nullptr, UNIT_SHOCK_CAVALRY);
    command.execute();
}

void BaseWidget::on_archerButton_clicked() {
    UiCommand command(UI_PRODUCE, nullptr, UNIT_ARCHER);
    command.execute();
}

void BaseWidget::on_crossbowmanButton_clicked() {
    UiCommand command(UI_PRODUCE, nullptr, UNIT_CROSSBOWMAN);
    command.execute();
}

void BaseWidget::on_scoutCavalryButton_clicked() {
    UiCommand command(UI_PRODUCE, nullptr, UNIT_SCOUT_CAVALRY);
    command.execute();
}

void BaseWidget::on_catapultButton_clicked() {
    UiCommand command(UI_PRODUCE, nullptr, UNIT_CATAPULT);
    command.execute();
}

void BaseWidget::on_ramButton_clicked() {
    UiCommand command(UI_PRODUCE, nullptr, UNIT_RAM);
    command.execute();
}
