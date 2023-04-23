#ifndef OOP1_SNAPSHOTFIELD_H
#define OOP1_SNAPSHOTFIELD_H

#include "Cell.h"
class Field;
class FileRead;
class File;
class SnapshotField {
public:
    SnapshotField(Field* field, int lengthX, int lengthY, int maxCountObject, int countUnit, Base* base1, Base* base2);


    void save();
    void load(Mediator *mediator);

private:
    int lenghtX, lengthY;
    int maxCountObject;
    int countUnit;
    Cell ***mapCell;
    Base* base1;
    Base* base2;
    Field* field;
    Adapter* adapter;
    FileRead* fileRead;
    FileWrite* file;


};


#endif //OOP1_SNAPSHOTFIELD_H
