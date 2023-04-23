#pragma once
#include "creatures_basic_interfaces.h"

class ClientInputData
{
public:
    virtual Action getAction() = 0;
};

class AttackClientData : public ClientInputData
{
public:
    unsigned int rowFrom;
    unsigned int columnFrom;
    unsigned int rowTo;
    unsigned int columnTo;

    AttackClientData(unsigned int rowFrom, unsigned int columnFrom,
                           unsigned int rowTo, unsigned int columnTo)
        : rowFrom(rowFrom), columnFrom(columnFrom), rowTo(rowTo), columnTo(columnTo) { }

    Action getAction() override { return ATTACK; }
};

class MoveClientData : public ClientInputData
{
public:
    unsigned int rowFrom;
    unsigned int columnFrom;
    unsigned int rowTo;
    unsigned int columnTo;

    MoveClientData(unsigned int rowFrom, unsigned int columnFrom,
                           unsigned int rowTo, unsigned int columnTo)
        : rowFrom(rowFrom), columnFrom(columnFrom), rowTo(rowTo), columnTo(columnTo) { }

    Action getAction() override { return MOVE; }
};

class StartNewGameData : public ClientInputData
{
public:
    RuleType ruleType;

    StartNewGameData(RuleType ruleType) :  ruleType(ruleType) { }

    Action getAction() override { return NEW_GAME; }
};

class AddUnitData : public ClientInputData
{
public:
    unsigned int row;
    unsigned int column;
    UnitType unitType;

    AddUnitData(unsigned int row, unsigned int column, UnitType unitType)
        : row(row), column(column), unitType(unitType) { }

    Action getAction() override { return ADD_UNIT; }
};

class AddBaseData : public ClientInputData
{
public:
    unsigned int row;
    unsigned int column;
    unsigned int possessorId;

    AddBaseData(unsigned int row, unsigned int column, unsigned int possessorId)
        : row(row), column(column), possessorId(possessorId) { }

    Action getAction() override { return ADD_BASE; }
};

class SaveGameData : public ClientInputData{
public:
    QString fileName;

    SaveGameData(QString fileName) { this->fileName = fileName; }

    Action getAction() override { return SAVE_GAME; }
};

class LoadGameData : public ClientInputData{
public:
    QString fileName;

    LoadGameData(QString fileName) { this->fileName = fileName; }

    Action getAction() override { return LOAD_GAME; }
};
