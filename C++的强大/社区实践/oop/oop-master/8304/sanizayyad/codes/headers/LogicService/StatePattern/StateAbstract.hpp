#ifndef StateAbstract_hpp
#define StateAbstract_hpp

#include <stdio.h>
#include <iostream>
#include "action.hpp"

class Context;

class State {
    
 protected:
  Context *context_;

 public:
  virtual ~State() {
  }

  void set_context(Context *context) {
    this->context_ = context;
  }

  virtual ACTION getInputAction() = 0;
  ACTION input(){
        if (true) {
               char ac;
               std::cin>>ac;
               switch (ac) {
                   case 'a':
                       return ACTION::ATTACK;
                   case 'd':
                       return ACTION::DEFFEND;
                   case 's':
                       return ACTION::SAVE;
                   case 'l':
                       return ACTION::LOAD;
                   case 'n':
                       return ACTION::NEW;
                   case '1':
                       return ACTION::CREATE_SHORTRANGE;
                   case '2':
                       return ACTION::CREATE_LONGRANGE;
                   case '3':
                       return ACTION::CREATE_DYNAMICRANGE;
                   case 'q':
                       return ACTION::EXIT;
               }
           }
           return ACTION::NO_ACTION;
    };
};




#endif /* StateAbstract_hpp */
