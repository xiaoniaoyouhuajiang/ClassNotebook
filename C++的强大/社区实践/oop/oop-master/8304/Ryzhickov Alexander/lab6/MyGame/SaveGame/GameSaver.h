//
// Created by Alex on 28.04.2020.
//

#ifndef GAME_GAMESAVER_H
#define GAME_GAMESAVER_H


#include <string>
#include <fstream>

class GameSaver {
private:
    std::string path;
    std::ofstream fin;
public:
    GameSaver(std::string path);
    ~GameSaver();
    void printInSaveFile(const std::string& inf);
    void open();
    void close();
};


#endif //GAME_GAMESAVER_H
