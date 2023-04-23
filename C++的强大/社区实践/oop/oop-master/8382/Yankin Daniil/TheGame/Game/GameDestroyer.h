#pragma once

class Game;


class GameDestroyer {
public:
    ~GameDestroyer();
    void init(Game* game);

private:
    Game* game;
};
