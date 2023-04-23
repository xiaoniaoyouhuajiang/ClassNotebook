#include "unit.h"

Unit::Unit(){

}

Player1Gladiator::Player1Gladiator(int x, int y){
    this->id.code = 0;
    this->x = x;
    this->y = y;
    this->hp = 400;
    this->force = 50;
    this->attackRange = 1;
    this->sym = 'G';
    this->cost = 100;
}

Player1Gunslinger::Player1Gunslinger(int x, int y){
    this->id.code = 1;
    this->x = x;
    this->y = y;
    this->hp = 250;
    this->force = 30;
    this->attackRange = 3;
    this->sym = 'S';
    this->cost = 125;
}

Player1Healer::Player1Healer(int x, int y){
    this->id.code = 2;
    this->x = x;
    this->y = y;
    this->hp = 100;
    this->force = 40;
    this->attackRange = 2;
    this->sym = 'H';
    this->cost = 150;
}

Player1Wizard::Player1Wizard(int x, int y){
    this->id.code = 3;
    this->x = x;
    this->y = y;
    this->hp = 50;
    this->force = 100;
    this->attackRange = 3;
    this->sym = 'W';
    this->cost = 200;
}

Player1Jew::Player1Jew(int x, int y){
    this->id.code = 4;
    this->x = x;
    this->y = y;
    this->hp = 1;
    this->force = 1;
    this->attackRange = 1;
    this->sym = 'J';
    this->cost = 1000;
}

Player1Kamikadze::Player1Kamikadze(int x, int y){
    this->id.code = 5;
    this->x = x;
    this->y = y;
    this->hp = 50;
    this->force = 1000;
    this->attackRange = 3;
    this->sym = 'K';
    this->cost = 50;
}

Player2Gladiator::Player2Gladiator(int x, int y){
    this->id.code = 6;
    this->x = x;
    this->y = y;
    this->hp = 400;
    this->force = 50;
    this->attackRange = 1;
    this->sym = 'G';
    this->cost = 100;
}

Player2Gunslinger::Player2Gunslinger(int x, int y){
    this->id.code = 7;
    this->x = x;
    this->y = y;
    this->hp = 250;
    this->force = 30;
    this->attackRange = 3;
    this->sym = 'S';
    this->cost = 125;
}

Player2Healer::Player2Healer(int x, int y){
    this->id.code = 8;
    this->x = x;
    this->y = y;
    this->hp = 100;
    this->force = 40;
    this->attackRange = 2;
    this->sym = 'H';
    this->cost = 150;
}

Player2Wizard::Player2Wizard(int x, int y){
    this->id.code = 9;
    this->x = x;
    this->y = y;
    this->hp = 50;
    this->force = 100;
    this->attackRange = 3;
    this->sym = 'W';
    this->cost = 200;
}

Player2Jew::Player2Jew(int x, int y){
    this->id.code = 10;
    this->x = x;
    this->y = y;
    this->hp = 1;
    this->force = 1;
    this->attackRange = 1;
    this->sym = 'J';
    this->cost = 1000;
}

Player2Kamikadze::Player2Kamikadze(int x, int y){
    this->id.code = 11;
    this->x = x;
    this->y = y;
    this->hp = 50;
    this->force = 1000;
    this->attackRange = 3;
    this->sym = 'K';
    this->cost = 50;
}

Gladiator * Player1Factory::createGladiator(int x, int y) {
    return new Player1Gladiator(x+1, y);
}

Gunslinger * Player1Factory::createGunslinger(int x, int y){
    return new Player1Gunslinger(x+1, y);
}

Healer * Player1Factory::createHealer(int x, int y){
    return new Player1Healer(x+1, y);
}

Wizard * Player1Factory::createWizard(int x, int y){
    return new Player1Wizard(x+1, y);
}

Jew * Player1Factory::createJew(int x, int y){
    return new Player1Jew(x+1, y);
}

Kamikadze * Player1Factory::createKamikadze(int x, int y){
    return new Player1Kamikadze(x+1, y);
}

Gladiator * Player2Factory::createGladiator(int x, int y) {
    return new Player2Gladiator(x-1, y);
}

Gunslinger * Player2Factory::createGunslinger(int x, int y){
    return new Player2Gunslinger(x-1, y);
}

Healer * Player2Factory::createHealer(int x, int y){
    return new Player2Healer(x-1, y);
}
Wizard * Player2Factory::createWizard(int x, int y){
    return new Player2Wizard(x-1, y);
}

Jew * Player2Factory::createJew(int x, int y){
    return new Player2Jew(x-1, y);
}

Kamikadze * Player2Factory::createKamikadze(int x, int y){
    return new Player2Kamikadze(x-1, y);
}
