#ifndef LABOOP_STRATEGY_HPP
#define LABOOP_STRATEGY_HPP

#include "../units/Unit.hpp"

class Strategy {
public:
    virtual ~Strategy(){};
    virtual void changeAttributes(Unit &unit) = 0;
};

class UnitContext{
public:
    UnitContext(Strategy *strategy = nullptr) : strategy(strategy) {};
    ~UnitContext() {delete strategy;};
    void setStrategy(Strategy *strategy) {delete this->strategy; this->strategy = strategy;};
    void changeUnitsAttributes(Unit &unit) {this->strategy->changeAttributes(unit);};
private:
    Strategy *strategy;
};

class HospitalStrategyPeople : public Strategy{
public:
    void changeAttributes(Unit &unit) override{
        unit.changeAttributes(0, 0, 100);
    }
};

class HospitalStrategyOther : public Strategy{
public:
    void changeAttributes(Unit &unit) override{
        unit.changeAttributes(0, 0, 50);
    }
};

class BarStrategy : public Strategy{
public:
    void changeAttributes(Unit &unit) override{
        unit.changeAttributes(100, 0, -20);
    }
};

class ShopStrategyScoutTank : public Strategy{
public:
    void changeAttributes(Unit &unit) override{
        unit.changeAttributes(0, 200, 0);
    }
};

class ShopStrategyOther : public Strategy{
public:
    void changeAttributes(Unit &unit) override{
        unit.changeAttributes(0, 100, 0);
    }
};

class TrainStrategyPeople : public Strategy{
public:
    void changeAttributes(Unit &unit) override{
        unit.changeAttributes(100, 0, -10);
    }
};

class TrainStrategyOther : public Strategy{
public:
    void changeAttributes(Unit &unit) override{
        unit.changeAttributes(100, 0, 0);
    }
};

#endif //LABOOP_STRATEGY_HPP
