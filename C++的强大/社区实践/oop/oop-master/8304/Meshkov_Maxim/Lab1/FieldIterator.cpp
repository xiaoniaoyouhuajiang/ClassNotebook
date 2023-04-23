#include "FieldIterator.hpp"

#include "Field.hpp"

FieldIterator::FieldIterator(const Field * field, bool endIterator)
    : m_field(field)
{
    if (endIterator) {
        m_row = field->getHeight();
        m_col = 0;
    }
}

bool FieldIterator::operator!=(const FieldIterator &other) const {
    return !(m_col == other.m_col && m_row == other.m_row);
}

FieldIterator &FieldIterator::operator++() {
    if (m_row >= m_field->getHeight()) {
        return *this;
    }
    if (m_col >= m_field->getWidth() - 1) {
        m_col = 0;
        m_row++;
    }
    else {
        m_col++;
    }
    return *this;
}

std::tuple<std::shared_ptr<Unit>, int, int> FieldIterator::operator*() const {
    return {m_field->getUnit({m_row, m_col}), m_row, m_col};
}
