#include "GameFacade.h"
#include "Game.h"
#include "GameInfo.h"
#include "Command/Command.h"
#include "Landscape/LandscapeHeader.h"
#include "Player/Player.h"
#include "Player/NeutralPlayer.h"
#include "Unit/UnitHeader.h"
#include "Base/Base.h"
#include "Neutrals/NeutralContext.h"
#include "Handler/UnitActionHandler.h"
#include "Field/RoutePlotter.h"


GameFacade::GameFacade(Game* game) : scene(nullptr) {
    this->game = game;
    scene = nullptr;
}

GameFacade::~GameFacade() {
    cellMovementMap.clear();
    visualLandVector.clear();
    visualUnitMap.clear();
    visualBaseMap.clear();
    visualBuildingMap.clear();
}

void GameFacade::clear() {
    cellMovementMap.clear();
    visualLandVector.clear();
    visualUnitMap.clear();
    visualBaseMap.clear();
    visualBuildingMap.clear();
    selectedObject = nullptr;

    if (scene != nullptr) {
        scene->hideAttributes();
        scene->hideBase();
        scene->hideTurn();
        scene->clear();
    }
}


void GameFacade::setScene(std::shared_ptr<ModifiedScene> scene) {
    if (game->field != nullptr && scene != nullptr) {
        this->scene = scene;
    }

    addLandToScene();
    addUnitsToScene();
    addBasesToScene();
    addBuldingsToScene();

    this->scene->showTurn();
    this->scene->showPlayer(PLAYER_BLUE);
}

void GameFacade::addLandToScene() {
    if (scene == nullptr)
        return;

    Field* field = game->field;

    visualLandVector.resize(field->getHeight());

    for (uint16_t i = 0; i < field->getHeight(); i++) {
        visualLandVector[i].resize(field->getWidth(), nullptr);

        for (uint16_t j = 0; j < field->getWidth(); j++) {
            visualLandVector[i][j] = new VisualItem(field->getLandscape(Point(j, i)));
            addVisualItemToScene(visualLandVector[i][j]);
            setVisualLandPos(field->getLandscape(Point(j, i)));
        }
    }
}

void GameFacade::addUnitsToScene() {
    if (scene == nullptr)
        return;

    for (auto player = game->playerVector.begin(); player != game->playerVector.end(); player++) {
        auto unitSet = (*player)->getUnitSet();

        for (auto unit = unitSet->begin(); unit != unitSet->end(); unit++) {
            VisualItem* unitItem = new VisualItem(*unit);

            visualUnitMap.insert(std::make_pair(*unit, unitItem));

            addVisualItemToScene(unitItem);
            setVisualUnitPos(*unit);
        }
    }
}

void GameFacade::addBasesToScene() {
    if (scene == nullptr)
        return;

    for (auto player = game->playerVector.begin(); player != game->playerVector.end(); player++) {
        auto baseSet = (*player)->getBaseSet();

        for (auto base = baseSet->begin(); base != baseSet->end(); base++) {
            VisualItem* baseItem = new VisualItem(*base);

            visualBaseMap.insert(std::pair <Base*, VisualItem*> (*base, baseItem));

            addVisualItemToScene(baseItem);
            setVisualBasePos(*base);
        }
    }
}

void GameFacade::addBuldingsToScene() {
    if (scene == nullptr)
        return;

    auto buildingSet = game->neutralPlayer->getNeutralObjectSet();

    for (auto building = buildingSet->begin(); building != buildingSet->end(); building++) {
        VisualItem* buildingItem = new VisualItem(static_cast <Object*> (*building) );

        visualBuildingMap.insert(std::make_pair(*building, buildingItem));

        addVisualItemToScene(buildingItem);
        setVisualBuildingPos(*building);
    }
}



void GameFacade::addVisualItemToScene(VisualItem* item) {
    if (scene == nullptr)
        return;

    scene->addItem(item);
    item->setPos(0, 0);
}

void GameFacade::setVisualLandPos(ILandscape* landscape) {
    if (scene == nullptr)
        return;

    Point point = landscape->getPoint();
    VisualItem* landItem = visualLandVector[point.getY()][point.getX()];

    uint16_t itemWidth = landItem->pixmap().width();
    uint16_t itemHeight = landItem->pixmap().height();

    if (point.getY() % 2 == 0)
        landItem->setPos(point.getX() * itemWidth, point.getY() * itemHeight*3/4);
    else
        landItem->setPos(point.getX() * itemWidth + itemWidth/2, point.getY() * itemHeight*3/4);
}

void GameFacade::setVisualUnitPos(IUnit* unit) {
    if (scene == nullptr)
        return;

    if (visualUnitMap.find(unit) == visualUnitMap.end()) {
        visualUnitMap[unit] = new VisualItem(unit);
        scene->addItem(visualUnitMap[unit]);
    }

    VisualItem* unitItem = visualUnitMap[unit];
    VisualItem* landItem = visualLandVector[unit->getPoint().getY()][unit->getPoint().getX()];

    uint16_t landX = landItem->x();
    uint16_t landY = landItem->y();

    uint16_t landWidth = landItem->pixmap().width();
    uint16_t landHeight = landItem->pixmap().height();

    unitItem->setPos(landX + landWidth/2, landY + landHeight/3);

    if (unit == selectedObject) {
        RoutePlotter router;
        cellMovementMap = router.getCellMovementMap(*Game::getInstance().field, unit);
        scene->showAttributes(selectedObject);
    }
}

