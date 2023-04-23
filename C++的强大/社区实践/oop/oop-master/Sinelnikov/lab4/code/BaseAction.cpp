//
// Created by max on 01.04.20.
//

#include "BaseAction.h"

void BaseAction::setBase(Field* f){
    Interaction inter;
    inter.setBase(f);
}

void BaseAction::showCharacteristics(Field* f,Base* base) {
    f->getLog()->write("ID : " + to_string(base->getObjectId()) + "\n");
    f->getLog()->write("Здоровье " + to_string(base->getBaseXp()) + " из" + to_string(base->getMaxXp()) + "\n");
    f->getLog()->write("Количество юнитов, принадлежащих базе: " +  to_string(base->getNumberOfUnits()) + "\n");
    f->getLog()->write("Максимальное количество юнитов на базу: " +  to_string(base->getMaxNumberOfUnits()) + "\n");
    f->getLog()->write("Положение базы: " + to_string(base->getXCoord()) + " " + to_string(base->getYCoord()) + "\n");
}

void BaseAction::run(Field* f, bool &check) {
    int player_move;
    int id;
    cout << "Введите id базы: ";
    cin >> id;
    id--;
    while (1) {
        if(id >= f->getNumberOfBases() || id < 0){
            f->getLog()->write("Такой базы нет\n");
            return;
        }
        cout << "0 - вернуться на предыдущий шаг\n";
        cout << "1 - показать характеристики\n";
        cout << "2 - создать юнита\n";
        cin >> player_move;
        switch (player_move){
            case 0:
                f->getLog()->write("Опция вернуться назад\n");
                return;
            case 1:
                f->getLog()->write("Опция показать характеристики\n");
                this->showCharacteristics(f,f->field[f->getBaseXCoordinateById(id)][f->getBaseYCoordinateById(id)].getBase());
                break;
            case 2:
                f->getLog()->write("Опция создать юнита\n");
                f->field[f->getBaseXCoordinateById(id)][f->getBaseYCoordinateById(id)].getBase()->createUnit(f,check);
                break;
        }
        if(check)
            return;
    }
}