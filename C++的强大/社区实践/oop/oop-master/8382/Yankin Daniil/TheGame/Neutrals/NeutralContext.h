#pragma once

#include <fstream>
#include "Trivia/Snapshot.h"
#include "Object/Object.h"
#include "NeutralObject.h"

class NeutralPlayer;


class NeutralContext : public Object
{
public:
    class NeutralSnapshot;

    NeutralContext(Point point, NeutralPlayer* player);
    NeutralContext(NeutralSnapshot& snapshot, NeutralPlayer* player);
    ~NeutralContext();

    uint16_t getGroupType() override;
    uint16_t getObjectType() override;
    Point getPoint() override;

    void setStrategy(NeutralObject* strategy);
    bool operator>>(IUnit& unit);

private:
    Point point;
    NeutralPlayer* player;
    NeutralObject* strategy;
};


class NeutralContext::NeutralSnapshot : public Snapshot {
    friend class NeutralContext;

public:
    NeutralSnapshot(NeutralContext& neutral);
    NeutralSnapshot(std::ifstream& stream);
    friend std::ofstream& operator<<(std::ofstream& stream, const NeutralContext::NeutralSnapshot& fieldSnapshot);

private:
    Point point;
};
