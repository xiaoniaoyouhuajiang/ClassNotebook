#ifndef LABOOP_MANAGER_HPP
#define LABOOP_MANAGER_HPP

#include "commands/StartGameCommand.hpp"
#include "commands/CreateUnitCommand.hpp"
#include "commands/DeleteUnitCommand.hpp"
#include "commands/MoveUnitCommand.hpp"
#include "commands/AttackUnitCommand.hpp"
#include "commands/UnitsAttributesCommand.hpp"
#include "commands/ActionWithObjectCommand.hpp"
#include "commands/AttackBaseCommand.hpp"
#include "Memento.hpp"

class Manager {
public:
    explicit Manager(){srand(time(NULL)); gameField = new GameField; proxy = nullptr;};
    void startGame(Rules *rules);
    void setBases();
    void printField();
    void printMenu();
    void makeChoice();
    void createGamer();
    void setLogger();
    void loadGame(Memento *memento, bool first);
    void saveGame();
    bool checkWin(int, int);
private:
    GameField *gameField;
    std::map<Gamer*, Base*> bases;
    std::map<int, Gamer*> gamers;
    StartGameCommand *startCommand;
    CreateUnitCommand *createUnitCommand;
    DeleteUnitCommand *deleteUnitCommand;
    MoveUnitCommand *moveUnitCommand;
    AttackUnitCommand *attackUnitCommand;
    UnitsAttributesCommand *unitsAttributesCommand;
    ActionWithObjectCommand *actionWithObjectCommand;
    AttackBaseCommand *attackBaseCommand;
    LogProxy *proxy;
    std::vector<Memento*> mementos;
    Rules *rules;
};


#endif //LABOOP_MANAGER_HPP
