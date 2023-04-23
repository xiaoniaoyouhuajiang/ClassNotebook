#pragma once

#include "UnitFactory.hpp"

template <typename T>
class ConcreteUnitFactory : public UnitFactory {
public:
    std::shared_ptr<Unit> create() const override {
        return std::make_shared<T>();
    };
};
