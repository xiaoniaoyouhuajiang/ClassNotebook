//
// Created by smokfyz on 12.04.19.
//

#ifndef XGAME_GAME_H
#define XGAME_GAME_H

#include <vector>
#include "../field/Field.h"
#include "../utility/Coord.h"
#include "../unit/Unit.h"
#include "../unit/OwnUnits.h"
#include "../impediment/Impediment.h"
#include "../player/Player.h"
#include "../gui/GUI.h"

using namespace std;

class Game {
    Game();

    unique_ptr<GUI> gui;
    unique_ptr<Field> field;

    unique_ptr<OwnUnits> own_units;

    vector<shared_ptr<Player>> players;
    unsigned current_turn_player;
    unsigned number_of_moves;

    shared_ptr<Cell> current_cell;

public:
    Game(Game const&)            = delete;
    void operator=(Game const&)  = delete;

    static Game &getGame();

    void run();

    void nextTurn();

    void createUnit(Coord, string, shared_ptr<Player>);
    void createUnit(shared_ptr<Cell>, shared_ptr<Unit>, shared_ptr<Player>);
    void clearUnits();
    void moveUnit(shared_ptr<Cell>, shared_ptr<Cell>, unsigned);
    void attackUnit(shared_ptr<Cell>, shared_ptr<Cell>);
    void resetUnits();

    void createImp(Coord, string);
    void deleteImp(Coord);
    vector<shared_ptr<Impediment>> &getImps();
    void updateImps();

    void createField(unsigned);
    Field &getField();

    vector<shared_ptr<Player>> &getPlayers();
    shared_ptr<Player> getCurrentPlayer();
    void addPlayer(shared_ptr<Player> &);
    void clearPlayers();

    void pickCell(Coord);
    bool hasPickCell();
    void clearPickCell();
    shared_ptr<Cell> getCell(Coord);
    shared_ptr<Cell> getCurrentCell();

    unsigned getNumOfMoves();
    void resetNumOfMoves();

    OwnUnits &getOwnUnits();

};


#endif //XGAME_GAME_H
