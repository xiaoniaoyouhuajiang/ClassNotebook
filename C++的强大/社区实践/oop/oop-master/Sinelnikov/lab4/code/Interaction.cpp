//
// Created by max on 31.03.20.
//

#include "Interaction.h"

void Interaction::setBase(Field *f) {
    int x,y;
    while (1){
        cout << "Введите координаты базы 1" << "\n";
        cin >> x >> y;
        if(x < f->getXsize() && y < f->getYsize() && x >= 0 && y>= 0 && !f->field[x][y].getIfOccupiedByBuilding()){
            if(f->getLandscapeName(f->field[x][y].getLandscape()->getObjectId()) != "water" \
            && f->getLandscapeName(f->field[x][y].getLandscape()->getObjectId()) != "mountain") {
                f->createBase(x, y);
                f->getLog()->write("База установлена\n");
                break;
            } else{
                f->getLog()->write("В данных природных условиях базу не поставить!!!\n");
            }

        } else
            if(x < f->getXsize() && y < f->getYsize()) {
                f->getLog()->write("На это место базу поставить нельзя! Поле занято ");
                f->getLog()->write(f->getNeutralObjectName(f->field[x][y].getNeutralObject()->getObjectId()));
                f->getLog()->write("\n");
            }
            else
                f->getLog()->write("Выход за пределы поля!!!\n");
    }
    while (1){
        cout << "Введите координаты базы 2" << "\n";
        cin >> x >> y;
        if(x < f->getXsize() && y < f->getYsize() && x >= 0 && y>= 0 && !f->field[x][y].getIfOccupiedByBuilding()){
            if(f->getLandscapeName(f->field[x][y].getLandscape()->getObjectId()) != "water" \
            && f->getLandscapeName(f->field[x][y].getLandscape()->getObjectId()) != "mountain") {
                f->createBase(x, y);
                f->getLog()->write("База установлена\n");
                break;
            } else{
                f->getLog()->write("В данных природных условиях базу не поставить!!!\n");
            }

        } else {
            f->getLog()->write("На это место базу поставить нельзя! Поле занято ");
            f->getLog()->write(f->getNeutralObjectName(f->field[x][y].getNeutralObject()->getObjectId()));
            f->getLog()->write("\n");
        }
    }
}

void Interaction::services(Field* f,Unit *unit, NeutralObject *object, bool &check) {
    object->operator+(unit);
    f->getLog()->write("услуга оказана\n");
    check = true;
}

void Interaction::repair(Field* f, Base* base, bool &check) {
    base->increaseXp(2);
    f->getLog()->write("Прочность базы улучшена\n");
    check = true;
}

void Interaction::killUnit(Field* f, Unit *unit, int x, int y) {
    f->field[f->getBaseXCoordinateById(f->field[x][y].getUnit()->getId())][f->getBaseYCoordinateById(f->field[x][y].getUnit()->getId())].getBase()->decreaseNumberOfUnits(1);
    f->deleteUnit(x,y);
    f->deleteUnitFromArray(unit->getNumberInArray());
}

void Interaction::battleWithUnit(Field* f,bool &check,Unit* unit1,Unit* unit2,int x1,int y1,int x2,int y2){
    check = true;
    if(unit1->getAttack() + unit1->getMoral() + unit1->getArmour() > unit2->getArmour() + unit2->getAttack() + unit2->getMoral()){
        f->getLog()->write("Юнит с номером ");
        f->getLog()->write(to_string(f->field[x2][y2].getUnit()->getNumberInArray()));
        f->getLog()->write(" погиб \n");
        this->killUnit(f,f->field[x2][y2].getUnit(),x2,y2);
        f->move(x1,y1,x2,y2,check);
        f->field[x1][y1].getUnit()->decreaseXp(f->field[x1][y1].getUnit()->getXp() / 2);
        f->field[x1][y1].getUnit()->increaseMoral(2);
    } else if(unit2->getAttack() + unit2->getMoral() + unit2->getArmour() > unit1->getArmour() + unit1->getAttack() + unit1->getMoral()){
        this->killUnit(f,f->field[x1][y1].getUnit(),x1,y1);
        f->field[x2][y2].getUnit()->decreaseXp(f->field[x2][y2].getUnit()->getXp() / 2);
        f->field[x2][y2].getUnit()->increaseMoral(2);
    } else{
        f->field[x2][y2].getUnit()->decreaseXp(f->field[x2][y2].getUnit()->getXp() / 2 + 1);
        f->field[x1][y1].getUnit()->decreaseXp(f->field[x1][y1].getUnit()->getXp() / 2 + 1);
        if(f->field[x1][y1].getUnit()->getXp() <= 0){
            f->getLog()->write("Юнит с номером ");
            f->getLog()->write(to_string(f->field[x1][y1].getUnit()->getNumberInArray()));
            f->getLog()->write(" погиб \n");
            this->killUnit(f,f->field[x1][y1].getUnit(),x1,y1);
        }
        if(f->field[x2][y2].getUnit()->getXp() <= 0){
            f->getLog()->write("Юнит с номером ");
            f->getLog()->write(to_string(f->field[x2][y2].getUnit()->getNumberInArray()));
            f->getLog()->write(" погиб \n");
            this->killUnit(f,f->field[x2][y2].getUnit(),x2,y2);
        }
    }
}

