#include <iostream>

class Unit{
public:
    int x, y;
    int healh, armor, attack;
public:
    void move(int newX, int newY){
        this->x = newX;
        this->y = newY;
    }
};


class Field{
    int lenghtX, lengthY;
    int maxCountObject;
    int countUnit;
    Unit** masUnit;

public:
    Field(int x, int y, int maxCountObject){
        this->lenghtX = x;
        this->lengthY = y;
        this->countUnit = 0;
        this->maxCountObject = maxCountObject;
        masUnit = new Unit*[this->maxCountObject];
    }

    Field(const Field& field) : lenghtX(field.lenghtX), lengthY(field.lengthY), maxCountObject(field.maxCountObject), countUnit(field.countUnit), masUnit(new Unit*[field.maxCountObject]){
        for (int i=0; i<countUnit; i++)
            masUnit[i] = field.masUnit[i];

    }

    void addUnit(Unit* unit){
        if (unit->x <= this->lenghtX   &&   unit->y <= this->lengthY   &&   this->countUnit < this->maxCountObject) {
            masUnit[this->countUnit] = unit;
            this->countUnit++;
        }
    }

    void removeUnit(Unit* unit){
        for (int i=0; i<this->countUnit; i++){
            if (masUnit[i] == unit){
                delete masUnit[i];
                for (int j=i; j<this->countUnit-1; j++)
                    masUnit[j] = masUnit[j+1];
                this->countUnit--;
                return;
            }
        }
    }

    void printAllUnit(){
        for (int i=0; i<this->countUnit; i++){
            std::cout << masUnit[i]->x << " " << masUnit[i]->y << std::endl;
        }
    }
};

class Soldier: public  Unit{
};

class YoungSoldier: public Soldier{
public:
    YoungSoldier(int x, int y){
        this->x = x;
        this->y = y;
        this->healh = 500;
        this->attack = 50;
        this->armor = 20;
    }
};

class OldSoldier: public Soldier{
public:
    OldSoldier(int x, int y){
        this->x = x;
        this->y = y;
        this->healh = 400;
        this->attack = 70;
        this->armor = 30;
    }
};

class Shooter: public Unit{

};

class KeenShooter: public Shooter{
public:
    KeenShooter(int x, int y){
        this->x = x;
        this->y = y;
        this->healh = 300;
        this->attack = 100;
        this->armor = 10;
    }
};

class SlantingShooter: public Shooter{
public:
    SlantingShooter(int x, int y){
        this->x = x;
        this->y = y;
        this->healh = 350;
        this->attack = 40;
        this->armor = 15;
    }
};

class Tank: public Unit{

};

class LightTank: public Tank{
public:
    LightTank(int x, int y){
        this->x = x;
        this->y = y;
        this->healh = 100;
        this->attack = 150;
        this->armor = 200;
    }
};

class HeavyTank: public Tank{
public:
    HeavyTank(int x, int y){
        this->x = x;
        this->y = y;
        this->healh = 200;
        this->attack = 100;
        this->armor = 250;
    }
};

int main() {
    Field* field = new Field(7, 7, 3);
    Unit* unit1 = new LightTank(3, 5);
    Unit* unit2 = new KeenShooter(4, 6);
    Unit* unit3 = new OldSoldier(2, 1);

    field->addUnit(unit1);
    field->addUnit(unit2);
    field->addUnit(unit3);

    Field* newField = new Field(*field);
    newField->removeUnit(unit2);

    field->printAllUnit();
    return 0;
}
