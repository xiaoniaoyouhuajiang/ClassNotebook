#pragma once

class GameInterface;

class PlayerState {
public:
    PlayerState(int player, GameInterface *game) : m_player(player), m_game(game) {}

    int getPlayer() const;

    void moveIsMade();

private:
    int m_player;
    GameInterface *m_game;
};
