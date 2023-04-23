//
// Created by max on 04.03.20.
//

#ifndef OOP_OBJECT_H
#define OOP_OBJECT_H

class Object {
    int x_coord = -1;
    int y_coord = -1;
    int object_id;
public:
    Object(int x,int y,int id) :  x_coord(x), y_coord(y), object_id(id) {};
    int getXCoord();
    int getYCoord();
    int getObjectId();
};


#endif //OOP_OBJECT_H
