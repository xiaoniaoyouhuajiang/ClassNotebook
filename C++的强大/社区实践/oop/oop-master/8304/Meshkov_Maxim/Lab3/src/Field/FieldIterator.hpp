#pragma once

#include <memory>

#include "FieldCell.hpp"
#include "../FieldPosition.hpp"

class Field;

class FieldIterator {
public:
    FieldIterator(const Field *field, bool endIterator = false);
    FieldIterator(const FieldIterator &) = default;

    bool operator!=(const FieldIterator &other) const;
    FieldIterator &operator++();
    std::tuple<std::shared_ptr<const FieldCell>, FieldPosition> operator*() const;

private:
    FieldPosition m_position;
    const Field* m_field;
};
