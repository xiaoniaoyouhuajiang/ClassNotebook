//
//  ConcreteWorkbenchForWeapons.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 28.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "ConcreteWorkbenchForWeapons.hpp"


NeutralObject* ConcreteWorkbenchForWeapons::CreateNeutralObject () {

       return new WorkbenchForWeapons();
   }
