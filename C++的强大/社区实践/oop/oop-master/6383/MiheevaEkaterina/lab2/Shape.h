//
// Created by katier on 07.03.18.
//

#ifndef UNTITLED_SHAPE_H
#define UNTITLED_SHAPE_H

#include <cmath>
#include <ostream>

struct Point{
    double x;
    double y;
    Point(double x,double y){
        this->x=x;
        this->y=y;
    }
    friend std::ostream &operator<<(std::ostream &os,  Point &point){
        os<<point.x<<" "<<point.y<<std::endl;
        return os;
    }
};

struct Colour{
    unsigned int red;
    unsigned int green;
    unsigned int blue;
    Colour(unsigned int red, unsigned int green,unsigned int blue){
        this->red=red;
        this->green=green;
        this->blue=blue;
    }
};

//unsigned long long counter=0;


class Shape{
public:
    explicit Shape(Colour colour);
    Colour getColour();
    void setColour(Colour colour);
    unsigned long long int getId();
    virtual void move(Point newCoord) {}
    virtual void rotate(double fi) = 0;
    virtual void scale(double k){}
    virtual void print(std::ostream& os){};

private:
    Colour colour;
    unsigned long long id;
    static unsigned long long counter;
protected:
    friend std::ostream &operator<<(std::ostream &os,  Shape &shape){
        shape.print(os);
        return os;
    }

};

#endif //UNTITLED_SHAPE_H
