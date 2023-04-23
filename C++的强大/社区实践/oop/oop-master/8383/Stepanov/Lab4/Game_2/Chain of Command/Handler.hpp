//
//  Handler.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 05.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef Handler_hpp
#define Handler_hpp

#include <string>

class Handler {
 public:
  virtual Handler *SetNext(Handler *handler) = 0;
  virtual bool Handle(std::string request) = 0;
};
#endif /* Handler_hpp */
