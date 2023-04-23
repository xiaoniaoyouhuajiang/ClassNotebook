//
//  AbstractHandler.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 05.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef AbstractHandler_hpp
#define AbstractHandler_hpp

#include <string>

#include "Handler.hpp"

class AbstractHandler : public Handler {

 public:
  Handler *next_handler_;

  
    AbstractHandler();
  
    Handler *SetNext(Handler *handler) override;
    

};

#endif /* AbstractHandler_hpp */
