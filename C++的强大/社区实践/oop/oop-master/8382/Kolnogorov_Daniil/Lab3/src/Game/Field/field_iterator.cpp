#include "field_iterator.hpp"
#include "field.hpp"

FieldIterator::FieldIterator(Field* field) {
    this->field = field;
    this->current = {0, 0};
}

bool FieldIterator::has_more() {
    return current.y < (int)field->get_height();
}

FieldIterator& FieldIterator::operator++() {
    if (current.x + 1 == (int)field->get_width()) {
        current.x = 0;
        current.y++;
    } else {
        current.x++;
    }
    return *this;
}

TileInterface* FieldIterator::operator*() {
    return field->tile_at(current);
}
