//
//  Ground.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef Ground_hpp
#define Ground_hpp

#include "Landscape.hpp"
class Unit;

class Ground: public Landscape {
    
    char getName () override;
};

#endif /* Ground_hpp */
