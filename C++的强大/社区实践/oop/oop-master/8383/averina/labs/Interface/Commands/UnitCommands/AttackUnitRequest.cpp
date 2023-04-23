#include <cmath>
#include "AttackUnitRequest.h"
#include "../../../Exceptions/LogicalError.h"
#include "../../../Exceptions/OutofRangeError.h"
#include "../../../Exceptions/TypeError.h"


void AttackUnitRequest::Command()
{
    std::cout << "-------- ATTACK --------" << std::endl;
    std::string X, Y, I, J;
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

    if (x < 0 || x >= field->height) throw OutOfRangeError("x");   // обработка выхода за границыы введенных координат
    else if (y < 0 || y >= field->width) throw OutOfRangeError("y");
    else if (field->field[x][y].object == nullptr) throw LogicalError("unit on tile (x, y) doesn't exist", "unit on tile (x, y)");
    else if (field->field[x][y].object->baseID != player[0] && field->field[x][y].object->id != 'B' && field->field[x][y].object->id != 'U' && field->field[x][y].object->id != 'D') throw LogicalError("unit on tile (x, y) non player property", "unit in player's property on tile (x, y)");
    else
    {
        std::cout << "to x = ";
        std::cin >> I;
        std::cout << "to y = ";
        std::cin >> J;
        try
        {
            i = std::stoi(I);   //  преобразуем строки в числа
            j = std::stoi(J);
        }
        catch (std::exception)      // исключение некорректного типа данных
        {
            throw TypeError("x (y)", "int");
        }
        std::cout << "---------------------------" << std::endl;
        bool isInRange = std::pow(x, 2) + std::pow(y, 2) >= std::pow(field->field[x][y].object->damage.getRange(), 2);
        if (i < 0 || i >= field->height) throw OutOfRangeError("x");
        else if (j < 0 || j >= field->width) throw OutOfRangeError("y");
        else if (!isInRange) throw LogicalError("tile (x, y) not in the damage range");
        if (field->field[i][j].object == nullptr)
        {
            std::cout << "Unit miss!" << std::endl;
            return;
        }

        if (player == "B" && field->field[i][j].isBrightView)
        {
            if (field->field[i][j].object->baseID == 'B') throw LogicalError("your unit on this tile");
            field->makeDamage(x, y, i, j);
        }
        else if (player == "D" && field->field[i][j].isDarkView)
        {
            if (field->field[i][j].object->baseID == 'D') throw LogicalError("your unit on this tile");
            field->makeDamage(x, y, i, j);
        }
        else if (player == "U" && field->field[i][j].isUndeadView)
        {
            if (field->field[i][j].object->baseID == 'U') throw LogicalError("your unit on this tile");
            field->makeDamage(x, y, i, j);
        }
        else return;
    }
}