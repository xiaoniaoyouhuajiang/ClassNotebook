#pragma once
#include "QString"
#include <QTextStream>
#include <clientInputData.h>

enum LogEventType
{
    NEW_GAME_STARTED,
    CREATED_BASE,
    CREATED_UNIT,
    UNIT_MOVED,
    ATTACK_COMMITED,
};

enum LogFormatType
{
    ACTIONS_ONLY,
    FULL_INFO
};

class LogData
{
protected:
    bool isAttemptSucced;
    LogFormatType formatType;
public:
    void setFormat(LogFormatType newFormat)
    {
        this->formatType = newFormat;
    }
    virtual ~LogData() = default;
    virtual LogEventType getType() = 0;
    virtual QString convertToString() = 0;
    friend std::ostream& operator<<(std::ostream& os, LogData* logData);
    friend QTextStream& operator<<(QTextStream& os, LogData* logData);
};



class NewGameLogData : public LogData
{
private:
    StartNewGameData* data;
public:
    NewGameLogData(StartNewGameData* data, bool isSucceed)
    {
        this->data = data;
        this->isAttemptSucced = isSucceed;
    }

    QString convertToString() override
    {
        QString returnable = nullptr;
        if(formatType == ACTIONS_ONLY)
        {
            returnable = "Новая игра." + QString(isAttemptSucced ? "(Успешно)" : "(Ошибка)");
        }
        else
            returnable = "Начало новой игры. Количество игроков: " + QString::number(data->playersAmount)
                    + ", ряды: " + QString::number(data->rows) + ", стобцы: " + QString::number(data->columns)
                    + ", максимум юнитов на поле: " + QString::number(data->maximumEntitiesAmount)
                    + ". " + (isAttemptSucced ? "(Успешно)" : "(Ошибка)");
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
             returnable = "Была создана база. " +QString(isAttemptSucced ? "(Успешно)" : "(Ошибка)");
        }
        else
            returnable = "База была создана игроком #" + QString::number(data->possessorId)
                    + ", ряд: " + QString::number(data->row) + ", стобец: " + QString::number(data->column)
                    + ". " + (isAttemptSucced ? "(Успешно)" : "(Ошибка)");
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
            case CRIT_ARCHER: return "Лучник с крит. уроном";
            case CRIT_CAVALRY: return "Конница с крит. уроном";
            case CRIT_INFANTRY: return "Пехота с крит. уроном";
            case ABSORB_ARCHER: return "Лучник с ув. здоровьем";
            case ABSORB_CAVALRY: return "Конница с ув. здоровьем";
            case ABSORB_INFANTRY: return "Пехота с ув. здоровьем";
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
            returnable = "Добавлен новый юнит. " + QString(isAttemptSucced ? "(Успешно)" : "(Ошибка)");
        }
        else
            returnable = "Добавлен юнит " + getUnitTypeAsString() + " игроком #"  + QString::number(playerNumber)
                    + ", ряд: " + QString::number(data->row) + ", столбец: " + QString::number(data->column)
                    + ". " + (isAttemptSucced ? "(Успешно)" : "(Ошибка)");
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
            returnable = "Перемещение юнита" + QString(isAttemptSucced ? "(Успешно)" : "(Ошибка)");
        }
        else
            returnable = "Юнит был перемещен игроком #" + QString::number(playerNumber)
                    + ", нач. ряд: " + QString::number(data->rowFrom) + ", нач. столбец: " + QString::number(data->columnFrom)
                    + ", кон. ряд: " + QString::number(data->rowTo) + ", кон. столбец: " + QString::number(data->columnTo)
                    + ". " + (isAttemptSucced ? "(Успешно)" : "(Ошибка)");
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
            returnable = "Атака. " + QString(isAttemptSucced ? "(Успешно)" : "(Ошибка)");
        }
        else
            returnable = "Юнит атакован " + QString::number(playerNumber)
                    + ", ряд атакующего: " + QString::number(data->rowFrom) + ", столбец атакующего: " + QString::number(data->columnFrom)
                    + ", ряд защитника: " + QString::number(data->rowTo) + ", столбец защитника: " + QString::number(data->columnTo)
                    + ". " + (isAttemptSucced ? "(Успешно)" : "(Ошибка)");

        return returnable;
    }

    LogEventType getType() override { return ATTACK_COMMITED; }
};

