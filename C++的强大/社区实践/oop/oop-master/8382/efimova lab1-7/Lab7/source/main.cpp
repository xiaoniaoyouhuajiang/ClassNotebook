#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <iostream>
#include "Game.h"

int main(int argc, char *argv[])
{
    Game* mGame = Game::getInstance();
    mGame->initGUI(argc, argv);
    return mGame->Start();
}
