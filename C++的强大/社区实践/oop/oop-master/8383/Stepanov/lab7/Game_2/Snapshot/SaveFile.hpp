//
//  SaveFile.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 03.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef SaveFile_hpp
#define SaveFile_hpp

#include <fstream>
#include <iostream>

#include "BaseSnapshot.hpp"
#include "FieldSnapshot.hpp"

class SaveFile{
    
    std::ofstream fileIn;
    std::ifstream fileOut;
    
public:
    SaveFile(bool writeFile);
    ~SaveFile();
    
    void write(BaseSnapshot* first, BaseSnapshot* second, FieldSnapshot* field);
    
    bool reed(BaseSnapshot* first, BaseSnapshot* second, FieldSnapshot* field);

};

#endif /* SaveFile_hpp */
