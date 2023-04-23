#pragma once

#include <cstdint>
#include <set>
#include "Game/Game.h"

class NeutralContext;


class NeutralPlayer
{
    friend class GameFacade;
    friend class Game::Saver;
    friend class SpeedRule;

public:
    ~NeutralPlayer();

    void addNeutralObject(NeutralContext* neutralObject);
    void removeNeutralObject(NeutralContext* neutralObject);

private:
    std::set <NeutralContext*>* getNeutralObjectSet();

private:
    std::set <NeutralContext*> neutralSet;
};
