#ifndef player2_hpp
#define player2_hpp

#include <stdio.h>
#include "StateAbstract.hpp"

class Player2 : public State {
 public:
    ACTION getInputAction() override{
       std::cout << "Player2 turn!\n";
       return input();
    }
};

#endif /* player2_hpp */
