//
// Created by vlad on 02.06.2020.
//

#include "Logg.h"

void Logg::creatingLog(char **field) {
    cout << "The field was created, like this: \n";
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++)
            cout << field[i][j];
        cout << endl;
    }
}

void Logg::movementLog(char choose, int x , int y) {
    cout << "Unit " << choose << " moved to (" << x << ", " << y << ")" << endl;
}

void Logg::attackLog(char choose, int attack, char enemy) {
    cout << "Unit " << choose << " attacked -" << attack << " unit " << enemy << endl;
}

void Logg::deathLog(char choose) {
    cout << "Unit " << choose << " is dead" << endl;
}

void Logg::gameoverLog() {
    cout << "Game over" << endl;
}