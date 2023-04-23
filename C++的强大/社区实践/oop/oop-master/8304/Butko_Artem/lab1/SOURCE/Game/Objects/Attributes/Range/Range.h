//
// Created by Artem Butko on 08/05/2020.
//

#ifndef OOP_NEW_RANGE_H
#define OOP_NEW_RANGE_H

/*
 * Range -- класс очков перемещения объекта.
 * -----------------------------------------
 * range_ -- текущие очки перемещения.
 */

class Range
{
public:
    void set(int range);
    int get();

private:
    int range_;
};


#endif //OOP_NEW_RANGE_H
