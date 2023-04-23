#include "facade.h"
#include "../Field.h"


void Facade::createField()
{
    std::cout<<"< field creating: >\n";
    field = new Field(7, 7, 10, adapter);
    field->print();

    basecomm = new chainOfResponsibility();

    basecomm->add(new createBaseCor(field));
    basecomm->add(new SwitchLogCor(field));
    basecomm->add(new baseInfoCor(field));
    basecomm->add(new createUnitCor(field));
    basecomm->add(new moveUnitCor(field));

    basecomm->add(new saveCor(field));
    basecomm->add(new loadCor(field));
    basecomm->add(new uknownCmdCor);
}

void Facade::play()
{
    std::cout << "Game started" << std::endl;
    std::string commandStr;

    while (true){
        std::cin >> commandStr;
        if(commandStr=="exit") {
            std::cout << "Bye!";
            break;
        }

        basecomm->chainOR(commandStr);
        field->print();
    }
}
