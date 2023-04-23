//
// Created by max on 05.03.20.
//

#include "Base.h"
#include "Field.h"

int Base::getBaseXp() {
    return this->basexp;
}

int Base::getMaxNumberOfUnits() {
    return this->max_number_of_units;
}

int Base::getNumberOfUnits() {
    return this->number_of_units;
}

int Base::getMaxXp() {
    return 10;
}

void Base::increaseNumberOfUnits(int amount) {
    this->number_of_units += amount;
}

void Base::decreaseNumberOfUnits(int amount) {
    this->number_of_units -= amount;
}

void Base::increaseXp(int amount) {
    this->basexp + amount < this->getMaxXp() ? this->basexp += amount : this->basexp = this->getMaxXp();
}

void Base::decreaseXp(int amount) {
    this->basexp-=amount;
}

void Base::createUnit(Field* f,bool &check) {
    int x,y,unit_id;
    cout << "Создать лучника - 1\n";
    cout << "Создать арбалетчика - 2\n";
    cout << "Создать копейщика - 3\n";
    cout << "Создать мечника - 4\n";
    cout << "Создать лёгкого кавалера - 5\n";
    cout << "Создать тяжёлого кавалера - 6\n";
    cin >> unit_id;
    if(unit_id < 1 || unit_id > 6){
        f->getLog()->write("Неправильно задан юнит!!!\n");
        return;
    }
    while (1) {
        cout << "Завдайте местоположение размещения\n";
        cin >> x >> y;
        if(x >= f->getXsize() || y >= f->getYsize() || x < 0 || y < 0)
            f->getLog()->write("Выход за пределы поля!!!\n");
        else
            if(abs(x - this->getXCoord()) > 3 || abs(y - this->getYCoord()) > 3) {
                f->getLog()->write("Слишком далеко от базы\n");
                return;
            }
            else
                if(f->getLandscapeName(f->field[x][y].getLandscape()->getObjectId()) == "water" ||
                f->getLandscapeName(f->field[x][y].getLandscape()->getObjectId()) == "mountain"){
                    f->getLog()->write("На эти природные объекты создавать нельзя\n");
                    return;
                }
                else
                    if(f->field[x][y].getIfOccupiedByUnit()) {
                        f->getLog()->write("Место занято! Выберите другое\n");
                    return;
                }
                else
                    break;
    }
    unit_id--;
    if(x < f->getXsize() && y < f->getYsize() && x >= 0 && y>= 0){
        if(!this->getNumberOfUnits() + 1 < this->getMaxNumberOfUnits()){
            f->increaseNumberOfObjects();
            switch(unit_id) {
                case 0:
                    f->field[x][y].setElement(new Bowman);
                    f->getLog()->write("Пользователь выбрал лучника\n");
                    break;
                case 1:
                    f->field[x][y].setElement(new Crossbowman);
                    f->getLog()->write("Пользователь выбрал арбалетчика\n");
                    break;
                case 2:
                    f->field[x][y].setElement(new Spearman);
                    f->getLog()->write("Пользователь выбрал копейщика\n");
                    break;
                case 3:
                    f->field[x][y].setElement(new Swordsman);
                    f->getLog()->write("Пользователь выбрал мечника\n");
                    break;
                case 4:
                    f->field[x][y].setElement(new LightCavalry);
                    f->getLog()->write("Пользователь выбрал лёгкого кавалера\n");
                    break;
                case 5:
                    f->field[x][y].setElement(new HardCavalry);
                    f->getLog()->write("Пользователь выбрал тяжёлого кавалера\n");
                    break;
            }
            f->field[x][y].getUnit()->setId(this->getObjectId());
            f->field[x][y].getUnit()->setNumberInArray(f->getNumberOfUnits());
            f->addUnitToArray(x,y);
            this->increaseNumberOfUnits(1);
            f->field[x][y].setOccupiedByUnit(true);
            check = true;
            f->getLog()->write("Юнит создан\n");
        }
    }
}