void GameFacade::setVisualBasePos(Base* base) {
    if (scene == nullptr)
        return;

    VisualItem* baseItem = visualBaseMap[base];
    VisualItem* landItem = visualLandVector[base->getPoint().getY()][base->getPoint().getX()];

    uint16_t landX = landItem->x();
    uint16_t landY = landItem->y();

    uint16_t landWidth = landItem->pixmap().width();
    uint16_t landHeight = landItem->pixmap().height();

    baseItem->setPos(landX + landWidth/5, landY + landHeight/3*2);
}

void GameFacade::setVisualBuildingPos(NeutralContext* building) {
    if (scene == nullptr)
        return;

    VisualItem* buildingItem = visualBuildingMap[building];
    VisualItem* landItem = visualLandVector[building->getPoint().getY()][building->getPoint().getX()];

    uint16_t landX = landItem->x();
    uint16_t landY = landItem->y();

    uint16_t landWidth = landItem->pixmap().width();
    uint16_t landHeight = landItem->pixmap().height();

    buildingItem->setPos(landX + landWidth/5 * 2, landY + landHeight/3 *2);
}

void GameFacade::unitWasDestructed(IUnit* unit) {
    if (scene == nullptr)
        return;

    if (unit == selectedObject && game->gameMediator != nullptr) {
        scene->hideAttributes();
        selectedObject = nullptr;
    }

    delete visualUnitMap[unit];
    visualUnitMap.erase(unit);
}

void GameFacade::baseWasDestructed(Base* base) {
    if (scene == nullptr)
        return;

    if (base == selectedObject && game->gameMediator != nullptr) {
        scene->hideAttributes();
        scene->hideBase();
        selectedObject = nullptr;
    }

    VisualItem* baseItem = visualBaseMap[base];
    delete baseItem;

    visualBaseMap.erase(base);
}


void GameFacade::updateInterface() {
    if (selectedObject == nullptr) {
        scene->hideAttributes();
        scene->hideBase();
        scene->showTurn();
        scene->showPlayer(Game::getInstance().gameInfo->getPlayerId());
    }
    else {
        scene->hideTurn();
        scene->hidePlayer();
        scene->showAttributes(selectedObject);
        if (selectedObject->getGroupType() == BASE) {
            scene->showBase(static_cast<Base*>(selectedObject));
        }
    }
}

void GameFacade::winnersMessage(std::vector<uint16_t>& winners) {
    if (scene == nullptr) {
        return;
    }
    scene->winnersMessage(winners);
}

void GameFacade::userCommand(uint16_t uiCommand, Object* object, uint16_t parameter) {
    // Выделение оъекта
    if (uiCommand == UI_SELECT_OBJECT) {
        selectedObject = nullptr;
        scene->hideAttributes();
        scene->hideBase();
        scene->showTurn();
        scene->showPlayer(Game::getInstance().gameInfo->getPlayerId());

        if (object->getGroupType() == BASE || object->getGroupType() == UNIT) {
            auto base = dynamic_cast<Base*>(object);
            auto unit = dynamic_cast<IUnit*>(object);

            if (base) {
                if (base->getPlayer()->getColor() != Game::getInstance().gameInfo->getPlayerId()) {
                    return;
                }
            }
            else if (unit) {
                if (unit->getPlayer()->getColor() != Game::getInstance().gameInfo->getPlayerId()) {
                    return;
                }
            }


            std::vector<int> logParameters = {object->getObjectType(), object->getPoint().getX(), object->getPoint().getY()};

            scene->hideTurn();
            scene->hideBase();

            selectedObject = object;
            scene->showAttributes(object);

            if (object->getGroupType() == BASE) {
                scene->showBase(static_cast <Base*> (object));

                logParameters.push_back((static_cast <Base*> (object))->getPlayer()->getColor());
            }

            else if (object->getGroupType() == UNIT) {
                RoutePlotter router;
                cellMovementMap = router.getCellMovementMap(*game->field, (static_cast <IUnit*> (object)));

                logParameters.push_back((static_cast <IUnit*> (object))->getPlayer()->getColor());
            }

            Game::getInstance().getLogAdapter().log(LOG_USER_SELECT_OBJECT, logParameters);
        }
        else {
            std::vector<int> logParameters;
            Game::getInstance().getLogAdapter().log(LOG_USER_UNSELECT_OBJECT, logParameters);
        }
    }

    else if (uiCommand == UI_INTERACT_OBJECT) {
        if (selectedObject == nullptr || selectedObject->getGroupType() != UNIT)
            return;

        UnitActionHandler handler;
        handler.handle(static_cast<IUnit*>(selectedObject), object);
    }

    // Создание юнитов базой
    else if (uiCommand == UI_PRODUCE) {
        Base* base = static_cast <Base*> (selectedObject);

        std::vector<int> logParameters = {base->getPoint().getX(), base->getPoint().getY(), base->getPlayer()->getColor(), parameter};
        Game::getInstance().getLogAdapter().log(LOG_USER_PRODUCE, logParameters);

        BaseProduceCommand command(base, parameter);
        command.execute();
        scene->showAttributes(selectedObject);
    }
}

void GameFacade::getRoute(Point start, Point finish, std::vector <Point>& route) {
    Cell* finishCell = game->field->getCell(finish);

    if (cellMovementMap.find(finishCell) == cellMovementMap.end())
        return;

    route.push_back(finish);

    while (route.back() != start) {
        finishCell = cellMovementMap.find(finishCell)->second.first;
        finish = finishCell->getPoint();
        route.push_back(finish);
    }
    route.pop_back();
}
