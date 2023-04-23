#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    resize(1300, 1000);
}


void PaintWidget::setGame(Game<TwoPlayersRule>* game) {
    this->game = game;
    connect(this->game->getField().get(), SIGNAL(updateSignal()), this, SLOT(paintItPlease()));
}


void PaintWidget::paintItPlease() {
    update();
}


void PaintWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    QPen pen(Qt::blue);
    painter.setPen(pen);
    QImage image;
    std::shared_ptr<Field> field;
    if (mode == GameMode::TWO_PLAYERS_GAME) {
        field = game->getField();
    }
    else {
        field = soloGame->getField();
    }
    for(int i = 0; i < field->getHeight(); i++) {
        for(int j = 0; j < field->getWidth(); j++) {
            std::shared_ptr<FieldCell> cell = field->getCell(j, i);
            image.load(QString::fromStdString(cell->getLand()->getPath()));
            painter.drawImage(j * 155, i * 155, image.scaled(150, 150));
            std::shared_ptr<Tower> tower = cell->getTower();
            std::shared_ptr<Unit> unit = cell->getUnit();
            if (tower != nullptr) {
                image.load("tower.png");
                painter.drawImage(j * 155, i * 155, image.scaled(150, 150));
                image.load(QString::fromStdString(tower->getFactory()->getPath()));
                painter.drawImage(j * 155, i * 155, image.scaled(50, 50));

                painter.drawText(j * 155, i * 155 + 60, QString::fromStdString("hp " + std::to_string(tower->getHP())));
                painter.drawText(j * 155, i * 155 + 70, QString::fromStdString("damage " + std::to_string(tower->getDamage())));
                painter.drawText(j * 155, i * 155 + 80, QString::fromStdString("size " + std::to_string(tower->getSize())));
                painter.drawText(j * 155, i * 155 + 90, QString::fromStdString("units " + std::to_string(tower->getUnitCount())));
            }
            else if (unit != nullptr) {
                image.load(QString::fromStdString(unit->getPath()));
                painter.drawImage(j * 155, i * 155, image.scaled(150, 150));

                painter.drawText(j * 155, i * 155 + 10, QString::fromStdString("hp " + std::to_string(unit->getHP())));
                painter.drawText(j * 155, i * 155 + 20, QString::fromStdString("damage " + std::to_string(unit->getOwnDamage() + unit->getLandDamage() + unit->getWeapon()->getDamage())));
                painter.drawText(j * 155, i * 155 + 30, QString::fromStdString("defence " + std::to_string(unit->getOwnArmor() + unit->getLandDefence() + unit->getArmor()->getDefend())));
            }
            else if (cell->getObj() != nullptr) {
                image.load(QString::fromStdString(cell->getObj()->getPath()));
                painter.drawImage(j * 155, i * 155, image.scaled(150, 150));
            }
        }
    }
}


QSize PaintWidget::sizeHint() const{
    return QSize(1300, 1000);
}


void PaintWidget::setMode(GameMode mode) {
    this->mode = mode;
}


void PaintWidget::setSoloGame(Game<SingleGameRule> *game) {
    this->soloGame = game;
    connect(this->soloGame->getField().get(), SIGNAL(updateSignal()), this, SLOT(paintItPlease()));
}
