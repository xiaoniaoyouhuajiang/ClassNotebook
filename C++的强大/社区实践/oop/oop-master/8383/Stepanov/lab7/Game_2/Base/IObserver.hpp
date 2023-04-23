//
//  IObserver.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 20.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef IObserver_hpp
#define IObserver_hpp

class Unit;

class IObserver {

     public:
      virtual void Update(Unit *unit);
};

#endif /* IObserver_hpp */




