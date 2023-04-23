//
// Created by vlad on 02.06.2020.
//

#ifndef UNTITLED_LOGG_H
#define UNTITLED_LOGG_H
#include <iostream>
using namespace std;

class Logg {
public:
    void creatingLog(char**);
    void movementLog(char , int , int);
    void attackLog(char , int , char);
    void deathLog(char );
    void gameoverLog();
};


#endif //UNTITLED_LOGG_H
