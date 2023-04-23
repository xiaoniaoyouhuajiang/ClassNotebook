//
//  ConcreteWorkbenchForWeapons.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 28.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef ConcreteWorkbenchForWeapons_hpp
#define ConcreteWorkbenchForWeapons_hpp

#include "NeutralObjectFactory.hpp"
#include "WorkbenchForWeapons.hpp"

class ConcreteWorkbenchForWeapons: public NeutralObjectFactory {

public:
    
    NeutralObject* CreateNeutralObject () override;
};

#endif /* ConcreteWorkbenchForWeapons_hpp */
