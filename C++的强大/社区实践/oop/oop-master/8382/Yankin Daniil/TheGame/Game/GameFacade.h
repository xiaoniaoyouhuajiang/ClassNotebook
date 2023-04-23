#pragma once

#include <queue>
#include <stack>
#include "UI/ModifiedScene.h"
#include "UI/VisualItem.h"
#include "Trivia/Point.h"

class Game;
class Cell;
class Object;
class ILandscape;
class IUnit;
class Base;
class NeutralContext;


class GameFacade
{
    friend class Game;
    friend class GameMediator;
    friend class RouteHandler;

public:
    ~GameFacade();

    void setScene(std::shared_ptr<ModifiedScene> scene);
    void setVisualLandPos(ILandscape* landscape);
    void setVisualUnitPos(IUnit* unit);
    void setVisualBasePos(Base* base);
    void setVisualBuildingPos(NeutralContext* building);

    void updateInterface();
    void winnersMessage(std::vector<uint16_t>& winners);

    void userCommand(uint16_t uiCommand, Object* object, uint16_t parameter = 0);

private:
    GameFacade(Game* game);
    void clear();

    void addVisualItemToScene(VisualItem* item);
    void addLandToScene();
    void addUnitsToScene();
    void addBasesToScene();
    void addBuldingsToScene();
    void unitWasDestructed(IUnit* unit);
    void baseWasDestructed(Base* base);

    void getRoute(Point start, Point finish, std::vector <Point>& routeVector);

private:
    Game* game;
    Object* selectedObject;
    std::map <Cell*, std::pair<Cell*, uint16_t>> cellMovementMap;

    std::shared_ptr<ModifiedScene> scene;
    std::vector <std::vector <VisualItem*>> visualLandVector;
    std::map <IUnit*, VisualItem*> visualUnitMap;
    std::map <Base*, VisualItem*> visualBaseMap;
    std::map <NeutralContext*, VisualItem*> visualBuildingMap;
};
