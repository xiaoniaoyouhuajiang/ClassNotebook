#ifndef GAMEFACADE_H
#define GAMEFACADE_H
#include <vector>
#include "game.h"
#include "clientInputData.h"
#include "logger.h"

class ViewInterface{
public:
    virtual ~ViewInterface() = default;
    virtual void update() = 0;
    virtual void askForBasesPosition() = 0;
    virtual void setCurrentPlayerInfo(unsigned int currentPlayer) = 0;
    virtual void showWinnerInfo(unsigned int winnerPlayer) = 0;
};

class GameFacade
{
private:

    unsigned int currentPlayer;
    unsigned int totalPlayersAmount;
    std::vector<unsigned int> playersAlive;
    Game* game;
    ViewInterface* view;
    LoggerInterface* logger;

    void switchCurrentPlayer()
    {
        for(unsigned int i = 0; i < playersAlive.size(); i++)
        {
            if(game->isPlayerAlive(playersAlive[i]) == false)
            {
                playersAlive.erase(playersAlive.begin() + i);
                i--;
            }
        }

        if(playersAlive.size() == 1)
        {
            view->showWinnerInfo(currentPlayer);
            return;
        }
        else
        {
            do
            {
                currentPlayer = (currentPlayer + 1) % totalPlayersAmount;
            } while (game->isPlayerAlive(currentPlayer) == false);

            view->setCurrentPlayerInfo(currentPlayer);
        }
    }

public:
    GameFacade(ViewInterface* view)
    {
        this->view = view;
        logger = new ProxyLogger(FILE_LOGGING, FULL_INFO);
    }


    void setLoggingProperties(LoggingType logType, LogFormatType logFormat)
    {
        delete logger;
        logger = new ProxyLogger(logType, logFormat);
    }

    void startNewGame(StartNewGameData* data)
    {

        unsigned int fieldRowSize = data->rows;
        unsigned int fieldColumnSize = data->columns;
        unsigned int maximumEntities = data->maximumEntitiesAmount;
        unsigned int playersAmount = data->playersAmount;

        this->totalPlayersAmount = playersAmount;
        this->currentPlayer = 0;

        playersAlive.clear();
        for(unsigned int i = 0; i < playersAmount; i++)
        {
            playersAlive.push_back(i);
        }

        game = new Game(fieldRowSize, fieldColumnSize, maximumEntities, playersAmount);
        logger->printLog(new NewGameLogData(data, true));
        view->askForBasesPosition();
        view->setCurrentPlayerInfo(currentPlayer);
    }

    void addBase(AddBaseData* data)
    {
        try
        {
            game->addBase(data->row, data->column, data->possessorId);
            logger->printLog(new AddBaseLogData(data, data->possessorId, true));
        }
        catch (...)
        {
            logger->printLog(new AddBaseLogData(data, data->possessorId, false));
        }
        view->update();
    }

    void addUnit(AddUnitData* data)
    {
        try
        {
            game->addUnit(data->row, data->column, data->unitType, currentPlayer);

            logger->printLog(new AddUnitLogData(data, currentPlayer, true));
        } catch (...)
        {
            logger->printLog(new AddUnitLogData(data, currentPlayer, false));
        }
        {
        }
        view->update();
        switchCurrentPlayer();
    }

    void moveUnit(MoveClientData* data)
    {
        try
        {
            game->moveUnit(data->rowFrom, data->columnFrom, data->rowTo, data->columnTo, currentPlayer);

            logger->printLog(new MoveUnitLogData(data, currentPlayer, true));
        } catch (...)
        {
            logger->printLog(new MoveUnitLogData(data, currentPlayer, false));

        }
        {
        }
        view->update();
        switchCurrentPlayer();
    }

    void attack(AttackClientData* data)
    {
        try
        {
            game->attack(data->rowFrom, data->columnFrom, data->rowTo, data->columnTo, currentPlayer);
            logger->printLog(new AttackLogData(data, currentPlayer, true));
        } catch (...)
        {
            logger->printLog(new AttackLogData(data, currentPlayer, false));
        }
        {

        }
        view->update();
        switchCurrentPlayer();
    }

    UnitType getUnitType(unsigned int row, unsigned int column)
    {
        return game->getUnitType(row, column);
    }

    CreatureType getCreatureType(unsigned int row, unsigned int column)
    {
        return  game->getCreatureType(row, column);
    }

    NeutralObjectType getNeutralObjectType(unsigned int row, unsigned int column)
    {
        return game->getNeutralObjectType(row, column);
    }

    QString getBaseInfo()
    {
        return game->getBaseInfo(currentPlayer);
    }

    LandscapeType getLandscapeType(unsigned int row, unsigned int column)
    {
        return game->getLandscapeType(row, column);
    }

    unsigned int getPlayersAmount()
    {
        return totalPlayersAmount;
    }
    unsigned int getRowsAmount()
    {
        return game->getRowsAmount();
    }
    unsigned int getColumnsAmount()
    {
        return game->getColumnsAmount();
    }
};

#endif // GAMEFACADE_H
