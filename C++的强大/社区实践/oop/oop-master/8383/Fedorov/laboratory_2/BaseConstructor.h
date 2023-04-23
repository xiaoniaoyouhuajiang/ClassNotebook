#ifndef BASECONSTRUCTOR_H
#define BASECONSTRUCTOR_H
class GameField;
class Base;


class BaseConstructor
{
private:
  //HumanFactory* human_factor;
  //ChaosFactory* chaos_factor;
  GameField* field_;
  bool isMovementBase(int x, int y);
public:
  Base* createHumanBase(int x, int y);
  Base* createChaosBase(int x, int y);
  BaseConstructor(GameField*);
  virtual ~BaseConstructor();
};

#endif // BASECONSTRUCTOR_H
