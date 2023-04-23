#pragma once

#include "SnapshotGame.h"
#include "../Field/Landscape/Landscape.h"
#include "../Field/NeutralObject/NeutralObject.h"
#include <fstream>

class GameLoad {
public:
    GameLoad(string name);
    ~GameLoad();
    SnapshotGame* load();
private:
    ifstream file;
    string fileName;
};