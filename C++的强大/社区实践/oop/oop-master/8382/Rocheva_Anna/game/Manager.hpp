#ifndef LABOOP_MANAGER_HPP
#define LABOOP_MANAGER_HPP

#include "GameField.hpp"
#include "commands/StartGameCommand.hpp"
#include "commands/CreateUnitCommand.hpp"
#include "commands/DeleteUnitCommand.hpp"
#include "commands/MoveUnitCommand.hpp"
#include "commands/AttackUnitCommand.hpp"
#include "commands/UnitsAttributesCommand.hpp"
#include "commands/ActionWithObjectCommand.hpp"

class Manager {
public:
    Manager(){srand(time(NULL)); gameField = new GameField();};
    void startGame();
    void printField();
    void printMenu();
    void makeChoice();
private:
    GameField *gameField;
    StartGameCommand *startCommand;
    CreateUnitCommand *createUnitCommand;
    DeleteUnitCommand *deleteUnitCommand;
    MoveUnitCommand *moveUnitCommand;
    AttackUnitCommand *attackUnitCommand;
    UnitsAttributesCommand *unitsAttributesCommand;
    ActionWithObjectCommand *actionWithObjectCommand;
};


#endif //LABOOP_MANAGER_HPP
