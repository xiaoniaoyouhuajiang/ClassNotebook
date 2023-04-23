#ifndef BASECONSTRUCTOR_H
#define BASECONSTRUCTOR_H
#include "Event.h"
class GameField;
class Base;


class BaseConstructor
{
private:
  GameField* field_;
  bool isMovementBase(int x, int y);
public:
  Base* createBase(Event event);
  Base* createHumanBase(int x, int y);
  Base* createChaosBase(int x, int y);
  void setField(GameField* field);
  BaseConstructor(GameField* field = nullptr);
  virtual ~BaseConstructor();
};

#endif // BASECONSTRUCTOR_H
