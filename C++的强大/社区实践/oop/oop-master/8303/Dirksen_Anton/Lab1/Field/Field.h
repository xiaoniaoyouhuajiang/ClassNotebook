#ifndef OOP_LABS_FIELD_H
#define OOP_LABS_FIELD_H
#include <cstdint>
#include "../Object.h"
#include <iostream>
#include "Cell.h"

class FieldIterator;

class Field {
    friend class FieldIterator;

public:
    explicit Field(int height, int width);
    ~Field();
    bool addObject(int x, int y, Object* object);
    bool addObject(Point &point, Object* object);
    bool deleteObject(int x, int y);
    bool deleteObject(Point& point);
    bool deleteObject(Object* object);
    bool isFreeCell(int x, int y) const;
    Field(Field const& field);
    Field(Field&& field);
    Field& operator=(Field const& field);
    Field& operator=(Field&& field);
    bool moveObject(Object* object, int x, int y);
    Object* getObject(int x, int y) const;
    void print() const;

    FieldIterator begin();
    FieldIterator end();

private:
    Point size;
    int countOfUnits = 0;
    int maxCountOfObjects = 10;

    Cell** cell;
};


#endif //OOP_LABS_FIELD_H