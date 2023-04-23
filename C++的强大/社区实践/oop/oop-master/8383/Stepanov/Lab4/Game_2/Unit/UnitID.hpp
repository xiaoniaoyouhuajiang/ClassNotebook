//
//  UnitID.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef UnitID_hpp
#define UnitID_hpp

class UnitID{
    
    int unitID; // 0 -> Smoker, 1 -> Shooter, 2 -> Runner
    
public:
    void setUnitID (int i);
    int getUnitID ();
};

#endif /* UnitID_hpp */
