#ifndef SHAPE_H
#define SHAPE_H

#include <assert.h>
#include <cstddef>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

#include "point2d.h"

struct Color
{
    unsigned char r, g, b;

    Color(unsigned char _r = 0, unsigned char _g = 0, unsigned char _b = 0) : r(_r), g(_g), b(_b) {}
};

class Shape
{
public:
    Shape();
    virtual ~Shape() {}

    // Возвращает площадь фигуры
    virtual double area() const = 0;
    // Возвращает периметр фигуры
    virtual double perimeter() const = 0;

    // Сдвигает фигуру по x координате на dp.x, по y координате на dp.y
    virtual void translate2d(const Point2d& dp) = 0;
    // Вращает фигуру на угол angle (в радианах)
    virtual void rotate(double angle = 0) = 0;
    // Масштабирует фигуру
    virtual void scale(double scale = 1) = 0;

    // Установить и получить цвет фигуры
    void setColor(const Color color);
    Color getColor() const;

    // Возвращает уникальный id экземпляра фигуры
    size_t getId() const;

    friend std::ostream& operator<< (std::ostream& os, const Shape& p);


protected:
    // Счетчик количества созданных фигур. Служит в качестве уникального идентификатора
    static size_t count;
    // Уникальный id экземпляра фигуры
    size_t m_id;
    // Цвет фигуры
    Color m_color;

    // Вывод id, цвета и координат фигуры в поток
    virtual void print(std::ostream& os) const = 0;
};

#endif // SHAPE_H
