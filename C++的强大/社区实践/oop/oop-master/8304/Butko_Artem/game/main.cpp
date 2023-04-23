#include <iostream>
#include "Field/Object/ObjectFabric.h"
#include "Field/GameField.h"
#include "Field/Object/Base.h"

int main() {
    ObjectFabric fabric;
    Base player1;
    GameField field(10, 10);
    field.addObject(player1.createBase(), 5, 5);
    player1.createUnit('A');
    field.addObject(player1.getUnit('A', 1), 3, 3);
    field.addObject(fabric.createTrap(), 2, 2);
    field.printField();
}
