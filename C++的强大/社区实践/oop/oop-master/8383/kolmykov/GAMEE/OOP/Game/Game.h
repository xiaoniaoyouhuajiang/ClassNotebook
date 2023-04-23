#pragma once
#include "gameinterface.h"
#include "state.h"
#include <QObject>
#include <SignalMaker.h>
#include "LogerAdapter.h"
#include "LogerProxy.h"
#include "FileLoger.h"
#include "towersettingstate.h"
#include "unitsettingstate.h"
#include "Saver.h"


template <typename T>
class Game : public GameInterface {
private:
    static Game<T>* instance;

    size_t stepNumber = 0;

    std::shared_ptr<State> currState;
    std::shared_ptr<Field> field;
    std::shared_ptr<Mediator> mediator;
    std::shared_ptr<LogerAdapter> loger;
    std::shared_ptr<Facade> facadeH;
    std::shared_ptr<Facade> facadeZ;

    std::shared_ptr<State> towerSettingState;
    std::shared_ptr<State> unitSettingState;
    std::shared_ptr<State> computerTST;
    std::shared_ptr<State> computerUST;

    std::shared_ptr<SignalMaker> signalMaker;

    std::map<UnitType, int> price = {{UnitType::BITING_ZOMBY, 2}, {UnitType::HUMAN_ON_CAR, 3}, {UnitType::STINKY_ZOMBY, 1}, {UnitType::STRONG_ZOMBY, 3}, {UnitType::HUMAN_ON_BIKE, 3}, {UnitType::HUMAN_WITH_BAT, 1}, {UnitType::HUMAN_WITH_GUN, 2}, {UnitType::KAMIKADZE_ZOMBY, 3}, {UnitType::HUMAN_WITH_SWORD, 2}, {UnitType::HUMAN_WITH_GRENADE, 1}, {UnitType::SPIT_TO_AREA_ZOMBY, 1}, {UnitType::SPIT_TO_ENEMY_ZOMBY, 2} };

    Game<T>() {
        signalMaker = std::shared_ptr<SignalMaker>(new SignalMaker);
    }

