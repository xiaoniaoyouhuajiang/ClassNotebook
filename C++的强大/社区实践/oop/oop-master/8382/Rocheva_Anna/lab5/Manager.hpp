#ifndef LABOOP_MANAGER_HPP
#define LABOOP_MANAGER_HPP

#include "commands/StartGameCommand.hpp"
#include "commands/CreateUnitCommand.hpp"
#include "commands/DeleteUnitCommand.hpp"
#include "commands/MoveUnitCommand.hpp"
#include "commands/AttackUnitCommand.hpp"
#include "commands/UnitsAttributesCommand.hpp"
#include "commands/ActionWithObjectCommand.hpp"
#include "Memento.hpp"

class Manager {
public:
    explicit Manager(){srand(time(NULL)); gameField = new GameField(); proxy = nullptr;};
    void startGame();
    void printField();
    void printMenu();
    void makeChoice();
    void createGamer();
    void setLogger();
    void loadGame(Memento *memento, bool first);
    void saveGame();
private:
    GameField *gameField;
    std::map <Gamer*, Base*> bases;
    StartGameCommand *startCommand;
    CreateUnitCommand *createUnitCommand;
    DeleteUnitCommand *deleteUnitCommand;
    MoveUnitCommand *moveUnitCommand;
    AttackUnitCommand *attackUnitCommand;
    UnitsAttributesCommand *unitsAttributesCommand;
    ActionWithObjectCommand *actionWithObjectCommand;
    LogProxy *proxy;
    std::vector<Memento*> mementos;
};


#endif //LABOOP_MANAGER_HPP
