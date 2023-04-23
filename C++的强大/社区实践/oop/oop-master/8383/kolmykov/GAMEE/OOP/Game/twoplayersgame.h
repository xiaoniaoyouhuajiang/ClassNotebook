#ifndef TWOPLAYERSGAME_H
#define TWOPLAYERSGAME_H


#include "Game.h"
#include "twoplayersrule.h"
#include <memory>
#include "Field.h"
#include "LogerProxy.h"
#include "FileLoger.h"
#include "LogerAdapter.h"
#include "Facade.h"
#include "towersettingstate.h"
#include "unitsettingstate.h"
#include "SignalMaker.h"


template<>
class Game<TwoPlayersRule> : public GameInterface {
private:
    static Game<TwoPlayersRule>* instance;

    size_t stepNumber = 0;

    std::shared_ptr<State> currState;
    std::shared_ptr<Field> field;
    std::shared_ptr<Mediator> mediator;
    std::shared_ptr<LogerAdapter> loger;
    std::shared_ptr<Facade> facadeH;
    std::shared_ptr<Facade> facadeZ;

    std::shared_ptr<State> stateSTH;
    std::shared_ptr<State> stateSTZ;
    std::shared_ptr<State> stateSUZ;
    std::shared_ptr<State> stateSUH;

    std::shared_ptr<SignalMaker> signalMaker;

    Game<TwoPlayersRule>() {
        signalMaker = std::shared_ptr<SignalMaker>(new SignalMaker);
    }

    ~Game<TwoPlayersRule>() {

    }

public:

    static Game<TwoPlayersRule>* getInstance() {
        if (instance == nullptr) {
            instance = new Game<TwoPlayersRule>;
        }
        return instance;
    }



    void startNewGame(int h, int w) {
        field = std::shared_ptr<Field>(new Field(h, w));
        std::shared_ptr<Mediator> mediator(new Mediator(field));
        std::shared_ptr<LogerAdapter> loger(new LogerAdapter(std::shared_ptr<LogerProxy>(new FileLoger(std::shared_ptr<Loger>(new Loger)))));
        mediator->setLoger(loger);
        field->setMediator(mediator);
        facadeH = std::shared_ptr<Facade>(new Facade(Kind::HUMAN, field));
        facadeZ = std::shared_ptr<Facade>(new Facade(Kind::ZOMBY, field));
        stateSTH = std::shared_ptr<State>(new TowerSettingState(Kind::HUMAN, 2, field, facadeH));
        stateSTZ = std::shared_ptr<State>(new TowerSettingState(Kind::ZOMBY, 1, field, facadeZ));
        stateSUH = std::shared_ptr<State>(new UnitSettingState(Kind::HUMAN, 2, field, facadeH));
        stateSUZ =  std::shared_ptr<State>(new UnitSettingState(Kind::ZOMBY, 1, field, facadeZ));
        stateSTZ->setNextState(stateSTH);
        stateSTH->setNextState(stateSUZ);
        stateSUZ->setNextState(stateSUH);
        stateSUH->setNextState(stateSUZ);
        currState = stateSTZ;
        field->printField();
    }

    std::shared_ptr<Field> getField() {
        return field;
    }

    void create(int xT, int xU, UnitType type) {
        currState->create(xT, xU, type);
    }

    void endStep() {
        stepNumber++;
        currState->renewResources();
        currState = currState->getNextState();
        int y;
        signalMaker->makeStateChangeSignal(currState->getKind());
        switch(currState->getKind()) {
        case Kind::HUMAN:
            y = field->getHeight() - 1;
            break;
        case Kind::ZOMBY:
            y = 0;
            break;
        default:
            break;
        }
        for (int x = 0; x < field->getWidth(); x++) {
            std::shared_ptr<Tower> tower = field->getCell(x, y)->getTower();
            if(tower != nullptr) {
                tower->attack();
            }
        }
        for (int y = field->getHeight() - 2; y > 0; y--) {
            for (int x = field->getWidth() - 1; x >= 0; x--) {
                std::shared_ptr<Unit> unit = field->getCell(x, y)->getUnit();
                if (unit != nullptr && unit->getKind() == currState->getKind() && unit->getLastStep() != stepNumber) {
                    unit->performMove();
                    unit->performAttack();
                    unit->setLastStep(stepNumber);
                }
            }
        }
        field->createObj();
        field->isGameEnd(currState->getKind());
    }


    Kind getKind() {
        return currState->getKind();
    }

    std::shared_ptr<SignalMaker> getSignalMaker() {
        return signalMaker;
    }

    void saveGame() {
        Saver saver(GameMode::TWO_PLAYERS_GAME, stepNumber, field, currState);
        saver.save();
    }

    void setStepNumber(size_t stepNumber) {
        this->stepNumber = stepNumber;
    }

    void setField(std::shared_ptr<Field> field) {
        this->field = field;
    }

    void setStates(std::shared_ptr<State> state) {
        std::shared_ptr<LogerAdapter> loger(new LogerAdapter(std::shared_ptr<LogerProxy>(new FileLoger(std::shared_ptr<Loger>(new Loger)))));
        field->getMediator()->setLoger(loger);
        facadeH = std::shared_ptr<Facade>(new Facade(Kind::HUMAN, field));
        facadeZ = std::shared_ptr<Facade>(new Facade(Kind::ZOMBY, field));
        stateSTH = std::shared_ptr<State>(new TowerSettingState(Kind::HUMAN, 2, field, facadeH));
        stateSTZ = std::shared_ptr<State>(new TowerSettingState(Kind::ZOMBY, 1, field, facadeZ));
        stateSUH = std::shared_ptr<State>(new UnitSettingState(Kind::HUMAN, 2, field, facadeH));
        stateSUZ =  std::shared_ptr<State>(new UnitSettingState(Kind::ZOMBY, 1, field, facadeZ));

        if (state->getKind() == Kind::ZOMBY && state->getType() == StateType::TOWER_SETTING_STATE) {
            stateSTZ = state;
        }
        else if (state->getKind() == Kind::HUMAN && state->getType() == StateType::TOWER_SETTING_STATE) {
            stateSTH = state;
        }
        else if(state->getKind() == Kind::ZOMBY && state->getType() == StateType::UNIT_SETTING_STATE) {
            stateSUZ = state;
        }
        else if(state->getKind() == Kind::HUMAN && state->getType() == StateType::UNIT_SETTING_STATE) {
            stateSUH = state;
        }

        currState = state;

        stateSTZ->setNextState(stateSTH);
        stateSTH->setNextState(stateSUZ);
        stateSUZ->setNextState(stateSUH);
        stateSUH->setNextState(stateSUZ);

        signalMaker->makeStateChangeSignal(state->getKind());
        field->printField();
    }
};




#endif // TWOPLAYERSGAME_H
