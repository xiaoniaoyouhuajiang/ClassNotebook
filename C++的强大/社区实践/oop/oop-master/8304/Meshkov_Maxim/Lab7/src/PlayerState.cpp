#include "PlayerState.hpp"

#include "GameInterface.hpp"

int PlayerState::getPlayer() const {
    return m_player;
}

void PlayerState::moveIsMade() {
    int nextPlayer = (m_player + 1) % 2;
    m_game->setPlayerState(std::make_shared<PlayerState>(nextPlayer, m_game));
}
