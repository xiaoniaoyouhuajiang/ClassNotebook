#pragma once
#include <fstream>
#include <ctime>
#include <string>

class Serializer {
public:
    Serializer(std::string path = "saves/1.sav");
    void serialize();
    ~Serializer();
protected:
    std::ofstream file;
};

class Unserializer {
public:
    Unserializer(std::string path = "saves/newgame.sav");
    void unserialize();
    ~Unserializer();
protected:
    std::ifstream file;
};