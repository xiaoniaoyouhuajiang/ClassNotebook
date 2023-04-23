#include "BaseInfoReuqest.h"

void BaseInfoReuqest::Command()
{
    int number;
    if (player == "B") number = 0;
    else if (player == "D") number = 1;
    else number = 2;
    if (this->field->basesOnField[number]!= nullptr) this->field->basesOnField[number]->getInformation();
    else std::cout << "ERROR: Base doesn't exist!" << std::endl;
}