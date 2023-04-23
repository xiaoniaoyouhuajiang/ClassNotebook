#include <cmath>
#include "MoveUnitRequest.h"
#include "../../../Exceptions/TypeError.h"
#include "../../../Exceptions/OutofRangeError.h"
#include "../../../Exceptions/LogicalError.h"

void MoveUnitRequest::Command()
{
    std::string X, Y, I, J;
    std::cout << "-------- MOVE UNIT --------" << std::endl;
    std::cout << "from x = ";
    std::cin >> X;
    std::cout << "from y = ";
    std::cin >> Y;
    try
    {
        x = std::stoi(X);
        y = std::stoi(Y);
    }
    catch (std::exception)
    {
        throw TypeError("x (y)", "int");
    }

    if (x < 0 || x >= field->height) throw OutOfRangeError("x");
    else if (y < 0 || y >= field->width) throw OutOfRangeError("y");
    else if (field->field[x][y].object == nullptr) throw LogicalError("unit on tile (x, y) doesn't exist", "unit on tile (x, y)");
    else if (field->field[x][y].object->baseID != player[0]) throw LogicalError("unit on tile (x, y) non player property", "unit in player's property on tile (x, y)");
    else
    {
        std::cout << "to x = ";
        std::cin >> I;
        std::cout << "to y = ";
        std::cin >> J;
        try
        {
            i = std::stoi(I);
            j = std::stoi(J);
        }
        catch (std::exception)
        {
            throw TypeError("x (y)", "int");
        }

        bool isInRange = std::pow(x, 2) + std::pow(y, 2) >= std::pow(field->field[x][y].object->range.get(), 2);

        if (i < 0 || i >= field->height) throw OutOfRangeError("x");
        else if (j < 0 || j >= field->width) throw OutOfRangeError("y");
        else if (!isInRange) throw LogicalError("tile (x, y) not in the move range");
        else if (field->field[i][j].object != nullptr) throw LogicalError("tile (x, y) not empty", "empty tile (x, y)");
        field->getVision(player[0], i , j);
        field->moveObject(x, y, i, j);
        std::cout << "---------------------------" << std::endl;

    }

}