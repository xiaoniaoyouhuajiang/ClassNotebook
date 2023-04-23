#pragma once
#include "gamefacade.h"

class Command
{
protected:
    GameFacade* receiverGameFacade;
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};


class MoveCommand : public Command
{
protected:
    MoveClientData* data;
public:
    MoveCommand(GameFacade* receiverGameFacade, MoveClientData* data)
    {
        this->receiverGameFacade = receiverGameFacade;
        this->data = data;
    }

    void execute() override
    {
       this->receiverGameFacade->moveUnit(data);
    }
};

class AttackCommand : public Command
{
protected:
    AttackClientData* data;
public:
    AttackCommand(GameFacade* receiverGameFacade, AttackClientData* data)
    {
        this->receiverGameFacade = receiverGameFacade;
        this->data = data;
    }

    void execute() override
    {
        this->receiverGameFacade->attack(data);
    }
};

class AddBaseCommand : public Command
{
protected:
    AddBaseData* data;
public:
    AddBaseCommand(GameFacade* receiverGameFacade, AddBaseData* data)
    {
        this->receiverGameFacade = receiverGameFacade;
        this->data = data;
    }

    void execute() override
    {
        receiverGameFacade->addBase(data);
    }
};

class AddUnitCommand : public Command
{
protected:
    AddUnitData* data;
public:
    AddUnitCommand(GameFacade* receiverGameFacade, AddUnitData* data)
    {
        this->receiverGameFacade = receiverGameFacade;
        this->data = data;
    }

    void execute() override
    {
        this->receiverGameFacade->addUnit(data);
    }
};

class StartNewGameCommand : public Command
{
protected:
    StartNewGameData* data;
public:
    StartNewGameCommand(GameFacade* receiverGameFacade, StartNewGameData* data)
    {
        this->receiverGameFacade = receiverGameFacade;
        this->data = data;
    }

    void execute() override
    {
        this->receiverGameFacade->startNewGame(data);
    }
};

