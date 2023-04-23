#ifndef OOP_LABS_OBJECT_H
#define OOP_LABS_OBJECT_H

#include "Point.h"

enum ObjectType{
    UNIT,
    NEUTRAL,
    OBJECT
};

enum Texture{
    ARCHMAGE = 'A',
    DRUID = 'D',
    BOWMAN = 'B',
    CROSSBOWMAN = 'C',
    KNIGHT = 'K',
    SQUIRE = 'S',
};


class Object {

protected:
    Point coords;
    int side;

public:
    virtual ~Object() = default;
    Point getCoords() const;
    virtual ObjectType type() const;
    virtual void move(Point point) = 0;
    virtual Texture texture() const = 0;
};


#endif //OOP_LABS_OBJECT_H
