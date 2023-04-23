#include <QGraphicsSceneMouseEvent>
#include "VisualItem.h"
#include "Game/Game.h"
#include "Landscape/LandscapeHeader.h"
#include "Player/Player.h"
#include "Unit/UnitHeader.h"
#include "Base/Base.h"
#include "Neutrals/NeutralContext.h"
#include "Command/Command.h"


VisualItem::VisualItem(Object* object, QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem(parent), object(object) {
    QPixmap pixmap;

    uint16_t objectType = object->getObjectType();

    IUnit* unit;
    Base* base;

    switch (objectType) {
    case LAND_PLAIN:
        pixmap.load("://imgs/plain.png");
        setPixmap(pixmap);
        setZValue(-10);
        break;

    case LAND_FOREST:
        pixmap.load("://imgs/forest.png");
        setPixmap(pixmap);
        setZValue(-10);
        break;

    case LAND_HILL:
        pixmap.load("://imgs/hill.png");
        setPixmap(pixmap);
        setZValue(-10);
        break;

    case LAND_FOREST_HILL:
        pixmap.load("://imgs/forest_hill.png");
        setPixmap(pixmap);
        setZValue(-10);
        break;

    case LAND_MOUNTAIN:
        pixmap.load("://imgs/mountain.png");
        setPixmap(pixmap);
        setZValue(-10);
        break;

    case LAND_WATER:
        pixmap.load("://imgs/water.png");
        setPixmap(pixmap);
        setZValue(-10);
        break;

    case UNIT_SWORDSMAN:
        unit = static_cast <IUnit*> (object);
        switch (unit->getPlayer()->getColor()) {
        case PLAYER_BLUE:
            pixmap.load("://imgs/swordsman_blue.png");
            break;
        case PLAYER_RED:
            pixmap.load("://imgs/swordsman_red.png");
            break;
        case PLAYER_GREEN:
            pixmap.load("://imgs/swordsman_green.png");
            break;
        case PLAYER_ORANGE:
            pixmap.load("://imgs/swordsman_orange.png");
            break;
        }
        setPixmap(pixmap);
        setZValue(10);
        break;

    case UNIT_PIKEMAN:
        unit = static_cast <IUnit*> (object);
        switch (unit->getPlayer()->getColor()) {
        case PLAYER_BLUE:
            pixmap.load("://imgs/pikeman_blue.png");
            break;
        case PLAYER_RED:
            pixmap.load("://imgs/pikeman_red.png");
            break;
        case PLAYER_GREEN:
            pixmap.load("://imgs/pikeman_green.png");
            break;
        case PLAYER_ORANGE:
            pixmap.load("://imgs/pikeman_orange.png");
            break;
        }
        setPixmap(pixmap);
        setZValue(10);
        break;

    case UNIT_SHOCK_CAVALRY:
        unit = static_cast <IUnit*> (object);
        switch (unit->getPlayer()->getColor()) {
        case PLAYER_BLUE:
            pixmap.load("://imgs/shock_cavalry_blue.png");
            break;
        case PLAYER_RED:
            pixmap.load("://imgs/shock_cavalry_red.png");
            break;
        case PLAYER_GREEN:
            pixmap.load("://imgs/shock_cavalry_green.png");
            break;
        case PLAYER_ORANGE:
            pixmap.load("://imgs/shock_cavalry_orange.png");
            break;
        }
        setPixmap(pixmap);
        setZValue(10);
        break;

    case UNIT_ARCHER:
        unit = static_cast <IUnit*> (object);
        switch (unit->getPlayer()->getColor()) {
        case PLAYER_BLUE:
            pixmap.load("://imgs/archer_blue.png");
            break;
        case PLAYER_RED:
            pixmap.load("://imgs/archer_red.png");
            break;
        case PLAYER_GREEN:
            pixmap.load("://imgs/archer_green.png");
            break;
        case PLAYER_ORANGE:
            pixmap.load("://imgs/archer_orange.png");
            break;
        }
        setPixmap(pixmap);
        setZValue(10);
        break;

    case UNIT_CROSSBOWMAN:
        unit = static_cast <IUnit*> (object);
        switch (unit->getPlayer()->getColor()) {
        case PLAYER_BLUE:
            pixmap.load("://imgs/crossbowman_blue.png");
            break;
        case PLAYER_RED:
            pixmap.load("://imgs/crossbowman_red.png");
            break;
        case PLAYER_GREEN:
            pixmap.load("://imgs/crossbowman_green.png");
            break;
        case PLAYER_ORANGE:
            pixmap.load("://imgs/crossbowman_orange.png");
            break;
        }
        setPixmap(pixmap);
        setZValue(10);
        break;

    case UNIT_SCOUT_CAVALRY:
        unit = static_cast <IUnit*> (object);
        switch (unit->getPlayer()->getColor()) {
        case PLAYER_BLUE:
            pixmap.load("://imgs/scout_cavalry_blue.png");
            break;
        case PLAYER_RED:
            pixmap.load("://imgs/scout_cavalry_red.png");
            break;
        case PLAYER_GREEN:
            pixmap.load("://imgs/scout_cavalry_green.png");
            break;
        case PLAYER_ORANGE:
            pixmap.load("://imgs/scout_cavalry_orange.png");
            break;
        }
        setPixmap(pixmap);
        setZValue(10);
        break;

    case UNIT_CATAPULT:
        unit = static_cast <IUnit*> (object);
        switch (unit->getPlayer()->getColor()) {
        case PLAYER_BLUE:
            pixmap.load("://imgs/catapult_blue.png");
            break;
        case PLAYER_RED:
            pixmap.load("://imgs/catapult_red.png");
            break;
        case PLAYER_GREEN:
            pixmap.load("://imgs/catapult_green.png");
            break;
        case PLAYER_ORANGE:
            pixmap.load("://imgs/catapult_orange.png");
            break;
        }
        setPixmap(pixmap);
        setZValue(10);
        break;

    case UNIT_RAM:
        unit = static_cast <IUnit*> (object);
        switch (unit->getPlayer()->getColor()) {
        case PLAYER_BLUE:
            pixmap.load("://imgs/ram_blue.png");
            break;
        case PLAYER_RED:
            pixmap.load("://imgs/ram_red.png");
            break;
        case PLAYER_GREEN:
            pixmap.load("://imgs/ram_green.png");
            break;
        case PLAYER_ORANGE:
            pixmap.load("://imgs/ram_orange.png");
            break;
        }
        setPixmap(pixmap);
        setZValue(10);
        break;

    case BASE:
        base = static_cast <Base*> (object);
        switch (base->getPlayer()->getColor()) {
        case PLAYER_BLUE:
            pixmap.load("://imgs/town_blue.png");
            break;
        case PLAYER_RED:
            pixmap.load("://imgs/town_red.png");
            break;
        case PLAYER_GREEN:
            pixmap.load("://imgs/town_green.png");
            break;
        case PLAYER_ORANGE:
            pixmap.load("://imgs/town_orange.png");
            break;
        }

        setPixmap(pixmap);
        setZValue(5);
        break;

    case NEUT_OBJECT:
        pixmap.load("://imgs/health_office.png");
        setPixmap(pixmap);
        setZValue(5);
        break;
    }

    // Уже не помню, зачем это, но потом обязательно вспомню
    setFlag(QGraphicsItem::ItemIsSelectable);
    //setFlag(QGraphicsItem::ItemIsMovable);
}


void VisualItem::mouseReleaseEvent(QGraphicsSceneMouseEvent*) {}


void VisualItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->modifiers() & Qt::AltModifier) {
        event->ignore();
        return;
    }

    if (event->button() == Qt::LeftButton) {
        UiCommand command(UI_SELECT_OBJECT, object);
        command.execute();
    }
    else if (event->button() == Qt::RightButton) {
        UiCommand command(UI_INTERACT_OBJECT, object);
        command.execute();
    }
}
