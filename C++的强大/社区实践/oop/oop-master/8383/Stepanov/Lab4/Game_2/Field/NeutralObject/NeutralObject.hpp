//
//  NeutralObject.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 28.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef NeutralObject_hpp
#define NeutralObject_hpp

class Unit;

class NeutralObject {
    
public:
    virtual Unit* operator +=  (Unit* unit)  = 0;
    virtual char* getName () = 0;
    
};

#endif /* NeutralObject_hpp */
