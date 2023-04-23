//
// Created by anton on 5/9/20.
//

#ifndef OOPROJECT_VITALITY_H
#define OOPROJECT_VITALITY_H


//#include "GameObject.h"
class GameObject;

class Vitality {
    int health;
public:
    int getHealth() const;

private:
    int armour;
    float dmgMul = 1;
    GameObject* master;

public:
    Vitality(int health, int armour, float dmgMul, GameObject *master);

public:
    void damage(int amount);
    void heal(int amount);
};


#endif //OOPROJECT_VITALITY_H
