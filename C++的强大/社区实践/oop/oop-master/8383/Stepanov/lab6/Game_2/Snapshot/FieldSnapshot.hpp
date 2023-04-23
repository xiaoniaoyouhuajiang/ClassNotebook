//
//  FieldSnapshot.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 02.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef FieldSnapshot_hpp
#define FieldSnapshot_hpp

class FieldSnapshot {

public:
    
    int height, width;
    char ** place;
    
    int busyCells;
    int maxBusyCells;
    
    FieldSnapshot(int height,
                  int width,
                  char** place,
                  int busyCells,
                  int maxBusyCells);
    
     FieldSnapshot();
};



#endif /* FieldSnapshot_hpp */
