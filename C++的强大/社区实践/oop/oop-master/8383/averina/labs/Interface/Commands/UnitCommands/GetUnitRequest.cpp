
#include <iostream>
#include "GetUnitRequest.h"
#include "GetUnitRequest.h"
#include "../../../Exceptions/LogicalError.h"
#include "../../../Exceptions/OutofRangeError.h"
#include "../../../Exceptions/TypeError.h"

void GetUnitRequest::Command()
{
    int number, X, Y;

    std::cout << "--------- GET UNIT --------" << std::endl;
    std::cout << "'C' - Crossbowman" << std::endl;
    std::cout << "'A' - Archer" << std::endl;
    std::cout << "'W' - Wizard" << std::endl;
    std::cout << "'M' - Mage" << std::endl;
    std::cout << "'K' - Knight" << std::endl;
    std::cout << "'S' - Spearman" << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "id = ";
    std::cin >> this->id;
    if (this->id != 'C' && this->id != 'A' && this->id != 'W' && this->id != 'M' && this->id != 'K' && this->id != 'S') throw LogicalError( "id (doesn't exist)" );
    std::cout << "x = ";
    std::cin >> X;
    std::cout << "y = " ;
    std::cin >> Y;
    try
    {
        this->x = X;
        this->y = Y;
    }
    catch(std::exception)
    {
        throw  TypeError("x (y)", "int");
    }

    if (x < 0 || x >= field->height) throw OutOfRangeError("x");
    else if (y < 0 || y >= field->width) throw OutOfRangeError("y");

    if (player == "B")
    {
        if (x > 2 || y > 2) throw LogicalError("tile on (x, y) not near the Kindom", "tiles near the Kindom (0, 2); (1, 2); (2, 2); (2, 1); (2, 0)");
        number = 0;
    }
    else if (player == "D")
    {
        if (x < 7 || y < 7) throw LogicalError("tile on (x, y) not near the Kindom", "tiles near the Kindom (9, 7); (8, 7); (7, 7); (7, 8); (7, 9)");
        number = 1;
    }
    else
    {
        if (x < 7 || y > 2) throw LogicalError("tile on (x, y) not near the Kindom", "tiles near the Kindom (7, 0); (7, 1); (7, 2); (8, 2); (9, 2)");
        number = 2;
    }
    if (field->field[x][y].object != nullptr) throw LogicalError("tile on (x, y) is busy");
    if (this->field->basesOnField[number]->unitsOnBase[this->id] == 0) throw LogicalError("unit is absent at the base", "create unit or choose different unit");
    std::cout << "---------------------------" << std::endl;
    field->addObject(this->field->basesOnField[number]->getUnit(this->id), this->x, this->y);
}