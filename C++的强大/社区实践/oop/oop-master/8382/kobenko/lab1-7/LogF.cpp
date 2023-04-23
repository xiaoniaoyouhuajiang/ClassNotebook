//
// Created by vlad on 02.06.2020.
//

#include "LogF.h"

void LogF::creatingLog(char **field) {
    fout.open("/home/vlad/Clion/log.txt", ios::app);
    if(fout.is_open()) {
        fout << "The field was created, like this: \n";
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++)
                fout << field[i][j];
            fout << endl;
        }
    }
    fout.close();
}

void LogF::movementLog(char choose, int x , int y) {
    fout.open("/home/vlad/Clion/log.txt", ios::app);
    if(fout.is_open()) {
        fout << "Unit " << choose << " moved to (" << x << ", " << y << ")" << endl;
    }
    fout.close();
}

void LogF::attackLog(char choose, int attack, char enemy) {
    fout.open("/home/vlad/Clion/log.txt", ios::app);
    if(fout.is_open()) {
        fout << "Unit " << choose << " attacked -" << attack << " unit " << enemy << endl;
    }
    fout.close();
}

void LogF::deathLog(char choose) {
    fout.open("/home/vlad/Clion/log.txt", ios::app);
    if (fout.is_open()) {
        fout << "Unit " << choose << " is dead" << endl;
    }
    fout.close();
}

void LogF::gameoverLog() {
    fout.open("/home/vlad/Clion/log.txt", ios::app);
    if (fout.is_open()) {
        fout << "Game over" << endl;
    }
    fout.close();
}
