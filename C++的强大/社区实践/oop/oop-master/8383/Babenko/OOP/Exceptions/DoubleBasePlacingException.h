#ifndef LAB2_OOP_DOUBLEBASEPLACINGEXCEPTION_H
#define LAB2_OOP_DOUBLEBASEPLACINGEXCEPTION_H

#include <exception>

class DoubleBasePlacingException: std::exception {
 public:
  int playerIndex;
  explicit DoubleBasePlacingException(int playerIndex): playerIndex(playerIndex){}
};

#endif //LAB2_OOP_DOUBLEBASEPLACINGEXCEPTION_H
