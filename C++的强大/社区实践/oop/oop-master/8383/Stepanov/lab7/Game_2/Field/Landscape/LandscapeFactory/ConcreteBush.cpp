//
//  ConcreteBush.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 27.03.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "ConcreteBush.hpp"

Landscape * ConcreteBush::CreateLandscap () {

    return new Bush();
}
