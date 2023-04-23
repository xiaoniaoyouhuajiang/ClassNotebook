#ifndef OOP_BASE_H
#define OOP_BASE_H

#include <algorithm>
#include <iostream>
#include <vector>
#include "Object.h"
#include "Field.h"
#include "Cell.h"

class Base: public Object{
public:

    Base();

    ~Base() final = default;

    bool create_unit(Field* f, Object* unit, int x, int y);

    void subscribe(Object* obj);

    void unsubscribe(Object* obj);

    void setMaxQuantity(int n);

    int getMaxQuantity();

    Base* clone();


private:

    int maxQuantity = 10;
    int currentQuantity = 0;
    std::vector<Object*> warriors;
};


#endif //OOP_BASE_H
