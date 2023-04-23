#ifndef COOR_H
#define COOR_H
#include <iostream>

class Coor
{
public:
    Coor();
    Coor(const Coor&);
    Coor(double x, double y);
    void setCoor(double x, double y);
    void setCoor(Coor);
    double x();
    double y();
    void x(double x);
    void y(double y);
    Coor& operator=(const Coor& right)
    {
        this->_x = right._x;
        this->_y = right._y;
        return *this;
    }
    friend std::ostream& operator<< (std::ostream &out, Coor&);
    std::ostream& print(std::ostream&);
private:
    double _x;
    double _y;
};

#endif // COOR_H
