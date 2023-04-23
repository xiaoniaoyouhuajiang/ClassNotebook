#pragma once

#include <cstdint>
#include <list>
#include <algorithm>
#include <fstream>


class PlayerContext;
class IPlayerState;
template <uint16_t id> class PlayerState;


class PlayerContext
{
    template <uint16_t id> friend class PlayerState;

public:
    class PlayerContextSnapshot;

public:
    PlayerContext(std::list<uint16_t>& playerList, uint16_t playerId);
    ~PlayerContext();
    void nextPlayerId();
    std::list<uint16_t> getOrder() const;
    uint16_t getPlayerId() const;
    void removePlayerId(uint16_t playerId);

private:
    void setState(uint16_t playerId);

private:
    std::list<uint16_t> playerList;
    IPlayerState* state;
};



class IPlayerState
{
public:
    IPlayerState() = default;
    virtual ~IPlayerState() = default;
    virtual void nextPlayerId(PlayerContext* context) = 0;
    virtual uint16_t getPlayerId() const = 0;
};



template <const uint16_t id>
class PlayerState : public IPlayerState
{
public:
    PlayerState() = default;
    ~PlayerState() = default;

    void nextPlayerId(PlayerContext* context) override {
        auto iter = std::find(context->playerList.begin(), context->playerList.end(), id);
        iter++;
        if (iter != context->playerList.end()) {
            context->setState(*iter);
        }
        else {
            iter = context->playerList.begin();
            context->setState(*iter);
        }
    }

    uint16_t getPlayerId() const {
        return id;
    }
};
