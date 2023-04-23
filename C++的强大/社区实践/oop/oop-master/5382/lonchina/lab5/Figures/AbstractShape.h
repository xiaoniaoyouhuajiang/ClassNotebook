#ifndef LONCHINA_SHAPE_H
#define LONCHINA_SHAPE_H

#include <string>

class AbstractShape
{
private:
    std::string color = "";
protected:
    int area = 0;
public:
    // установить цвет фигуры
    void setColor(std::string);

    // получить цвет фигуры
    std::string getColor();

    // чистые виртуальные методы для сдвига, подсчета площади фигуры,
    // поворота, масштабирования и вывода соответственно, ну и деструктор
    virtual void moveTo() = 0;

    virtual void calculateArea() = 0;

    virtual void rotateOn(double) = 0;

    virtual void scaleOn(double) = 0;

    virtual void draw() = 0;

    virtual ~AbstractShape() {}

    int getArea() const;

    bool operator<(const AbstractShape &rhs) const;

    bool operator>(const AbstractShape &rhs) const;

    bool operator<=(const AbstractShape &rhs) const;

    bool operator>=(const AbstractShape &rhs) const;

    bool operator==(const AbstractShape &rhs) const;

    bool operator!=(const AbstractShape &rhs) const;
};

#endif //LONCHINA_SHAPE_H
