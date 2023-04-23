#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "SnapshotBase.h"
#include "SnapshotField.h"

using namespace std;

class SnapshotGame {
public:
    SnapshotGame(unsigned size, vector<SnapshotBase*> bases, SnapshotField* field);
    unsigned getSize() const;
    vector<SnapshotBase*> getBases() const;
    SnapshotField* getField() const;

private:
    unsigned size;
    vector<SnapshotBase*> bases;
    SnapshotField* field;
};
