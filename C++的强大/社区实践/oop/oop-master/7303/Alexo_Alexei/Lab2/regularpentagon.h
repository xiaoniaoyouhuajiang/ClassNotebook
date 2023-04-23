#ifndef REGULARPENTAGON_H
#define REGULARPENTAGON_H

#include <vector>
#include "shape.h"

class RegularPentagon: public Shape{
public:
    RegularPentagon(Color color, Point center, int lenght);
    void Scale(double coefficient) override;
    friend ostream &operator << (ostream &out, const RegularPentagon& regularPentagon);

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
