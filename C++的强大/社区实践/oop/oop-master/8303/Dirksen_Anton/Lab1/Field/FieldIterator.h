//
// Created by mensch on 4/3/20.
//

#ifndef OOP_LABS_FIELDITERATOR_H
#define OOP_LABS_FIELDITERATOR_H


#include <iterator>
#include "../Units/Unit.h"
#include "Cell.h"
#include "Field.h"

class FieldIterator : public std::iterator<std::input_iterator_tag, Cell>{
    friend class Field;

private:
    Point coordinates;
    Field* field;

private:
    FieldIterator(const Point& coordinates, Field* field) {
        this->coordinates = coordinates;
        this->field = field;
    }

public:
    FieldIterator(const FieldIterator& it) {
        coordinates = it.coordinates;
        field = it.field;
    }

    bool operator!=( const FieldIterator& other) const {
        return coordinates != other.coordinates;
    }

    bool operator==(const FieldIterator& other) const {
        return coordinates == other.coordinates;
    }


    reference operator*() const {
        return (field->cell)[coordinates.y][coordinates.x];
    }


    FieldIterator& operator++() {
        Point next = coordinates;
        next.x++;

        if (next.x < field->size.x) {
            coordinates = next;
            return *this;
        } else {
            next.x = 0;
            next.y++;

            coordinates = next;
            return *this;
        }
    }


};


#endif //OOP_LABS_FIELDITERATOR_H
