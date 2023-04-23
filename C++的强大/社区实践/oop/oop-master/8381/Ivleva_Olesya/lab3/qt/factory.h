#include <iostream>
#include <string>
using namespace std;
#pragma once
#include <item.h>

class AbstractFactory {
 public:
  virtual Unit *CreateUnitA(IObserver *observer) = 0;
  virtual Unit *CreateUnitB(IObserver *observer) = 0;
};


class ConcreteFactoryDragon : public AbstractFactory {
 public:
    virtual Unit *CreateUnitA(IObserver *observer){
        return new Dragons_red(observer);
    }

    virtual Unit *CreateUnitB(IObserver *observer){
        return new Dragons_green(observer);
    }
};

/**
 * Каждая Конкретная Фабрика имеет соответствующую вариацию продукта.
 */
class ConcreteFactoryWarrior : public AbstractFactory {
 public:
  virtual Unit *CreateUnitA(IObserver *observer){
    return new Warrior_fight(observer);
  }
  virtual Unit *CreateUnitB(IObserver *observer){
    return new Warrior_ronin(observer);
  }
};

class ConcreteFactorySentry : public AbstractFactory {
 public:
  virtual Unit *CreateUnitA(IObserver *observer){
    return new Sentry_fire(observer);
  }
  virtual Unit *CreateUnitB(IObserver *observer){
    return new Sentry_lion(observer);
  }
};



