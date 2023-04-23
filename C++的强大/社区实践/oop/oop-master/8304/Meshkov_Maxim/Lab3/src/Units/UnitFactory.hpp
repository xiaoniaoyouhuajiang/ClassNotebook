#pragma once

#include <memory>
class Unit;

class UnitFactory {
public:
    virtual std::shared_ptr<Unit> create() const = 0;
};