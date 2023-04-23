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
    virtual void showError(Exception* exc) = 0;
};

class GameFacade
{
private:
    IGame* game;
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

        RuleType ruleType = data->ruleType;

        switch (ruleType) {
            case FIRST:
                game = Game<FirstRule>::getInstance(true);
                break;
            case SECOND:
                game = Game<SecondRule>::getInstance(true);
                break;
        }

        logger->printLog(new NewGameLogData(data, true));

        //view->askForBasesPosition();
        view->setCurrentPlayerInfo(game->getCurrentPlayer());
    }

    void addBase(AddBaseData* data){
        try{
            game->addBase(data->row, data->column, data->possessorId);
            logger->printLog(new AddBaseLogData(data, data->possessorId, true));
        }
        catch (Exception* exc)
        {
            view->showError(exc);
            logger->printLog(new AddBaseLogData(data, data->possessorId, false));
        } catch(...) {}
        view->update(PARTICAL_UPDATE);
    }

    void addUnit(AddUnitData* data){
        try {
            game->addUnit(data->row, data->column, data->unitType, game->getCurrentPlayer());

            logger->printLog(new AddUnitLogData(data, game->getCurrentPlayer(), true));

            view->setCurrentPlayerInfo(game->getCurrentPlayer());

        } catch (Exception* exc) {

            view->showError(exc);
            logger->printLog(new AddUnitLogData(data, game->getCurrentPlayer(), false));

        } catch(...) {}
        view->update(PARTICAL_UPDATE);
    }

    void moveUnit(MoveClientData* data)
    {
        try {
            game->moveUnit(data->rowFrom, data->columnFrom, data->rowTo, data->columnTo, game->getCurrentPlayer());

            logger->printLog(new MoveUnitLogData(data, game->getCurrentPlayer(), true));

            view->setCurrentPlayerInfo(game->getCurrentPlayer());


        } catch (Exception* exc) {
            view->showError(exc);
            logger->printLog(new MoveUnitLogData(data, game->getCurrentPlayer(), false));

        } catch (...){}
        view->update(PARTICAL_UPDATE);
    }

    void attack(AttackClientData* data)
    {
        try {
            game->attack(data->rowFrom, data->columnFrom, data->rowTo, data->columnTo, game->getCurrentPlayer());

            logger->printLog(new AttackLogData(data, game->getCurrentPlayer(), true));

            view->setCurrentPlayerInfo(game->getCurrentPlayer());

            if(game->isWinner())
            {
                int winner = game->getWinner();

                if(winner != -1)
                {
                    view->showWinnerInfo(winner);
                }

            }

        } catch (Exception* exc) {

            view->showError(exc);
            logger->printLog(new AttackLogData(data, game->getCurrentPlayer(), false));

        } catch (...) {}
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

    unsigned int getPlayersAmount() { return game->getTotalPlayersAmount(); }
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

            switch (gs->ruleType) {
                case FIRST:
                    game = Game<FirstRule>::getInstance(gs, true);
                    break;
                case SECOND:
                    game = Game<SecondRule>::getInstance(gs, true);
                    break;
            }

            view->setCurrentPlayerInfo(game->getCurrentPlayer());
            view->update(TOTAL_UPDATE);

            view->onLoadingSucceed();
        } catch (Exception* exc) {

            view->showError(exc);
        } catch (...){

        }
    }
};

#endif // GAMEFACADE_H
