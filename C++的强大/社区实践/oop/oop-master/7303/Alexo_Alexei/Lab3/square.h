#ifndef SQUARE_H
#define SQUARE_H

#include "point.h"
#include "shape.h"
#include <vector>
using namespace std;

class Square:public Shape{
public:
    Square(Color color, Point center, double lenght);
    void Scale(double coefficient) override;
    friend ostream &operator << (ostream &out, const Square& square);

    void Print() {
        Shape::Print();
        std::cout << "Left-Up point`s square:(" << points[0].getX() << "," << points[0].getY() << ")" << endl;
        std::cout << "Lenght`s square:" << lenght << endl;
    }

    /*Square operator *= (double coefficient){
        this->Scale(coefficient);
        cout << "* " << coefficient << endl;
        return *this;
    }*/

    Square operator * (double coefficient){
            this->Scale(coefficient);
            cout << "* " << coefficient << endl;
            return *this;
    }

    Square operator + (double distance) {
        this->Move(distance);
        cout << "+ " << distance << endl;
        return *this;
    }

private:
    double lenght;
};

#endif // SQUARE_H
