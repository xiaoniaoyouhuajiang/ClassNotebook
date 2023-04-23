//
// Created by Mila
//

#include "Game.h"

Game::Game() {
    counter = 0;
    field = new Field(12, 12, 5);
    units = new Unit*[field->getControlMax()];//выделяем место для массива
    base = new Base(field, units, counter++, field->getControlMax());


}

Game::~Game() {
    for (int i = 0; i < base->getCountUnit(); i++) {

        if(dynamic_cast<Archer *>(units[i]) != nullptr) {
            auto *archer = dynamic_cast<Archer *>(units[i]);
            delete archer;
        }
        else if(dynamic_cast<Magician *>(units[i]) != nullptr) {
            auto *magician = dynamic_cast<Magician *>(units[i]);
            delete magician;
        }
        else if(dynamic_cast<ElfOnUnicorn *>(units[i]) != nullptr) {
            auto *elfOnUnicorn = dynamic_cast<ElfOnUnicorn *>(units[i]);
            delete elfOnUnicorn;
        }
        else if(dynamic_cast<KnightOnHorse *>(units[i]) != nullptr) {
            auto *knightOnHorse = dynamic_cast<KnightOnHorse *>(units[i]);
            delete knightOnHorse;
        }
        else if(dynamic_cast<Gnome *>(units[i]) != nullptr) {
            auto *gnome = dynamic_cast<Gnome *>(units[i]);
            delete gnome;
        }
        else if(dynamic_cast<Knight *>(units[i]) != nullptr) {
            auto *knight = dynamic_cast<Knight *>(units[i]);
            delete knight;
        }
        //delete(units[i]);

    }
    delete(units);

}
