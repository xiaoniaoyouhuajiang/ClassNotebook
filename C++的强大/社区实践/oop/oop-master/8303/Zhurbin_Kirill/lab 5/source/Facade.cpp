#include "Facade.h"

void Facade::createGame() {

    /*adapter = new Adapter();

    field = new Field(8, 8, 20, adapter);
    field->addLandscape();
    field->printLandscape();


    std::cout << "---------------------------"<< std::endl;

    field->addNeutral(1, 1, 'z');
    field->addNeutral(2, 2, 'p');
    field->addNeutral(3, 3, 's');
    field->addNeutral(4, 4, 'a');
    field->printNeutral();
    std::cout << "---------------------------"<< std::endl;

    mediator = new Mediator(field);
    baseHandler = new BaseHandler();
    setBase = new SetBaseHandler(field, adapter);
    noCommand = new NoCommandHandler();
    setUnit = new SetUnitHandler(field, mediator, adapter);
    moveUnit = new MoveUnitHandler(field);
    statusBase = new StatusBaseHandler(field);
    attackUnit = new AttackUnitHandler(field);
    switchLogMode = new SwitchLogHandler(adapter);
    save = new SaveHandler(field);
    load = new LoadHandler(field, mediator);
    baseHandler->add(setBase);
    baseHandler->add(statusBase);
    baseHandler->add(moveUnit);
    baseHandler->add(setUnit);
    baseHandler->add(attackUnit);
    baseHandler->add(switchLogMode);
    baseHandler->add(save);
    baseHandler->add(load);
    baseHandler->add(noCommand);

    std::cout << "Game preparation done, you can start playing" << std::endl;*/
}



void Facade::play(std::string commandStr) {
        /*baseHandler->handle(commandStr);
        field->printAll();*/
}
