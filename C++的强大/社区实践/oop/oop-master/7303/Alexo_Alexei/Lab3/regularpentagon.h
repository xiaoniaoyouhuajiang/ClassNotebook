#ifndef REGULARPENTAGON_H
#define REGULARPENTAGON_H

#include <vector>
#include "shape.h"

class RegularPentagon: public Shape{
public:
    RegularPentagon(Color color, Point center, int lenght);
    void Scale(double coefficient) override;
    friend ostream &operator << (ostream &out, const RegularPentagon& regularPentagon);

    void Print() {
        Shape::Print();
        std::cout << "point`s RegularPentagon:" << endl;
        for(int i = 0; i < points.size(); i++)
            std::cout << "   (" << points[i].getX() << "," << points[i].getY() << ")" << endl;
        std::cout << "Length`s RegularPentagon:" << lenght << endl;
    }

    RegularPentagon operator * (double coefficient){
        this->Scale(coefficient);
        cout << "* " << coefficient << endl;
        return *this;
    }

    RegularPentagon operator + (double distance){
         this->Move(distance);
         cout << "+ " << distance << endl;
         return *this;
    }

private:
    int lenght;
};

#endif // REGULARPENTAGON_H
