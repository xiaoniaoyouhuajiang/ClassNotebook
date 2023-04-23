// OOP_lr_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <utility>
#include <list>
#include "GameBoard.h"
#include "Shooters.h"
#include "IUnit.h"
#include "Game.h"
#include "Landscapes.h"
#include "NeutralObjects.h"

using namespace std;



int main()
{
	Game* game = new Game();
	game->startGame();
}

