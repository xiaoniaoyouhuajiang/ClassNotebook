//
//  ConcreteBoxWithArmor.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 28.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "ConcreteBoxWithArmor.hpp"

NeutralObject* ConcreteBoxWithArmor::CreateNeutralObject () {

    return new BoxWithArmor();
}
