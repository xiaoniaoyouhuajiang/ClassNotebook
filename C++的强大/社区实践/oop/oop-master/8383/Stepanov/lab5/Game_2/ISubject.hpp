//
//  ISubject.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 25.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef ISubject_hpp
#define ISubject_hpp

class IObserver;

class ISubject {
 public:
   ~ISubject();
  virtual void Attach(IObserver *observer);
  virtual void Detach(IObserver *observer);
  virtual void Notify();
};


#endif /* ISubject_hpp */
