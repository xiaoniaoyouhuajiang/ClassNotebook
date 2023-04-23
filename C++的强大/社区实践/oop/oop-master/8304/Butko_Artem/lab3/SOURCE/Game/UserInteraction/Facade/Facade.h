//
// Created by Artem Butko on 20/05/2020.
//

#ifndef OOP_NEW_FACADE_H
#define OOP_NEW_FACADE_H


#include "../../GameField/Field/Field.h"
#include "../ChainOfResponsibility/Chain.h"
#include "../ChainOfResponsibility/CreateBaseLink/CreateBaseLink.h"
#include "../ChainOfResponsibility/BaseInfoLink/BaseInfoLink.h"
#include "../ChainOfResponsibility/CreateUnitLink/CreateUnitLink.h"
#include "../ChainOfResponsibility/GetUnitLink/GetUnitLink.h"
#include "../ChainOfResponsibility/MoveUnitLink/MoveUnitLink.h"
#include "../ChainOfResponsibility/AttackUnitLink/AttackUnitLink.h"
#include "../ChainOfResponsibility/UnknownLink/UnknownLink.h"

/*
 * Facade -- класс, реализующий паттерн "Фасад".
 */

class Facade
{
public:
    void createGame();
    void playGame();
private:
    Field* field;
    Chain* command;
};


#endif //OOP_NEW_FACADE_H
