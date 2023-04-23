//
//  ConcreteBoxWithArmor.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 28.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef ConcreteBoxWithArmor_hpp
#define ConcreteBoxWithArmor_hpp

#include "NeutralObjectFactory.hpp"
#include "BoxWithArmor.hpp"

class ConcreteBoxWithArmor: public NeutralObjectFactory {

public:
    
    NeutralObject* CreateNeutralObject () override;
};
#endif /* ConcreteBoxWithArmor_hpp */
