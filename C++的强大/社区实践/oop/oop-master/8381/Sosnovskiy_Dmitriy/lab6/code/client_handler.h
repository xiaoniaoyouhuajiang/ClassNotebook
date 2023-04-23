#pragma once
#include "string"
#include "gamefacade.h"
#include "command.h"
#include "clientinputdata.h"

class Handler{
public:
    virtual ~Handler() = default;
    virtual Handler *setNext(Handler* handler) = 0;
    virtual ClientInputData* handle(ClientInputData* data) = 0;
};

class AbstractHandler : public Handler
{
private:
    Handler* nextHandler;
protected:
    GameFacade* gameFacade;
public:
    AbstractHandler(): nextHandler(nullptr) { }
    Handler *setNext(Handler* handler) override {
        this->nextHandler = handler;
        return handler;
    }
    ClientInputData* handle(ClientInputData* data) override {
        if(this->nextHandler)
        {
            return this->nextHandler->handle(data);
        } else return nullptr;
    }
};


class StartGameHandler : public AbstractHandler{
public:
    StartGameHandler(GameFacade* gameFacade) { this->gameFacade = gameFacade; }
    ClientInputData* handle(ClientInputData* data) override {
        if(data->getAction() == NEW_GAME)
        {
            StartNewGameData* newGameData = dynamic_cast<StartNewGameData*>(data);
            Command* startGameCommand = new StartNewGameCommand(gameFacade, newGameData);
            startGameCommand->execute();
            return nullptr;
        } else return AbstractHandler::handle(data);
    }
};


class AttackHandler : public AbstractHandler {
public:
    AttackHandler(GameFacade* gameFacade) { this->gameFacade = gameFacade; }
    ClientInputData* handle(ClientInputData* data) override {
        if(data->getAction() == ATTACK)
        {
            AttackClientData* attackData = dynamic_cast<AttackClientData*>(data);

            Command* attackCommand = new AttackCommand(gameFacade, attackData);
            attackCommand->execute();
            return nullptr;
        } else return AbstractHandler::handle(data);
    }
};

class AddBaseHandler : public AbstractHandler {
public:
    AddBaseHandler(GameFacade* gameFacade) { this->gameFacade = gameFacade; }
    ClientInputData* handle(ClientInputData* data) override {
        if(data->getAction() == ADD_BASE)
        {
            AddBaseData* addBaseData = dynamic_cast<AddBaseData*>(data);

            Command* addBaseCommand = new AddBaseCommand(gameFacade, addBaseData);
            addBaseCommand->execute();
            return nullptr;
        } else return AbstractHandler::handle(data);
    }
};

class AddUnitHandler : public AbstractHandler {
public:
    AddUnitHandler(GameFacade* gameFacade) { this->gameFacade = gameFacade; }
    ClientInputData* handle(ClientInputData* data) override {
        if(data->getAction() == ADD_UNIT)
        {
            AddUnitData* addUnitData = dynamic_cast<AddUnitData*>(data);

            Command* addUnitCommand = new AddUnitCommand(gameFacade, addUnitData);
            addUnitCommand->execute();
            return nullptr;
        } else return AbstractHandler::handle(data);
    }
};

class MoveHandler : public AbstractHandler {
public:
    MoveHandler(GameFacade* gameFacade) { this->gameFacade = gameFacade; }
    ClientInputData* handle(ClientInputData* data) override {
        if(data->getAction() == MOVE)
        {
            MoveClientData* moveData = dynamic_cast<MoveClientData*>(data);

            Command* moveCommand = new MoveCommand(gameFacade, moveData);
            moveCommand->execute();
            return nullptr;
        } else return AbstractHandler::handle(data);
    }
};

class SaveGameHandler : public AbstractHandler
{
public:
    SaveGameHandler(GameFacade* gameFacade) { this->gameFacade = gameFacade; }
    ClientInputData* handle(ClientInputData* data) override {
        if(data->getAction() == SAVE_GAME)
        {
            SaveGameData* saveData = dynamic_cast<SaveGameData*>(data);
            Command* saveGameCommand = new SaveGameCommand(gameFacade, saveData);
            saveGameCommand->execute();
            return nullptr;
        } else return AbstractHandler::handle(data);
    }
};


class LoadGameHandler : public AbstractHandler
{
public:
    LoadGameHandler(GameFacade* gameFacade) { this->gameFacade = gameFacade; }
    ClientInputData* handle(ClientInputData* data) override {
        if(data->getAction() == LOAD_GAME)
        {
            LoadGameData* loadData = dynamic_cast<LoadGameData*>(data);
            Command* saveGameCommand = new LoadGameCommand(gameFacade, loadData);
            saveGameCommand->execute();
            return nullptr;
        } else return AbstractHandler::handle(data);
    }
};
