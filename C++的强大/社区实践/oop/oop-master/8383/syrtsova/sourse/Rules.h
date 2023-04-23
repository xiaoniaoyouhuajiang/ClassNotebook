#pragma once

/// Класс Интерфейса правил игры

/**
* Класс, содержащий информацию о правилах игры
*/

class Rules {
public:
	int player_count = 0;
	bool last_move = false;
	bool multiplayer = false;
	int start_resourses = 0;
	int number_moves = 0;
	int countermoves = 0;
};

