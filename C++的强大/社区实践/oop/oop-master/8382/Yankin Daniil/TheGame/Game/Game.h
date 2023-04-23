#pragma once

#include <vector>
#include <map>
#include <queue>
#include <memory>

#include "GameDestroyer.h"
#include "GameMediator.h"
#include "GameFacade.h"

#include "Field/Field.h"
#include "Neutrals/NeutralContext.h"
#include "Log/LogAdapter.h"

class IGameInfo;
class PlayerContext;
class Player;
class NeutralPlayer;

using FieldInit = std::vector<std::vector<uint16_t>>;
using ObjectInit = std::vector<std::pair<Point, uint16_t>>;
using StartInit = std::tuple<FieldInit, ObjectInit, ObjectInit>;


class Game
{
private:
    static Game* instance;
    static GameDestroyer destroyer;

public:
    static Game& getInstance();

public:
    bool exist();

    class Initializer;
    class Saver;
    class Loader;
    void newGame(uint16_t width, uint16_t height, uint16_t playerCount, uint16_t rule);
    int save(std::string& fileName);
    int load(std::string& fileName);

    GameMediator& getGameMediator();
    GameFacade& getGameFacade();
    LogAdapter& getLogAdapter();

    void objectWasCreated(Object* object);
    void objectWasDestructed(Object* object);
    void unitWasMoved(IUnit* unit);

    void checkEndGame();

private:
    Game();
    Game(const Game& game) = delete;
    Game(Game&& game) = delete;
    ~Game();

    void clear();
    void setGameInfo(uint16_t playerCount, uint16_t rule);

    Player* getPlayerOfColor(uint16_t color);

    void unitWasCreated(IUnit* unit);
    void unitWasDestructed(IUnit* unit);
    void baseWasDestructed(Base* base);
    void turn();

private:
    GameMediator* gameMediator;
    GameFacade* gameFacade;
    IGameInfo* gameInfo;
    LogAdapter* logAdapter;

    Field* field;

    std::vector <Player*> playerVector;
    NeutralPlayer* neutralPlayer;


    friend class GameDestroyer;
    friend class GameMediator;
    friend class GameFacade;
    friend class GameCommand;
    friend class EliminationRule;
    friend class SpeedRule;
};


class Game::Initializer {
public:
    Initializer() = default;
    Initializer(const Initializer& initializer) = delete;
    Initializer(Initializer&& initializer) = delete;
    ~Initializer() = default;
    int initialize(uint16_t playerCount, uint16_t width, uint16_t height, StartInit& startInit);
};


class Game::Saver {
public:
    Saver(std::string& fileName);
    Saver(const Saver& saver) = delete;
    Saver(Saver&& saver) = delete;
    ~Saver();
    int save(Game& game);

private:
    std::ofstream stream;
};


class Game::Loader {
public:
    Loader(std::string& fileName);
    Loader(const Loader& loader) = delete;
    Loader(Loader&& loader) = delete;
    ~Loader();
    int load(Game& game);

private:
    void clearAfterError(Game& game);

private:
    std::ifstream stream;
};
