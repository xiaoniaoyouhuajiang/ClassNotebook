#ifndef LABOOP_MEMENTO_HPP
#define LABOOP_MEMENTO_HPP

#include <iostream>
#include <ctime>
#include <fstream>
#include <map>

#include "GameField.hpp"
#include "loggers/LogProxy.hpp"
#include "Gamer.hpp"

#define MAXLANDNAME 3
#define MAXOBJNAME 3
#define MAXUNITNAME 5

typedef struct {
    int UnitName;
    Coordinates *coordinates;
    int attack;
    int defense;
    int health;
} UnitState;
typedef struct {
    Coordinates *coordinates;
    int health;
    int numUnits;
    std::vector<UnitState*> units;
} BaseState;
typedef struct {
    std::pair<int, int> size; // width, height
    std::vector<std::pair<int, Coordinates*>> lands;
    std::vector<std::pair<int, Coordinates*>> objects;
    std::map <std::string, BaseState*> bases; // gamer name, base
} GameState;


class Memento{
public:
    Memento (std::string path) : path(path) { if (path == "-") return; stateDoc.open(path);};
    ~Memento() {if (path == "-") return; stateDoc.close();}
    void loadGameFromDoc();
    void saveGame(GameField *gameField, std::map <Gamer*, Base*> bases);
    bool getCorrectFlag() { return correct;};
    GameState *getGameState() { return gameState;};
private:
    std::fstream stateDoc;
    std::string path;
    GameState *gameState;
    bool correct;
};

#endif //LABOOP_MEMENTO_HPP
