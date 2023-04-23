#ifndef OOP_SESSION_H
#define OOP_SESSION_H


template<class Rule>
class GameRules{
public:
    int maxUnitCount(int square){
        Rule r;
        return r.maxUnitCount(square);
    }
    int playerHP(){
        Rule r;
        return r.playerHP;
    }
    int countUnitSteps(){
        Rule r;
        return r.stepsCount;
    }
    bool win(int unitCount){
        Rule r;
        return r.win(unitCount);
    }
};

class RuleEasy{
public:
    // create World with 10% enemies
    int maxUnitCount(int square){
        return square/20;
    }
    // set Player with hp=100
    const int playerHP = 100;
    // unit walk
    const int stepsCount = 1;
    bool win(int unitCount){
        return unitCount == 0;
    }
};

class RuleHard{
public:
    // create World with 20% enemies
    int maxUnitCount(int square){
        return square/10;
    }
    // set Player with hp=75
    const int playerHP = 75;
    // unit double walk
    const int stepsCount = 2;
    bool win(int unitCount){
        return unitCount == 1;
    }
};

#endif //OOP_SESSION_H
