//
//  ErrorSpec.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 18.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef ErrorSpec_hpp
#define ErrorSpec_hpp

#include <iostream>
#include <string>

class ErrorSpec {
    
private:
    int type;
    int num;
    std::string name;
    
public:
    
    ErrorSpec(std::string);
    ErrorSpec (int num);
    
    std::string getName ();
    int getNum();
    
    void writeErr();
    
    
    
    
    
};

#endif /* ErrorSpec_hpp */
