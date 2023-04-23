#pragma once

#include <GAME/controller/Rules2.hpp>
#include <GAME/controller/Rules3.hpp>
#include <GAME/controller/GameController.hpp>

template<typename R, int PlayersCount>
class GameControllerImp1 : public GameController {};

template<typename R>
class GameControllerImp1<R, 2> : public GameController {
private:
	static GameControllerImp1* _instance;
	R _rules;
	GameBoard* _board = nullptr;

public:
	static GameControllerImp1* instance() {
		if (_instance == nullptr)
			_instance = new GameControllerImp1();

		return _instance;
	}

	GameBoard* board() override{
		return _board;
	}

	void newGame() override {
		if (_board != nullptr)
			delete _board;

		_board = _rules.makeBoard();
	}

	PlayerState& currentState() override {
		return _rules.currentState();
	}

	void step() override {
		_rules.step(board());
	}

	bool isOver() override {
		return _rules.isOver(board());
	}
};

template<typename R>
class GameControllerImp1<R, 3> : public GameController {
private:
	static GameControllerImp1* _instance;
	R _rules;
	GameBoard* _board = nullptr;

public:
	static GameControllerImp1* instance() {
		if (_instance == nullptr)
			_instance = new GameControllerImp1();

		return _instance;
	}

	GameBoard* board() override{
		return _board;
	}

	void newGame() override {
		if (_board != nullptr)
			delete _board;

		_board = _rules.makeBoard();
	}

	PlayerState& currentState() override {
		return _rules.currentState();
	}

	void step() override {
		_rules.step(board());
	}

	bool isOver() override {
		return _rules.isOver(board());
	}
};

template<typename R>
GameControllerImp1<R, 2>* GameControllerImp1<R, 2>::_instance = nullptr;

template<typename R>
GameControllerImp1<R, 3>* GameControllerImp1<R, 3>::_instance = nullptr;

typedef GameControllerImp1<Rules2, 2> GameControllerImp1_2;
typedef GameControllerImp1<Rules3, 3> GameControllerImp1_3;