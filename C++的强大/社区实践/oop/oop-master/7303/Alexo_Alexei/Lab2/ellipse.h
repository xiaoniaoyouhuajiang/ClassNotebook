#ifndef ELIPSE_H
#define ELIPSE_H

#include <vector>
#include "shape.h"

class Ellipse: public Shape{
public:
    Ellipse(Color color, Point center, double smallRadius, double bigRadius);
    void Scale(double coefficient) override;
    friend ostream &operator << (ostream &out, const Ellipse& ellipse);

    Ellipse operator * (double coefficient){
        this->Scale(coefficient);
        cout << "* " << coefficient << endl;
        return *this;
    }

    Ellipse operator + (double distance){
         this->Move(distance);
         cout << "+ " << distance << endl;
         return *this;
    }


private:
    double smallRadius;
    double bigRadius;
};

#endif // ELIPSE_H
