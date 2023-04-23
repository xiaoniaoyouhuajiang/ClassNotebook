
#ifndef OOP_RANGE_H
#define OOP_RANGE_H

/*
 * Range -- класс очков перемещения объекта.
 * Показывает, на какое расстояние может перемещаться объект
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


#endif //OOP_RANGE_H
