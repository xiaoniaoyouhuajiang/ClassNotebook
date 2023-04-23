//
// Created by Artem Butko on 22.05.2020.
//

#ifndef OOP_NEW_SNAPSHOT_H
#define OOP_NEW_SNAPSHOT_H


#include "../File/File.h"
#include "../../GameField/Field/Field.h"

/*
 * Snapshot -- класс, реализующий паттерн "Снимок". Можно сохранить игру и загрузить сохраненную игру.
 */


class Field;

class Snapshot
{
public:
    Snapshot(Field* field, int height, int width, int objectLimit, int objectCounter, int unitLimit, int unitCounter);
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


#endif //OOP_NEW_SNAPSHOT_H
