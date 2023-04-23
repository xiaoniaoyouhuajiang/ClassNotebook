
#include "WeaponBehavior.h"
#include <cstdlib>
#define N 0.4

Sword::Sword(){
    this->baseDamage = 25;
    this->extraRandomDamage = 5;
    this->radius = 1;
    this->againstMagicArmor = 85;
    this->againstPhysicalArmor = 15;
}

Dagger::Dagger(){
    this->baseDamage = 20;
    this->extraRandomDamage = 15;
    this->radius = 1;
    this->againstMagicArmor = 55;
    this->againstPhysicalArmor = 45;
}

Hands::Hands(){
    this->baseDamage = 20;
    this->extraRandomDamage = 5;
    this->radius = 2;
    this->againstMagicArmor = 30;
    this->againstPhysicalArmor = 70;
}

Lance::Lance(){
    this->baseDamage = 20;
    this->extraRandomDamage = 10;
    this->radius = 2;
    this->againstMagicArmor = 45;
    this->againstPhysicalArmor = 55;
}

Bow::Bow(){
    this->baseDamage = 15;
    this->extraRandomDamage = 10;
    this->radius = 3;
    this->againstMagicArmor = 70;
    this->againstPhysicalArmor = 30;
}


Staff::Staff(){
    this->baseDamage = 20;
    this->extraRandomDamage = 5;
    this->radius = 3;
    this->againstMagicArmor = 15;
    this->againstPhysicalArmor = 85;
}


int WeaponBehavior::damageСalculation(int magicResistance, int armor, int againstMA, int againstPA){
    float onMageArm = ((1.0 - (float)againstMA/100)+(1.0-(float)magicResistance/100))*N;
    float onPhArm = ((1.0 - (float)againstPA/100)+(1.0-(float)armor/100))*N;
    float damageReduction = onMageArm + onPhArm;
    int damage = baseDamage*damageReduction;
    return damage;
}
int WeaponBehavior::damageСalculation(int magicResistance, int armor){
    return damageСalculation(magicResistance, armor, againstMagicArmor, againstPhysicalArmor);
}

int Sword::useWeapon(int distance, int magicResistance, int armor){
    int damage = damageСalculation(magicResistance, armor);
    damage += rand() % extraRandomDamage;
    return damage;
}


int Lance::useWeapon(int distance, int magicResistance, int armor){
    float multiplier = 0;
    if(distance == 1){
        multiplier = 1;
    }
    else{
        multiplier = 0.7;
    }
    int damage = damageСalculation(magicResistance, armor) * multiplier;
    damage += rand() % extraRandomDamage;
    return damage;
}


int Bow::useWeapon(int distance, int magicResistance, int armor){
    float multiplier = 0;
    if(distance == 1){
        multiplier = 0.6;
    }
    else if(distance == 2){
       multiplier = 1;
    }
    else{
        multiplier = 1.5;
    }
    int damage = damageСalculation(magicResistance, armor) * multiplier;
    damage += rand() % extraRandomDamage;
    return damage;
}


int Dagger::useWeapon(int distance, int magicResistance, int armor){
   int damage = damageСalculation(magicResistance, armor);
    damage += rand() % extraRandomDamage;
    return damage;
}


int Staff::useWeapon(int distance, int magicResistance, int armor){
    int againstMA = againstMagicArmor;
    int againstPA = againstPhysicalArmor;
    if(distance == 1){
        againstMA += 50;
        againstPA += 0;
    }
    else if(distance <= 4){
        againstMA -= 10;
        againstPA += 15;
    }
    else{
        againstMA -= 20;
        againstPA += 15;
    }
    int damage = damageСalculation(magicResistance, armor, againstMA, againstPA);
    damage += rand() % extraRandomDamage;
    return damage;
}


int Hands::useWeapon(int distance, int magicResistance, int armor){
    int againstMA = againstMagicArmor;
       int againstPA = againstPhysicalArmor;
       if(distance > 1){
           againstMA -= 15;
           againstPA += 30;
       }
       int damage = damageСalculation(magicResistance, armor, againstMA, againstPA);
       damage += rand() % extraRandomDamage;
       return damage;
    return 20;
}

