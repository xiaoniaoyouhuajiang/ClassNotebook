//
//  ProxyLog.hpp
//  Game_2
//
//  Created by Владислав  Степанов on 20.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#ifndef ProxyLog_hpp
#define ProxyLog_hpp

#include <fstream>
#include <iostream>
#include <string>

class ProxyLog {
    
    std::ofstream outFile;
    bool isFile;
    bool logMotions;
  
    
public:
    
    ProxyLog(bool logMotions, bool isFile);
    ~ProxyLog ();
    
    void write (std::string s);
    
    
};
#endif /* ProxyLog_hpp */
