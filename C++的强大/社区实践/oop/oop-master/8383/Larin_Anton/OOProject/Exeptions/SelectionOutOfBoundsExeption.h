//
// Created by anton on 6/2/20.
//

#ifndef OOPROJECT_SELECTIONOUTOFBOUNDSEXEPTION_H
#define OOPROJECT_SELECTIONOUTOFBOUNDSEXEPTION_H


#include <utility>
#include <ostream>

class SelectionOutOfBoundsExeption {
public:

    SelectionOutOfBoundsExeption(const std::pair<int, int> &selection, const std::pair<int, int> &bounds) : selection(
            selection), bounds(bounds) {}

    friend std::ostream &operator<<(std::ostream &os, const SelectionOutOfBoundsExeption &exeption) {
        os << "Selection out of bounds: selection: " << exeption.selection.first<<":"<<exeption.selection.second << " bounds: 0-" << exeption.bounds.first-1<<":0-"<<exeption.bounds.second-1;
        return os;
    }

private:
    std::pair<int,int> selection;
    std::pair<int,int> bounds;
};


#endif //OOPROJECT_SELECTIONOUTOFBOUNDSEXEPTION_H
