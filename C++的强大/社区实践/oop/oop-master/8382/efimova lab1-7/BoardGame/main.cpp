#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <iostream>
#include "Game.h"

int main(int argc, char *argv[])
{
    Game* mGame = Game::getInstance();//возвращаем экземпл€р 
    mGame->Init(argc, argv); // дл€ qt
    mGame->_debug_demo(); //вывод наших примеров в консоль
    //mGame->Start();
}
