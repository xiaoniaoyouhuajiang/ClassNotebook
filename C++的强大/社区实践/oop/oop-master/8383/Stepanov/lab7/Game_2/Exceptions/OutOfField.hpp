//
//  OutOfField.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 18.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef OutOfField_hpp
#define OutOfField_hpp

#include <iostream>


class OutOfField {
    
private:
    int x, y;
    
public:
    OutOfField(int x, int y);
    int getX();
    int getY();
    void writeErr();

    
    
};

#endif /* OutOfField_hpp */
