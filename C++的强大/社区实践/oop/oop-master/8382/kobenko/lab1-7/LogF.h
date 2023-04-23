//
// Created by vlad on 02.06.2020.
//

#ifndef UNTITLED_LOGF_H
#define UNTITLED_LOGF_H
#include <fstream>

using namespace std;

class LogF {
public:
    void creatingLog(char**);
    void movementLog(char , int , int);
    void attackLog(char , int , char);
    void deathLog(char );
    void gameoverLog();
private:
    std:: ofstream fout;
};


#endif //UNTITLED_LOGF_H
