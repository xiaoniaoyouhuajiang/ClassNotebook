//
// Created by anton on 2/11/20.
//

#ifndef PROJ_FIELD_H
#define PROJ_FIELD_H

#include<string>
#include<assert.h>

//#include "GameObject.h"
class GameObject;

class FieldIterator;

class Field {
    friend class Mediator;

    friend class FieldIterator;
private:
    GameObject ***content;
    int width;
    int height;
    int objCount;
    int objLimit;
public:
    //Field(int width, int height);

    Field(int width, int height, int objLimit);

    Field(const Field &src);

    FieldIterator begin();

    FieldIterator end();

    void getSize(int &width, int &height);

    std::pair<int, int> getSize();

    void resetField();

    GameObject *getAt(int x, int y);

    bool setAt(GameObject &obj, int x, int y);

    GameObject *replaceAt(GameObject &obj, int x, int y);

    GameObject *removeAt(int x, int y);

    bool move(int x1, int y1, int x2, int y2);

    void swap(int x1, int y1, int x2, int y2);//Zerb

    Field &operator=(const Field &src);

    Field &operator=(Field &&other);

    std::string toString();

    std::wstring toWString();

    virtual ~Field();
};

class FieldIterator {
private:
    Field *field;
    int x, y;
public:
    FieldIterator(int x1, int y1, Field *field1) {
        x = x1;
        y = y1;
        field = field1;
    }

    bool operator==(const FieldIterator &other) const {
        return (x == other.x) && (y == other.y);
    }

    bool operator!=(const FieldIterator &other) const {
        return !(this->operator==(other));
    }

    GameObject *operator*() {
        assert(x != field->width && y != field->height);
        return field->content[x][y];
    }

    FieldIterator &operator++() {
        if (x++ >= field->width) {
            x = 0;
            y++;
        }
        return *this;
    }

    FieldIterator &next() {
        if (x++ >= field->width) {
            x = 0;
            y++;
        }
        return *this;
    }

};


#endif //PROJ_FIELD_H
