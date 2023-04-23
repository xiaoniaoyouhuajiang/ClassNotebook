
#include "CreateUnitRequest.h"
#include "../../../Exceptions/LogicalError.h"

void CreateUnitRequest::Command()
{
    int number;
    if (player == "B") number = 0;
    else if (player == "D") number = 1;
    else number = 2;
    if (this->field->basesOnField[number]!= nullptr)
    {
        std::cout << "------ CREATING UNIT ------" << std::endl;
        std::cout << "'C' - Crossbowman" << std::endl;
        std::cout << "'A' - Archer" << std::endl;
        std::cout << "'W' - Wizard" << std::endl;
        std::cout << "'M' - Mage" << std::endl;
        std::cout << "'K' - Knight" << std::endl;
        std::cout << "'S' - Spearman" << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << "id = ";
        std::cin >> this->id;
        if (this->id != 'C' && this->id != 'A' && this->id != 'W' && this->id != 'M' && this->id != 'K' && this->id != 'S')
            throw LogicalError( "id (doesn't exist)" );
        std::cout << "---------------------------" << std::endl;
        field->basesOnField[number]->createUnit(this->id);
        field->logging->loggingCreateUnit(this->id);
    }
    else std::cout << "ERROR: Base doesn't exist!" << std::endl;

}