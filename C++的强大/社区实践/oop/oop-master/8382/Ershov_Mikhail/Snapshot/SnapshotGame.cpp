#include "SnapshotGame.h"

SnapshotGame::SnapshotGame(unsigned size, vector<SnapshotBase*> bases, SnapshotField* field) : size(size), bases(bases), field(field) {

}

unsigned SnapshotGame::getSize() const {
    return size;
}

vector<SnapshotBase*> SnapshotGame::getBases() const {
    return bases;
}

SnapshotField* SnapshotGame::getField() const {
    return field;
}
