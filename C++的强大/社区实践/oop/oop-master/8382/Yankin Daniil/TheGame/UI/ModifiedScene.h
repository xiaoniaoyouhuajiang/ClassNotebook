#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QGraphicsSceneWheelEvent>
#include <QKeyEvent>
#include <QWidget>
#include <QGraphicsProxyWidget>

#include "AttributeWidget.h"
#include "BaseWidget.h"
#include "TurnButton.h"
#include "Ui/PlayerWidget.h"

#define OFFSET_STEP 0.01

class Object;
class Base;


class ModifiedScene : public QGraphicsScene
{
public:
    ModifiedScene(QWidget *parent = nullptr);
    ~ModifiedScene();

    void showAttributes(Object* object);
    void hideAttributes();

    void showBase(Base* base);
    void hideBase();

    void showTurn();
    void hideTurn();

    void showPlayer(uint16_t playerId);
    void hidePlayer();

    void updateInterface();

    void winnersMessage(std::vector<uint16_t>& winners);

private:
    AttributeWidget* attributeWidget;
    BaseWidget* baseWidget;
    TurnButton* overButton;
    PlayerWidget* playerWidget;

    qreal x;
    qreal y;
    qreal width;
    qreal height;
};
