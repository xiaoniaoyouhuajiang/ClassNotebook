#pragma once

#include <memory>

#include "Units/Unit.hpp"

class Field;

class FieldIterator {
public:
    explicit FieldIterator(const Field *field, bool endIterator = false);
    FieldIterator(const FieldIterator &) = default;

    bool operator!=(const FieldIterator &other) const;
    FieldIterator &operator++();
    std::tuple<std::shared_ptr<Unit>, int /*row*/, int /*col*/> operator*() const;

private:
    int m_row = 0;
    int m_col = 0;
    const Field* m_field;
};
