//
//  ISubject.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 25.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "ISubject.hpp"

ISubject::~ISubject(){};
void ISubject::Attach(IObserver *observer){}
void ISubject::Detach(IObserver *observer){}
void ISubject::Notify(){}
