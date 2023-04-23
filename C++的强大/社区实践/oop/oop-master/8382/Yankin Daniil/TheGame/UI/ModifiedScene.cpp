#include "ModifiedScene.h"
#include "Unit/UnitHeader.h"
#include "Base/Base.h"
#include <fstream>
#include "MainWindow.h"


ModifiedScene::ModifiedScene(QWidget *parent) : QGraphicsScene(parent),
    attributeWidget(nullptr), baseWidget(nullptr), overButton(nullptr), playerWidget(nullptr), x(0), y(0), width(0), height(0) {}

ModifiedScene::~ModifiedScene() {
    int a = 5;
    a++;
}


void ModifiedScene::showAttributes(Object* object) {
    if (object == nullptr) return;

    if (object->getGroupType() == UNIT || object->getGroupType() == BASE) {
        hideAttributes();

        QGraphicsView* view = *(views().begin());

        attributeWidget = new AttributeWidget(view);
        attributeWidget->setValues(object);
        attributeWidget->move(view->width() - attributeWidget->width(), view->height() - attributeWidget->height());
        attributeWidget->show();
    }
}

void ModifiedScene::hideAttributes() {
    delete attributeWidget;
    attributeWidget = nullptr;
}


void ModifiedScene::showBase(Base* base) {
    if (base == nullptr)
        return;

    hideBase();

    QGraphicsView* view = *(views().begin());
    baseWidget = new BaseWidget(view);
    baseWidget->move(view->width() - baseWidget->width(), 0);
    baseWidget->show();
}

void ModifiedScene::hideBase() {
    delete baseWidget;
    baseWidget = nullptr;
}


void ModifiedScene::showTurn() {
    if (overButton != nullptr) {
        return;
    }

    QGraphicsView* view = *(views().begin());

    overButton = new TurnButton(view);
    overButton->move(view->width() - overButton->width(), view->height() - overButton->height());
    overButton->show();
}

void ModifiedScene::hideTurn() {
    delete overButton;
    overButton = nullptr;
}


void ModifiedScene::showPlayer(uint16_t playerId) {
    hidePlayer();

    QGraphicsView* view = *(views().begin());
    playerWidget = new PlayerWidget(view);
    playerWidget->setPlayer(playerId);
    playerWidget->move(view->width() - playerWidget->width(), 0);
    playerWidget->show();
}

void ModifiedScene::hidePlayer() {
    delete playerWidget;
    playerWidget = nullptr;
}



void ModifiedScene::updateInterface() {
    QGraphicsView* view = *(views().begin());

    if (overButton != nullptr) {
        overButton->move(view->width() - overButton->width(), view->height() - overButton->height());
    }
    if (baseWidget != nullptr) {
        baseWidget->move(view->width() - baseWidget->width(), 0);
    }
    if (attributeWidget != nullptr) {
        attributeWidget->move(view->width() - attributeWidget->width(), view->height() - attributeWidget->height());
    }
    if (playerWidget != nullptr) {
        playerWidget->move(view->width() - playerWidget->width(), 0);
    }
}



void ModifiedScene::winnersMessage(std::vector<uint16_t>& winners) {
    QGraphicsView* view = *(views().begin());
    auto mainWindow = static_cast<MainWindow*>(view->parent()->parent()->parent()->parent());
    mainWindow->showWinners(winners);
}
