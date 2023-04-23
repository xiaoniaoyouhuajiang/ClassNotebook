//
// Created by Artem Butko on 20/05/2020.
//

#include "BaseInfoCommand.h"

void BaseInfoCommand::Command()
{
    if (field->base != nullptr) field->base->getInformation();
    else std::cout << "ERROR: Base doesn't exist!" << std::endl;
}
