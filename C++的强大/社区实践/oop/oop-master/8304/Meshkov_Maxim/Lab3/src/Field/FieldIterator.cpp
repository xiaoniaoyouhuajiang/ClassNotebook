#include "FieldIterator.hpp"

#include "Field.hpp"

FieldIterator::FieldIterator(const Field * field, bool endIterator)
    : m_field(field)
{
    if (endIterator) {
        m_position.row = field->getHeight();
        m_position.col = 0;
    }
}

bool FieldIterator::operator!=(const FieldIterator &other) const {
    return m_position != other.m_position;
}

FieldIterator &FieldIterator::operator++() {
    if (m_position.row >= m_field->getHeight()) {
        return *this;
    }
    if (m_position.col >= m_field->getWidth() - 1) {
        m_position.col = 0;
        m_position.row++;
    }
    else {
        m_position.col++;
    }
    return *this;
}

std::tuple<std::shared_ptr<const FieldCell>, FieldPosition> FieldIterator::operator*() const {
    return {m_field->getCell(m_position), m_position};
}
