//
// Created by Alex on 28.04.2020.
//

#include "GameSaver.h"

GameSaver::GameSaver(std::string path) : path(path) {}

void GameSaver::printInSaveFile(const std::string &inf) {
    fin << inf << "\n";
}

GameSaver::~GameSaver() {
    if (fin.is_open()) {
        fin.close();
    }
}

void GameSaver::open() {
    fin.open(path);
}

void GameSaver::close() {
    fin.close();
}
