#pragma once
#include <iostream>
#include <string>

class Vector2D;

#define EXIT_COMMAND 'p'

#define NEXT_BASE_COMMAND 't'
#define PREV_BASE_COMMAND 'r'
#define SPAWN_COLLECTOR '1'
#define SPAWN_SPRINKLER '2'
#define SPAWN_UNIT01 '3'
#define SPAWN_UNIT02 '4'
#define SPAWN_UNIT03 '5'

#define NEXT_UNIT_COMMAND 'e'
#define PREV_UNIT_COMMAND 'q'
#define MOVE_UP_COMMAND 'w'
#define MOVE_DAWN_COMMAND 's'
#define MOVE_LEFT_COMMAND 'a'
#define MOVE_RIGTH_COMMAND 'd'
#define ATTACK_COMMAND 'z'
#define SACRAFICE_COMMAND 'x'

#define SAVE_COMMAND 'k'
#define LOAD_COMMAND 'l'
#define NEW_GAME 'n'

class PlayerInput {
public:
	PlayerInput();
	~PlayerInput();

	Vector2D readMapDimensions();
	std::string readString(std::string messege);
	void readInput(char &messageCommand);
};

