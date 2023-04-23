#include <iostream>
#include <string>
using namespace std;

class Battle{
protected:
    int radius_attack = 0; //Радиус атаки
    int attack = 0; //Атака
    int accuracy = 0; //Точность
    int attack_speed = 0; //Скорость атаки

public:
    Battle(int rad, int att, int acc, int att_sp): radius_attack(rad), attack(att), accuracy(acc), attack_speed(att_sp){

    }

    Battle(){}

    void add_attack(int bonus_attack){
        attack += bonus_attack;
    }

    int get_attack(){
        return attack;
    }
};
