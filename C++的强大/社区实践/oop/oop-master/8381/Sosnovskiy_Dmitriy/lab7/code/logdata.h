#pragma once
#include "QString"
#include <QTextStream>
#include <clientinputdata.h>

class LogData{
protected:
    bool isAttemptSucced;
    LogFormatType formatType;
public:
    void setFormat(LogFormatType newFormat) { this->formatType = newFormat; }
    virtual ~LogData() = default;
    virtual LogEventType getType() = 0;
    virtual QString convertToString() = 0;
    friend std::ostream& operator<<(std::ostream& os, LogData* logData);
    friend QTextStream& operator<<(QTextStream& os, LogData* logData);
};



class NewGameLogData : public LogData{
private:
    StartNewGameData* data;
public:
    NewGameLogData(StartNewGameData* data, bool isSucceed)
    {
        this->data = data;
        this->isAttemptSucced = isSucceed;
    }

    QString convertToString() override {
        QString returnable = nullptr;
        if(formatType == ACTIONS_ONLY)
        {
            returnable = "New game has started. " + QString(isAttemptSucced ? "[SUCCESS]" : "[FAILURE]");

        }
        else
        {
            QString ruleTypeStr = data->ruleType == FIRST ? "First" : "Second";
            returnable = "New game has started. Rule type: " + ruleTypeStr + ". "
                    + (isAttemptSucced ? "[SUCCESS]" : "[FAILURE]");
        }
        return returnable;

    }

    LogEventType getType() override { return CREATED_BASE; }
};

class AddBaseLogData : public LogData
{
private:
    AddBaseData* data;
    unsigned int playerNumber;
public:
    AddBaseLogData(AddBaseData* data, unsigned int playerNumber, bool isSucceed) {
        this->data = data;
        this->isAttemptSucced = isSucceed;
        this->playerNumber = playerNumber;
    }

    QString convertToString() override {
        QString returnable = nullptr;
        if(formatType == ACTIONS_ONLY)
        {
             returnable = "Base was created. " +QString(isAttemptSucced ? "[SUCCESS]" : "[FAILURE]");
        }
        else
            returnable = "The base was created by player number " + QString::number(data->possessorId)
                    + ", row number: " + QString::number(data->row) + ", column number: " + QString::number(data->column)
                    + ". " + (isAttemptSucced ? "[SUCCESS]" : "[FAILURE]");
        return returnable;
    }

    LogEventType getType() override { return CREATED_BASE; }
};

class AddUnitLogData : public LogData
{
private:
    AddUnitData* data;
    unsigned int playerNumber;

    QString getUnitTypeAsString() {
        switch (data->unitType) {
            case CRIT_ARCHER: return "Crit archer";
            case CRIT_CAVALRY: return "Crit cavalry";
            case CRIT_INFANTRY: return "Crit infantry";
            case ABSORB_ARCHER: return "Absorb archer";
            case ABSORB_CAVALRY: return "Absorb cavalry";
            case ABSORB_INFANTRY: return "Absorb infantry";
        }
    }
public:
    AddUnitLogData(AddUnitData* data, unsigned int playerNumber, bool isSucceed)
    {
        this->data = data;
        this->isAttemptSucced = isSucceed;
        this->playerNumber = playerNumber;
    }

    QString convertToString() override {
        QString returnable = nullptr;

        if(formatType == ACTIONS_ONLY)
        {
            returnable = "Added unit. " + QString(isAttemptSucced ? "[SUCCESS]" : "[FAILURE]");
        }
        else
            returnable = "Added unit " + getUnitTypeAsString() + " by player number "  + QString::number(playerNumber)
                    + ", row number: " + QString::number(data->row) + ", column number: " + QString::number(data->column)
                    + ". " + (isAttemptSucced ? "[SUCCESS]" : "[FAILURE]");
        return returnable;
    }

    LogEventType getType() override { return CREATED_UNIT; }
};

class MoveUnitLogData : public LogData
{
private:
    MoveClientData* data;
    unsigned int playerNumber;
public:
    MoveUnitLogData(MoveClientData* data, unsigned int playerNumber, bool isSucceed)
    {
        this->data = data;
        this->playerNumber = playerNumber;
        this->isAttemptSucced = isSucceed;
    }

    QString convertToString() override{
        QString returnable = nullptr;
        if(formatType == ACTIONS_ONLY)
        {
            returnable = "Moving unit" + QString(isAttemptSucced ? "[SUCCESS]" : "[FAILURE]");
        }
        else
            returnable = "Unit was moved by player number " + QString::number(playerNumber)
                    + ", start row number: " + QString::number(data->rowFrom) + ", start column number: " + QString::number(data->columnFrom)
                    + ", end row number: " + QString::number(data->rowTo) + ", end column number: " + QString::number(data->columnTo)
                    + ". " + (isAttemptSucced ? "[SUCCESS]" : "[FAILURE]");
        return returnable;
    }

    LogEventType getType() override { return UNIT_MOVED; }
};

class AttackLogData : public LogData
{
private:
    AttackClientData* data;
    unsigned int playerNumber;
public:
    AttackLogData(AttackClientData* data, unsigned int playerNumber, bool isSucceed)
    {
        this->data = data;
        this->playerNumber = playerNumber;
        this->isAttemptSucced = isSucceed;
    }

    QString convertToString() override{
        QString returnable = nullptr;

        if(formatType == ACTIONS_ONLY)
        {
            returnable = "Attack commited. " + QString(isAttemptSucced ? "[SUCCESS]" : "[FAILURE]");
        }
        else
            returnable = "Attack commited by player number " + QString::number(playerNumber)
                    + ", row number of attack unit: " + QString::number(data->rowFrom) + ", column number of attack unit: " + QString::number(data->columnFrom)
                    + ", row number of defend creature: " + QString::number(data->rowTo) + ", column number of defend creature: " + QString::number(data->columnTo)
                    + ". " + (isAttemptSucced ? "[SUCCESS]" : "[FAILURE]");

        return returnable;
    }

    LogEventType getType() override { return ATTACK_COMMITED; }
};

