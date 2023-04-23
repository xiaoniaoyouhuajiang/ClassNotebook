//
//  ProxyLog.cpp
//  Game_2
//
//  Created by Владислав  Степанов on 20.04.2020.
//  Copyright © 2020 Владислав  Степанов. All rights reserved.
//

#include "ProxyLog.hpp"

ProxyLog::ProxyLog(bool logMotions, bool isFile) {
     
    if (logMotions && isFile) {
        outFile.open("./LogFile.txt");
    }
    
    this -> logMotions = logMotions;
    this -> isFile = isFile;
    
}

ProxyLog:: ~ProxyLog (){
    
    if (logMotions && isFile){
        outFile.close();
    }
}

void ProxyLog::write (std::string s){
    
    if (logMotions && isFile){
        outFile << s << std::endl;
    } else if (logMotions){
        std::cout << s << std::endl;
    }

    
}
