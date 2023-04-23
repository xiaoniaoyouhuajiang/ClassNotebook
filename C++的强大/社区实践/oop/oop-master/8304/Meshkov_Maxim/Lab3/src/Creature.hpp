#pragma once

#include <string>
#include <optional>

class Creature {
public:
    virtual std::string getName() const = 0;

    virtual std::optional<int> getPlayer() const = 0;

    virtual int getHealth() const = 0;
    virtual int getMaxHealth() const = 0;
    virtual void modifyHealth(int change) = 0;
};