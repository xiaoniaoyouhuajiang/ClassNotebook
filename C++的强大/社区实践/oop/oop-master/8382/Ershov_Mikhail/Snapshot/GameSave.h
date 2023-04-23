#pragma once

#include "SnapshotGame.h"
#include "../Base/Base.h"
//#include "Landscape.h"
//#include "NeutralObject.h"
#include <fstream>

class GameSave {
public:
    GameSave(string name);
    ~GameSave();
    void save(SnapshotGame* snapshot);
private:
    ofstream file;
    string fileName;
};
