#pragma once

#include "../Field/Cell.h"

class SnapshotField {
public:
    SnapshotField(int size, Cell** c, int turn);
    SnapshotField();
    int getSize() const;
    int getWhoseTurn() const;
    Cell** getCell() const;
private:
    int size;
    int whoseTurn;
    Cell** cell;
};
