
#ifndef OOP_SNAPSHOT_H
#define OOP_SNAPSHOT_H

#include "../Logging/File.h"
#include "../../Field/Field.h"
#include "../../Base/Base.h"

/*
 * Snapshot -- класс, реализующий паттерн "Снимок".
 */

class Field;

class Snapshot{

public:
    Snapshot(Field* field, int height, int width, int objectLimit,
                    int objectCounter, int unitLimit, int unitCounter);
    Snapshot(Field* field);
    void saveGame();
    Field* loadGame();
    Field* field;

private:
    int height, width;
    int objectLimit, objectCounter;
    int unitLimit, unitCounter;

    File* file;
    bool isOpen;
};


#endif //OOP_SNAPSHOT_H
