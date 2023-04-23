#pragma once

#include <memory>

#include "TwoDimensionalArray.hpp"
#include "Units/Unit.hpp"
#include "FieldPosition.hpp"
#include "FieldIterator.hpp"

class Field {
public:
    Field(int width, int height);
    Field(const Field &other);
    Field(Field &&other) noexcept;
    Field &operator=(const Field &other);
    Field &operator=(Field &&other) noexcept;

    FieldIterator begin() const;
    FieldIterator end() const;

    int getWidth() const;
    int getHeight() const;

    void addUnit(const std::shared_ptr<Unit> &unit, FieldPosition position);
    void removeUnit(FieldPosition position);
    std::shared_ptr<Unit> getUnit(FieldPosition position) const;

private:
    TwoDimensionalArray<std::shared_ptr<Unit>> m_units;
    void copyUnits();
};