void Interaction::attackBase(Field* f, bool &check,int x1,int y1,int x2,int y2) {
    if(f->field[x1][y1].getUnit()->getAttack() / 2 + f->field[x1][y1].getUnit()->getMoral() / 5 >= f->field[x2][y2].getBase()->getBaseXp()){
        f->destroyBase(f->field[x2][y2].getBase()->getObjectId());
    } else{
        f->field[x2][y2].getBase()->decreaseXp(f->field[x1][y1].getUnit()->getAttack() / 2 + f->field[x1][y1].getUnit()->getMoral() / 5);
    }
    check = true;
}

void Interaction::attack(Field* f,Unit* curr_unit,bool &check,int x,int y) {
    bool check1,check2;
    bool check_on_fit_to_field;
    int player_move;
    Unit* enemy_unit;
    int x_new,y_new;
    while (1) {
        check_on_fit_to_field = false;
        check1 = false;
        check = false;
        cout << "0 - вернуться на шаг назад\n";
        cout << "1 - аттаковать направо\n";
        cout << "2 - аттаковать налево\n";
        cout << "3 - аттаковать наверх\n";
        cout << "4 - аттаковать вниз\n";
        int ch;
        cin >> ch;
        if(!ch)
            break;
        switch (ch) {
            case 3:
                x_new = x + 1;
                y_new = y;
                if(y_new >= f->getYsize()){
                    f->getLog()->write("Выход за пределы поля!!!\n");
                    break;
                }
                check_on_fit_to_field = true;
                break;
            case 4:
                x_new = x - 1;
                y_new = y;
                if(y_new < 0){
                    f->getLog()->write("Выход за пределы поля!!!\n");
                    break;
                }
                check_on_fit_to_field = true;
                break;
            case 2:
                x_new = x;
                y_new = y - 1;
                if(x_new < 0){
                    f->getLog()->write("Выход за пределы поля!!!\n");
                    break;
                }
                check_on_fit_to_field = true;
                break;
            case 1:
                x_new = x;
                y_new = y + 1;
                if(x_new >= f->getXsize()){
                    f->getLog()->write("Выход за пределы поля!!!\n");
                    break;
                }
                check_on_fit_to_field = true;
                break;
            default:
                break;
        }
        if(!check_on_fit_to_field)
            continue;
        while (1) {
            cout << "0 - вернуться на шаг назад\n";
            if (f->field[x_new][y_new].getIfOccupiedByUnit() &&
                f->field[x_new][y_new].getUnit()->getId() != curr_unit->getId()) {
                cout << "1 - Атаковать вражеского юнита\n";
                check1 = true;
            }
            if (f->field[x_new][y_new].getBase() != nullptr && f->field[x_new][y_new].getBase()->getObjectId() != f->field[x][y].getUnit()->getId()) {
                cout << "2 - Атаковать базу\n";
                check2 = true;
            }
            if(!check1 && !check2){
                f->getLog()->write("На этом поле нет объектов/юнитов для атаки\n");
                break;
            }
            cin >> player_move;
            if(!player_move)
                break;
            switch (player_move){
                case 1:
                    enemy_unit = f->field[x_new][y_new].getUnit();
                    if(check1)
                        this->battleWithUnit(f,check,curr_unit,enemy_unit,x,y,x_new,y_new);
                    break;
                case 2:
                    if(check2)
                        this->attackBase(f,check,x,y,x_new,y_new);
                    break;
                default:
                    break;
            }
            if(check)
                break;
        }
        if(check)
            break;
    }
}
