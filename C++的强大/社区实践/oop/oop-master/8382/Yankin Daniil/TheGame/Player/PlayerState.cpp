#include "PlayerState.h"
#include "Player.h"
#include <stdexcept>

#include <array>

PlayerContext::PlayerContext(std::list<uint16_t>& playerList, uint16_t playerId) : playerList(playerList), state(nullptr) {
    for (auto playerListId : playerList) {
        if (playerListId != PLAYER_BLUE && playerListId != PLAYER_RED && playerListId != PLAYER_GREEN && playerListId != PLAYER_ORANGE) {
            throw std::runtime_error("Incorrent playerList in PlayerContext constructor");
        }
    }
    if (playerId != PLAYER_BLUE && playerId != PLAYER_RED && playerId != PLAYER_GREEN && playerId != PLAYER_ORANGE) {
        throw std::runtime_error("Incorrent playerId in PlayerContext()");
    }

    switch(playerId) {
    case PLAYER_BLUE:
        state = new PlayerState<PLAYER_BLUE>();
        break;
    case PLAYER_RED:
        state = new PlayerState<PLAYER_RED>();
        break;
    case PLAYER_GREEN:
        state = new PlayerState<PLAYER_GREEN>();
        break;
    case PLAYER_ORANGE:
        state = new PlayerState<PLAYER_ORANGE>();
        break;
    }
}

PlayerContext::~PlayerContext() {
    delete state;
}

void PlayerContext::setState(uint16_t playerId) {
    if (playerId != PLAYER_BLUE && playerId != PLAYER_RED && playerId != PLAYER_GREEN && playerId != PLAYER_ORANGE) {
        throw std::runtime_error("Incorrent playerId in setState()");
    }

    delete this->state;
    switch(playerId) {
    case PLAYER_BLUE:
        state = new PlayerState<PLAYER_BLUE>();
        break;
    case PLAYER_RED:
        state = new PlayerState<PLAYER_RED>();
        break;
    case PLAYER_GREEN:
        state = new PlayerState<PLAYER_GREEN>();
        break;
    case PLAYER_ORANGE:
        state = new PlayerState<PLAYER_ORANGE>();
        break;
    }
}

void PlayerContext::nextPlayerId() {
    state->nextPlayerId(this);
}

std::list<uint16_t> PlayerContext::getOrder() const {
    return playerList;
}

uint16_t PlayerContext::getPlayerId() const {
    return state->getPlayerId();
}

void PlayerContext::removePlayerId(uint16_t playerId) {
    playerList.remove(playerId);
}
