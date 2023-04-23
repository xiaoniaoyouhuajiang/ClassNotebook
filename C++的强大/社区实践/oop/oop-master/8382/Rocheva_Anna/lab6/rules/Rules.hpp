#ifndef LABOOP_RULES_HPP
#define LABOOP_RULES_HPP

#include "../GameField.hpp"

enum START_CONDITION {ANGLE, CENTER}; // базы в углах или в центре
enum VICTORY_CONDITION {BASE, UNITS}; // уничтожить либо базу, либо всех юнитов

class Rules {
public:
    virtual START_CONDITION getStartCondition() = 0;
    virtual VICTORY_CONDITION getVictoryCondition() = 0;
    virtual int getCurrentGamer() = 0;
    virtual bool isWin(Base *base) = 0;
};

class DamageBase : public Rules {
public:
    explicit DamageBase() : currentGamer(0), firstTurn(true) {};
    START_CONDITION getStartCondition() override {
        return CENTER;
    }
    VICTORY_CONDITION getVictoryCondition() override {
        return BASE;
    }
    int getCurrentGamer() override {
        firstTurn = false;
        if (currentGamer == 0){
            currentGamer = 1;
            return 0;
        } else if (currentGamer == 1){
            currentGamer = 0;
            return 1;
        }
    };
    bool isWin(Base *base) override{
        return !base->isExist(); // true, если база уже не существует
    }

private:
    int currentGamer;
    bool firstTurn;
};

class KillUnits : public Rules {
public:
    explicit KillUnits() : currentGamer(0), firstTurn(true){};
    START_CONDITION getStartCondition() override {
        return ANGLE;
    }
    VICTORY_CONDITION getVictoryCondition() override {
        return UNITS;
    }
    int getCurrentGamer() override {
        if (currentGamer == 0){
            currentGamer = 1;
            return 0;
        } else if (currentGamer == 1){
            currentGamer = 0;
            return 1;
        }
    };
    bool isWin(Base *base) override{
        if (firstTurn){
            firstTurn = false;
            return false;
        }
        return base->getUnits().empty();
    }
private:
    int currentGamer;
    bool firstTurn;
};


#endif //LABOOP_RULES_HPP
