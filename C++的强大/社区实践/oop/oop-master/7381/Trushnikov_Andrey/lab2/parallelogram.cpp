#include "parallelogram.h"

Parallelogram::Parallelogram( Colour colour,std::vector <Point> coord, double a, double b, double h): a(a), b(b), h(h) {
    this->setColour(colour);
    this->setPoints(coord);
}

double Parallelogram::perimetr(){
    return 2*(a+b);
}

double Parallelogram::area(){
    return a*h;
}

void Parallelogram::scale(double k){
    for(unsigned i = 0; i < coord.size(); i++){
        coord[i].setX(k*coord[i].getX());
        coord[i].setY(k*coord[i].getY());
    }
}

void Parallelogram::print(std::ostream& out){
    out << "Parallelogram #" << id << ' ';
    out << colour << " ";
    out << " a = " << a << " b = " << b;
    out << " P = " << this->perimetr() << " S = " << this->area();
    out << " Coordinates: ";
    for(unsigned i = 0; i < coord.size(); i++){
        out << coord[i];
    }
    out << std::endl;
}
