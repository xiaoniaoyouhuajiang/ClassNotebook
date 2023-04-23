#include "Game.h"
#include "GameInfo.h"
#include "Field/Field.h"
#include "Player/PlayerState.h"
#include "Player/Player.h"
#include "Player/NeutralPlayer.h"
#include "Unit/UnitHeader.h"
#include "Base/Base.h"
#include "Neutrals/NeutralContext.h"


Game* Game::instance = nullptr;
GameDestroyer Game::destroyer;


Game& Game::getInstance() {
    if (instance == nullptr) {
        instance = new Game();
        destroyer.init(instance);
    }
    return *instance;
}



Game::Game() : field(nullptr), neutralPlayer(nullptr) {
    gameMediator = new GameMediator(this);
    gameFacade = new GameFacade(this);
    gameInfo = new GameInfo<EliminationRule, 2>;
    logAdapter = new LogAdapter(LOGGING_DIR_FILE, LOGGING_MODE_DEFAULT);
}

Game::~Game() {
    delete gameMediator;
    gameMediator = nullptr;

    for (auto player = playerVector.begin(); player != playerVector.end(); player++) {
        delete (*player);
    }
    delete neutralPlayer;
    delete field;
    delete gameFacade;
    delete gameInfo;

    std::vector<int> logParameters;
    logAdapter->log(LOG_GAME_DELETED, logParameters);
    delete logAdapter;
}

void Game::clear() {
    for (auto player = playerVector.begin(); player != playerVector.end(); player++) {
        delete (*player);
    }
    playerVector.clear();
    delete neutralPlayer;
    neutralPlayer = nullptr;
    delete field;
    field = nullptr;

    gameFacade->clear();
    setGameInfo(2, RULE_ELIMINATION);
}

bool Game::exist() {
    if (field)
        return true;
    else
        return false;
}

void Game::newGame(uint16_t width, uint16_t height, uint16_t playerCount, uint16_t rule) {
    clear();
    setGameInfo(playerCount, rule);

    Game::Initializer initializer;
    auto startInit = gameInfo->getStartInit(width, height);
    initializer.initialize(playerCount, width, height, startInit);
}

int Game::save(std::string& fileName) {
    if (field == nullptr) {
        return 2;
    }

    try {
        Game::Saver saver(fileName);
        return saver.save(*this);
    }
    catch(std::runtime_error error) {
        return 3;
    }
}

int Game::load(std::string& fileName) {
    clear();

    try {
        Game::Loader loader(fileName);
        return loader.load(*this);
    }
    catch(std::runtime_error error) {
        return 3;
    }
}



GameMediator& Game::getGameMediator() {
    return *gameMediator;
}

GameFacade& Game::getGameFacade() {
    return *gameFacade;
}

LogAdapter& Game::getLogAdapter() {
    return *logAdapter;
}


void Game::setGameInfo(uint16_t playerCount, uint16_t rule) {
    delete gameInfo;
    if (rule == RULE_ELIMINATION) {
        if (playerCount == 2) {
            gameInfo = new GameInfo<EliminationRule, 2>();
        }
        else if (playerCount == 3) {
            gameInfo = new GameInfo<EliminationRule, 3>();
        }
        else if (playerCount == 4) {
            gameInfo = new GameInfo<EliminationRule, 4>();
        }
    }
    else if (rule == RULE_SPEED) {
        if (playerCount == 2) {
            gameInfo = new GameInfo<SpeedRule, 2>();
        }
        else if (playerCount == 3) {
            gameInfo = new GameInfo<SpeedRule, 3>();
        }
        else if (playerCount == 4) {
            gameInfo = new GameInfo<SpeedRule, 4>();
        }
    }
}

Player* Game::getPlayerOfColor(uint16_t color) {
    for (auto iter = playerVector.begin(); iter != playerVector.end(); iter++) {
        if ((*iter)->getColor() == color) {
            return *iter;
        }
    }
    return nullptr;
}



void Game::objectWasCreated(Object* object) {
    if (object->getGroupType() == UNIT) {
        unitWasCreated(static_cast <Unit*> (object));
    }
}

void Game::unitWasCreated(IUnit* unit) {
    field->setUnit(unit->getPoint(), unit);
    gameFacade->setVisualUnitPos(unit);
}


void Game::objectWasDestructed(Object* object) {
    if (object->getGroupType() == UNIT) {
        unitWasDestructed(static_cast <IUnit*> (object));
    }
    else if (object->getGroupType() == BASE) {
        baseWasDestructed(static_cast <Base*> (object));
    }
}

void Game::unitWasDestructed(IUnit* unit) {
    field->removeUnit(unit->getPoint());
    gameFacade->unitWasDestructed(unit);
}

void Game::baseWasDestructed(Base* base) {
    field->removeBase(base->getPoint());
    gameFacade->baseWasDestructed(base);
}


void Game::unitWasMoved(IUnit* unit) {
    gameFacade->setVisualUnitPos(unit);
}


void Game::turn() {
    auto player = getPlayerOfColor(gameInfo->getPlayerId());
    std::set <IUnit*>* unitSet = player->getUnitSet();
    for (auto unit = unitSet->begin(); unit != unitSet->end(); unit++) {
        (*unit)->smallHeal();
        (*unit)->renewMovePoints();
        (*unit)->unsetAttacked();
    }

    gameInfo->nextPlayerId();
    gameFacade->updateInterface();

    std::vector<int> parameters;
    logAdapter->log(LOG_GAME_TURN, parameters);
}



void Game::checkEndGame() {
    auto result = gameInfo->checkEndGame();
    if (result.first) {
        gameFacade->winnersMessage(result.second);
        clear();
    }
    for (auto player : playerVector) {
        if (player->baseSet.size() == 0) {
            gameInfo->removePlayerId(player->getColor());
        }
    }
}
