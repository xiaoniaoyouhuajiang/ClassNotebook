//
//  BaseSnapshot.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 02.05.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef BaseSnapshot_hpp
#define BaseSnapshot_hpp

#include <string>
#include <vector>

class BaseSnapshot {


public:
    std::vector<std::string> names;
    std::vector<int> h;
    std::vector<int> a;
    std::vector<int> p;
    std::vector<bool> blocAtt;
    std::vector<int> ux;
    std::vector<int> uy;
    
    int numberUnit = 0;
    int countUnit = 0;
    int x = 0;
    int y = 0;
    int concretCountUnit[3] = {0, 0, 0};
    std::string name;

    BaseSnapshot(std::vector<std::string> names,
                 std::vector<int> h,
                 std::vector<int> a,
                 std::vector<int> p,
                 std::vector<bool> blocAtt,
                 std::vector<int> ux,
                 std::vector<int> uy,
                 
                 int numberUnit,
                 int countUnit,
                 int x,
                 int y,
                 int concretCountUnit[3],
                 std::string name);
    
    BaseSnapshot();
};

#endif /* BaseSnapshot_hpp */
