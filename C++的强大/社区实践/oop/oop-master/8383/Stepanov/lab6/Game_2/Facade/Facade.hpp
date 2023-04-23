//
//  Facade.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 04.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef Facade_hpp
#define Facade_hpp

#include "Field.hpp"
#include "Unit.hpp"
#include "Base.hpp"
#include "NeutralObject.hpp"

class Facade {

protected:
    Field* field;
    Base *first;
    Base *second;
    
public:
    
    Facade (Field *f, Base *first, Base *second);
    
    void printField ();
    
    void printPoints ();
    
};

#endif /* Facade_hpp */
