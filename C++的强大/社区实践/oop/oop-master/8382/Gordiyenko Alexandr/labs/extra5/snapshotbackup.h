#ifndef LABS_SNAPSHOTBACKUP_H
#define LABS_SNAPSHOTBACKUP_H

#include <vector>

class Field;
class RAII;
class FileRead;
class Base;
class Adapter;

class SnapshotBackup
{
private:
    int x, y;
    int maxUnit;
    int curUnit;
    Field *field;
    std::vector<Base*> bases;
    RAII *fileWrie;
    FileRead *fileRead;
    Adapter* adapter;

public:
    SnapshotBackup(Field* field, int x, int y, int maxUnit, int curUnit, std::vector<Base *> bases);
    SnapshotBackup(Field *field);
    ~SnapshotBackup();

    void saveGame();
    void loadGame();
};

#endif //LABS_SNAPSHOTBACKUP_H
