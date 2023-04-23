#ifndef LAB2_OOP_GAMEFIELDOUTOFRANGEEXCEPTION_H
#define LAB2_OOP_GAMEFIELDOUTOFRANGEEXCEPTION_H

#include <exception>

class GameFieldOutOfRangeException: std::exception {
 public:
  int x;
  int y;

  GameFieldOutOfRangeException(int x, int y): x(x), y(y){}
};

#endif //LAB2_OOP_GAMEFIELDOUTOFRANGEEXCEPTION_H
