//
// Created by Alex on 14.04.2020.
//

#ifndef GAME_LOGGER_H
#define GAME_LOGGER_H


#include "../ProxyLogger/ProxyLogger.h"

class Logger {
private:
    ProxyLogger proxyLogger;
public:
    void enableTerminalWriteMode();
    void enableFileWriteLogMode();
    void enableWrite();
    void disableWrite();
    void switchWriteMode();
    void logAddSwordsmen(int x, int y);
    void logAddSpearmen(int x, int y);
    void logAddArcher(int x, int y);
    void logAddMagician(int x, int y);
    void logAddKing(int x, int y);
    void logAddKnight(int x, int y);
    void logUpdatePosition(int lastX, int lastY, int newX, int newY);
    void logUnitDie(int x,int y);
    void logAttackUnit(int lastX, int lastY, int newX, int newY);

    void logStartLoad();
    void logEndLoad();
    void logLoadCorrect();
    void logLoadNotCorrect();
    void logLoadUnit(int x, int y, std::string type, int health, int maxHealth, int armor, int maxArmor, int damage,
                     int attackBonus);
};


#endif //GAME_LOGGER_H
