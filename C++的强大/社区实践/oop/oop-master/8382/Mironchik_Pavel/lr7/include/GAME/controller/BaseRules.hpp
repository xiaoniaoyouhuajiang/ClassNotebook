#pragma once

#include <list>
#include <memory>

#include <GAME/controller/Rules.hpp>
#include <GAME/controller/PlayerState.hpp>

using std::shared_ptr;

template<int playersCount>
class BaseRules : public Rules<playersCount> {
private:
	int _currentState = 0;
	std::list<PlayerState> _states;
public:
	BaseRules() {
		for (int i = 0; i < playersCount; i++) {
			_states.push_back(PlayerState(i));
		}
	}

	virtual PlayerState& currentState() override {
		auto it = _states.begin();
		std::advance(it, _currentState);
		return *it;
	}

	virtual void step(GameBoard* board) override {
		if (isOver(board))
			return;

		_currentState = (_currentState + 1) % playersCount;

		while (currentState().isOver(board))
			_currentState = (_currentState + 1) % playersCount;
	}

	virtual bool isOver(GameBoard* board) override {
		int activePlayersCount = 0;

		for (auto& state : _states)
			if (!state.isOver(board))
				activePlayersCount++;

		return activePlayersCount <= 1;
	}
};