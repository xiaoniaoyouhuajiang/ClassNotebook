//
//  Cell.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 20.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "Cell.hpp"



    
    int Cell::whatHere () {
        
        if (base.length() == 2) {return 1;}
        if (neutralObject) {return 2;}
        if (unit) {return 3;}
        if (landscape) {return 4;}
    
        return 0;
    }

    
