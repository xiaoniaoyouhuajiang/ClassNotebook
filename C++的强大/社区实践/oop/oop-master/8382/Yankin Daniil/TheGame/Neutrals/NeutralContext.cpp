#include "NeutralContext.h"
#include "Player/NeutralPlayer.h"
#include <Game/Game.h>


NeutralContext::NeutralContext(Point point, NeutralPlayer* player) : point(point), player(player), strategy(nullptr) {
    player->addNeutralObject(this);

    std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY()};
    Game::getInstance().getLogAdapter().log(LOG_NEUTRAL_CREATED, logParameters);
}

NeutralContext::NeutralContext(NeutralSnapshot& snapshot, NeutralPlayer* player) : point(snapshot.point), player(player), strategy(nullptr) {
    player->addNeutralObject(this);

    std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY()};
    Game::getInstance().getLogAdapter().log(LOG_NEUTRAL_CREATED, logParameters);
}

NeutralContext::~NeutralContext() {
    delete strategy;
    player->removeNeutralObject(this);

    std::vector<int> logParameters = {getObjectType(), point.getX(), point.getY()};
    Game::getInstance().getLogAdapter().log(LOG_NEUTRAL_DESTRUCTED, logParameters);
}


uint16_t NeutralContext::getGroupType() {
    return NEUT_OBJECT;
}

uint16_t NeutralContext::getObjectType() {
    return NEUT_OBJECT;
}

Point NeutralContext::getPoint() {
    return point;
}


void NeutralContext::setStrategy(NeutralObject* strategy) {
    delete this->strategy;
    this->strategy = strategy;
}

bool NeutralContext::operator>>(IUnit& unit) {
    if (strategy != nullptr)
        return (*strategy >> unit);
    return true;
}
