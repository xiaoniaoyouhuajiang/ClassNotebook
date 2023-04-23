#ifndef FIELDSNAPSHOT_H
#define FIELDSNAPSHOT_H

#include <sstream>
#include "base.h"
#include "Landscapes/landscape.h"
#include "NeutralObject/neutralobject.h"
#include "file.h"
#include "filein.h"

class Mediator;
struct Point;

class FieldSnapshot
{
    GameField* field;
    bool isCorrectCreated;
    int x;
    int y;
    int unitCount;
    int maxCount;
    Point*** pointsMap;
    Base* base1;
    Base* base2;

    bool isFileCorrect();

public:
    FieldSnapshot(GameField*, bool, const int x, const int y, int unitCount, const int maxCount, Point*** pointsMap, Base* base1, Base* base2);
    void save();
    void load(Mediator*);
};

#endif // FIELDSNAPSHOT_H
