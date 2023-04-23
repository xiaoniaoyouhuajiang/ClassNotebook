#include <iostream>

class Healh{
public:
    int health;
    int stamina;
};

class Armor{
public:
    int helmet;
    int vest;
};

class Attack{
public:
    int strongAttack;
    int ligthAttack;
};

class Unit: public Healh, public Armor, public Attack{
public:
    int x, y;
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
    Unit*** mapUnit;
    Unit** masUnit;

public:
    Field(int x, int y, int maxCountObject){
        this->lenghtX = x;
        this->lengthY = y;
        this->countUnit = 0;
        this->maxCountObject = maxCountObject;

        mapUnit = new Unit**[this->lengthY];
        for (int i=0; i<this->lengthY; i++) {
            mapUnit[i] = new Unit *[x];
            for (int j=0; j<this->lenghtX; j++)
                mapUnit[i][j] = nullptr;
        }

        masUnit = new Unit*[this->maxCountObject];
    }

    Field(const Field& field) : lenghtX(field.lenghtX), lengthY(field.lengthY), maxCountObject(field.maxCountObject), countUnit(field.countUnit), mapUnit(new Unit**[field.lengthY]){
        for (int i=0; i<field.lengthY; i++) {
            mapUnit[i] = new Unit *[field.lenghtX];
            for (int j=0; j<field.lenghtX; j++) {
               mapUnit[i][j] = field.mapUnit[i][j];

            }
        }
    }

    Field(Field&& field) : lenghtX(field.lenghtX), lengthY(field.lengthY), maxCountObject(field.maxCountObject), countUnit(field.countUnit), mapUnit(new Unit**[field.lengthY]){
        for (int i=0; i<field.lengthY; i++) {
            mapUnit[i] = new Unit *[field.lenghtX];
            for (int j=0; j<field.lenghtX; j++)
                mapUnit[i][j] = field.mapUnit[i][j];
        }
    }


    void addUnit(Unit* unit){
        if (unit->x < this->lenghtX   &&   unit->y < this->lengthY   &&   this->countUnit < this->maxCountObject) {
            mapUnit[unit->y][unit->x] = unit;
            masUnit[this->countUnit] = unit;
            this->countUnit++;
        }
    }


    class Iterator{

        Unit** cur;

    public:
        Iterator(Unit** first) : cur(first){

        }

        Unit*& operator+ (int n) {return *(cur+n);}
        Unit*& operator- (int n) {return *(cur-n);}
        Unit*& operator++ (int n) {return *cur++;}
        Unit*& operator-- (int n) {return *cur--;}
        Unit*& operator++ () {return *++cur;}
        Unit*& operator-- () {return *--cur;}
        bool operator!= (const Iterator& iter) {return cur!=iter.cur;}
        bool operator== (const Iterator& iter) {return cur==iter.cur;}
        Unit*& operator* () {return *cur;}
    };

    Iterator begin() { return masUnit;}
    Iterator end() {return masUnit+this->countUnit;}

    void removeUnit(Unit* unit){
        for (int i=0; i<this->lengthY; i++){
            for (int j=0; j<this->lenghtX; j++)
            if (mapUnit[i][j] == unit){
                delete mapUnit[i][j];
                mapUnit[i][j] = nullptr;
                this->countUnit--;
                return;
            }
        }
    }

    void printAllUnit(){
        for (int i=0; i<this->lengthY; i++){
            for (int j=0; j<this->lenghtX; j++)
                if (mapUnit[i][j] != nullptr){
                    std::cout << "1 ";
                }
                else{
                    std::cout << "0 ";
                }
            std::cout << std::endl;
            }
        }

        void moveUnit(Unit* unit, int x, int y) {
            mapUnit[unit->y][unit->x] = nullptr;
            unit->move(x,y);
            mapUnit[unit->y][unit->x] = unit;
        }
    };

class Soldier: public  Unit{
};

class YoungSoldier: public Soldier{
public:
    YoungSoldier(int x, int y){
        this->x = x;
        this->y = y;
        this->health = 500;
        this->vest = 50;
        this->strongAttack = 20;
        this->stamina = 200;
        this->helmet = 30;
        this->ligthAttack = 10;
    }
};

class OldSoldier: public Soldier{
public:
    OldSoldier(int x, int y){
        this->x = x;
        this->y = y;
        this->health = 400;
        this->strongAttack = 70;
        this->vest = 30;
        this->stamina = 300;
        this->helmet = 10;
        this->ligthAttack = 50;
    }
};

class Shooter: public Unit{

};

class KeenShooter: public Shooter{
public:
    KeenShooter(int x, int y){
        this->x = x;
        this->y = y;
        this->health = 300;
        this->strongAttack = 100;
        this->vest = 10;
        this->stamina = 200;
        this->helmet = 5;
        this->ligthAttack = 50;
    }
};

class SlantingShooter: public Shooter{
public:
    SlantingShooter(int x, int y){
        this->x = x;
        this->y = y;
        this->health = 350;
        this->strongAttack = 40;
        this->vest = 15;
        this->stamina = 200;
        this->helmet = 10;
        this->ligthAttack = 30;
    }
};

class Tankman: public Unit{

};

class LightTankman: public Tankman{
public:
    LightTankman(int x, int y){
        this->x = x;
        this->y = y;
        this->health = 100;
        this->strongAttack = 150;
        this->vest = 200;
        this->stamina = 50;
        this->helmet = 100;
        this->ligthAttack = 100;
    }
};

class HeavyTankman: public Tankman{
public:
    HeavyTankman(int x, int y){
        this->x = x;
        this->y = y;
        this->health = 200;
        this->strongAttack = 100;
        this->vest = 250;
        this->stamina = 100;
        this->helmet = 100;
        this->ligthAttack = 50;
    }
};



int main() {

    Field* field = new Field(7, 7, 5);
    Unit* unit1 = new LightTankman(2, 4);
    Unit* unit2 = new KeenShooter(4, 2);
    Unit* unit3 = new OldSoldier(2, 6);

    field->addUnit(unit1);
    field->addUnit(unit2);
    field->addUnit(unit3);

    field->printAllUnit();
    std::cout << "---------------------------"<< std::endl;

    field->moveUnit(unit1, 0, 0);
    field->moveUnit(unit2, 1, 1);
    field->printAllUnit();

    std::cout << "---------------------------"<< std::endl;

    Field* newField = new Field(*field);
    newField->printAllUnit();
    std::cout << "---------------------------"<< std::endl;

    Field::Iterator iter = field->begin();
    while (iter != field->end()){
        std::cout << iter.operator*()->health << std::endl;
        iter++;
    }


    return 0;
}