    ~Game<T>() {

    }

public:
    static Game<T>* getInstance() {
        if (instance == nullptr) {
            instance = new Game<T>();
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
        towerSettingState = std::shared_ptr<State>(new TowerSettingState(Kind::HUMAN, 2, field, facadeH));
        computerTST = std::shared_ptr<State>(new TowerSettingState(Kind::ZOMBY, 1, field, facadeZ));
        unitSettingState = std::shared_ptr<State>(new UnitSettingState(Kind::HUMAN, 2, field, facadeH));
        computerUST =  std::shared_ptr<State>(new UnitSettingState(Kind::ZOMBY, 1, field, facadeZ));

        computerTST->setNextState(towerSettingState);
        towerSettingState->setNextState(computerUST);
        computerUST->setNextState(unitSettingState);
        unitSettingState->setNextState(computerUST);
        currState = computerTST;
        makeComputerTowerSetting();
        currState = towerSettingState;
        signalMaker->makeStateChangeSignal(currState->getKind());
        field->printField();
    }

    std::shared_ptr<Field> getField() {
        return field;
    }

    void create(int xT, int xU, UnitType type) {
        currState->create(xT, xU, type);
    }

    void endStep() {//add computer step
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
        checkGameEnd();
        if(currState->getKind() == Kind::ZOMBY) {
            makeComputerUnitSetting();
            endStep();
        }
    }

    bool checkGameEnd() {
        return field->isGameEnd(currState->getKind());
    }

    Kind getKind() {
        return currState->getKind();
    }

    std::shared_ptr<SignalMaker> getSignalMaker() {
        return signalMaker;
    }

    void makeComputerTowerSetting() {
        for(int i = 0; i < field->getWidth(); i++) {
            UnitType type;
            int typeRand = rand()%6;
            switch (typeRand) {
            case 0:
                type = UnitType::BITING_ZOMBY;
                break;
            case 1:
                type = UnitType::STINKY_ZOMBY;
                break;
            case 2:
                type = UnitType::STRONG_ZOMBY;
                break;
            case 3:
                type = UnitType::KAMIKADZE_ZOMBY;
                break;
            case 4:
                type = UnitType::SPIT_TO_AREA_ZOMBY;
                break;
            case 5:
                type = UnitType::SPIT_TO_ENEMY_ZOMBY;
                break;
            }
            create(i, 0, type);
        }
    }

    void makeComputerUnitSetting() {
        bool isTowerChosen = false;
        bool isChooseEnd = false;
        while(!isChooseEnd) {
            std::cout <<"chose\n";
            int xT = rand()% field->getWidth();
            int xU;
            int tmpXT = xT;
            std::cout << "xT " << xT << std::endl;
            while(xT < field->getWidth()) {
                std::cout <<"+t\n";
                std::shared_ptr<Tower> tower = field->getCell(xT, 0)->getTower();
                if (tower == nullptr || price[tower->getFactory()->getType()] > currState->getResources() || !tower->canCreateUnit()) {
                    xT++;
                    isTowerChosen = false;
                }
                else {
                    isTowerChosen = true;
                    break;
                }
            }
            if (!isTowerChosen) {
                while(tmpXT >= 0) {
                    std::cout <<"-t\n";
                    std::shared_ptr<Tower> tower = field->getCell(tmpXT, 0)->getTower();
                    if (tower == nullptr || price[tower->getFactory()->getType()] > currState->getResources() || !tower->canCreateUnit()) {
                        tmpXT--;
                        isTowerChosen = false;
                    }
                    else {
                        isTowerChosen = true;
                        break;
                    }
                }
                xT = tmpXT;
            }
            if(isTowerChosen) {
                xU = getRandomFreeCell();
                std::cout << "xU " << xU << std::endl;
                if(xU != -1) {
                    std::cout << xT << " " << xU << std::endl;
                    create(xT, xU, UnitType::BITING_ZOMBY);
                }
            }
            if(!isTowerChosen || xU == -1 || currState->getResources() == 0) {
                isChooseEnd = true;
            }
        }
    }


    int getRandomFreeCell() {
        bool isCellFounded = false;
        int x = rand()%field->getWidth();
        int tmpX = x;
        while(x < field->getWidth()) {
            std::cout <<"c\n";
            if (field->getCell(x, 1)->getUnit() != nullptr) {
                x++;
            }
            else {
                isCellFounded = true;
                break;
            }
        }
        if (!isCellFounded) {
            while(tmpX >= 0) {
                std::cout <<"c\n";
                if (field->getCell(tmpX, 1)->getUnit() != nullptr) {
                    tmpX--;
                }
                else {
                    isCellFounded = true;
                    break;
                }
            }
            x = tmpX;
        }
        return x;
    }

    void saveGame() {
        Saver saver(GameMode::SOLO_GAME, stepNumber, field, currState);
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
        towerSettingState = std::shared_ptr<State>(new TowerSettingState(Kind::HUMAN, 2, field, facadeH));
        computerTST = std::shared_ptr<State>(new TowerSettingState(Kind::ZOMBY, 1, field, facadeZ));
        unitSettingState = std::shared_ptr<State>(new UnitSettingState(Kind::HUMAN, 2, field, facadeH));
        computerUST =  std::shared_ptr<State>(new UnitSettingState(Kind::ZOMBY, 1, field, facadeZ));

        if (state->getType() == StateType::UNIT_SETTING_STATE) {
            unitSettingState = state;
        }
        else {
            towerSettingState = state;
        }

        computerTST->setNextState(towerSettingState);
        towerSettingState->setNextState(computerUST);
        computerUST->setNextState(unitSettingState);
        unitSettingState->setNextState(computerUST);

        currState = state;

        signalMaker->makeStateChangeSignal(currState->getKind());
        field->printField();
    }
};
