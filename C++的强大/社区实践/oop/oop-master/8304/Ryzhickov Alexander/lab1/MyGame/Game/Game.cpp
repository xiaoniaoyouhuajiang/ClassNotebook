//
// Created by Alex on 03.03.2020.
//


#include "Game.h"

Game::Game() {
    Game::field = new Field(10,10,20);
    Game::units = new Unit*[field->getMaxCountUnits()];
    Game::base = new Base(units,0,0,20);
    field->setBase(0,0,base);
}

Game::~Game() {
    //units = new Unit*[field->getMaxCountUnits()];
    int b = base->getCountUnitsInGame();
    for (int i = 0; i < b; ++i) {

        //bool is = true;

        /*for (int num : base->vectorDeleteUnits) {
            if (i==num){
                is = false;
                break;
            }
        }*/

      //if(is) {
          delete (units[i]);
      //}

    }
    delete (units);
    delete (field);
    delete(base);
}
