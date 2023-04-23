#pragma once
#include "game.hpp"
#include "map.hpp"
#include "exceptions.hpp"

enum class FacadeResultCode {SUCCESS, ERROR};

class Facade {
public:
    Facade(uint32_t width = 10, uint32_t height = 10);
    FacadeResultCode startGame();
    FacadeResultCode mainLoop();
    FacadeResultCode handle(char command, char arg);
    FacadeResultCode updateScreen();
    FacadeResultCode updateState();
    FacadeResultCode handleQ(char arg = 'a');
    FacadeResultCode handleE(char arg = 'a');
    FacadeResultCode handleP(char arg = 'a');
    FacadeResultCode handleL(char arg = 'a');
    FacadeResultCode handleV(char arg = 'a');
    FacadeResultCode handleS(char arg = 'a');
    FacadeResultCode handleC(char arg = 'a');
    FacadeResultCode handleB(char arg = 'a');
    FacadeResultCode handleM(char arg = 'a');
    FacadeResultCode handleA(char arg = 'a');
    FacadeResultCode handleN(char arg = 'a');
    void inc();
    void step();
    void nullifystep();
    void log();
    ~Facade();

private:
    GameController* gc;
    int iter = 0;
    unsigned int steps = 0;
};