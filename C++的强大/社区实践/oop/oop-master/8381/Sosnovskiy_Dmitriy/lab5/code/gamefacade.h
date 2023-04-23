#ifndef GAMEFACADE_H
#define GAMEFACADE_H
#include <vector>
#include "game.h"
#include "clientinputdata.h"
#include "logger.h"

class IView{
public:
    virtual ~IView() = default;
    virtual void update(UPDATE_UI_TYPE type) = 0;
    virtual void askForBasesPosition() = 0;
    virtual void setCurrentPlayerInfo(unsigned int currentPlayer) = 0;
    virtual void showWinnerInfo(unsigned int winnerPlayer) = 0;
    virtual void onLoadingSucceed() = 0;
    virtual void showLoadingError() = 0;
};

//перенести всю логику о текущем игроке  в класс game.
// успехов!:)


class GameFacade
{
private:
    Game* game;
    IView* view;
    ILogger* logger;

public:
    GameFacade(IView* view) {
        this->view = view;
        logger = new ProxyLogger(FILE_LOGGING, FULL_INFO);
    }


    void setLoggingProperties(LoggingType logType, LogFormatType logFormat)
    {
        delete logger;
        logger = new ProxyLogger(logType, logFormat);
    }

    void startNewGame(StartNewGameData* data){

        unsigned int fieldRowSize = data->rows;
        unsigned int fieldColumnSize = data->columns;
        unsigned int maximumEntities = data->maximumEntitiesAmount;
        unsigned int playersAmount = data->playersAmount;

        game = new Game(fieldRowSize, fieldColumnSize, maximumEntities, playersAmount);


        logger->printLog(new NewGameLogData(data, true));



        view->askForBasesPosition();
        view->setCurrentPlayerInfo(game->getCurrentPlayer());
    }

    void addBase(AddBaseData* data){
        try{
            game->addBase(data->row, data->column, data->possessorId);
            logger->printLog(new AddBaseLogData(data, data->possessorId, true));
        }
        catch (...)
        {
            logger->printLog(new AddBaseLogData(data, data->possessorId, false));
        }
        view->update(PARTICAL_UPDATE);
    }

    void addUnit(AddUnitData* data){
        try {
            game->addUnit(data->row, data->column, data->unitType, game->getCurrentPlayer());

            logger->printLog(new AddUnitLogData(data, game->getCurrentPlayer(), true));

            view->setCurrentPlayerInfo(game->getCurrentPlayer());

        } catch (...) {

            logger->printLog(new AddUnitLogData(data, game->getCurrentPlayer(), false));

        }{}
        view->update(PARTICAL_UPDATE);


    }

    void moveUnit(MoveClientData* data)
    {
        try {
            game->moveUnit(data->rowFrom, data->columnFrom, data->rowTo, data->columnTo, game->getCurrentPlayer());

            logger->printLog(new MoveUnitLogData(data, game->getCurrentPlayer(), true));

            view->setCurrentPlayerInfo(game->getCurrentPlayer());


        } catch (...) {
            logger->printLog(new MoveUnitLogData(data, game->getCurrentPlayer(), false));

        }{}
        view->update(PARTICAL_UPDATE);
    }

    void attack(AttackClientData* data)
    {
        try {
            game->attack(data->rowFrom, data->columnFrom, data->rowTo, data->columnTo, game->getCurrentPlayer());

            logger->printLog(new AttackLogData(data, game->getCurrentPlayer(), true));

            view->setCurrentPlayerInfo(game->getCurrentPlayer());


        } catch (...) {

            logger->printLog(new AttackLogData(data, game->getCurrentPlayer(), false));

        }{}
        view->update(PARTICAL_UPDATE);
    }

    UnitType getUnitType(unsigned int row, unsigned int column) {
        return game->getUnitType(row, column);
    }

    CreatureType getCreatureType(unsigned int row, unsigned int column)
    {
        return  game->getCreatureType(row, column);
    }

    NeutralObjectType getNeutralObjectType(unsigned int row, unsigned int column) {
        return game->getNeutralObjectType(row, column);
    }

    QString getBaseInfo()
    {
        return game->getBaseInfo(game->getCurrentPlayer());
    }

    LandscapeType getLandscapeType(unsigned int row, unsigned int column)
    {
        return game->getLandscapeType(row, column);
    }

    unsigned int getPlayersAmount() { return game->getTotalPlayersAmonut(); }
    unsigned int getRowsAmount() { return game->getRowsAmount(); }
    unsigned int getColumnsAmount() { return game->getColumnsAmount(); }


    void saveGame(SaveGameData* data)
    {
        GameSnapshotCaretaker* caretaker = new GameSnapshotCaretaker();
        caretaker->saveGameState(data->fileName, game->createSnapshot());
    }

    void loadGame(LoadGameData* data)
    {
        try{

        GameSnapshotCaretaker* caretaker = new GameSnapshotCaretaker();
        GameSnapshot* gs = caretaker->loadGameState(data->fileName);
            game = new Game(gs);

            view->setCurrentPlayerInfo(game->getCurrentPlayer());
            view->update(TOTAL_UPDATE);

            view->onLoadingSucceed();
        } catch (...) {
            view->showLoadingError();
        }{}
    }
};

#endif // GAMEFACADE_H
