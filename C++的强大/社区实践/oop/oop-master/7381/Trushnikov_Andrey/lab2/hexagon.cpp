#include "hexagon.h"

Hexagon::Hexagon( Colour colour,std::vector <Point> coord, double a, double r): a(a),radius(r){
    this->setColour(colour);
    this->setPoints(coord);
}

double Hexagon::perimetr(){
    return 6*a;
}

double Hexagon::area(){
    return (perimetr()/2) * radius;
}

void Hexagon::scale(double k){
    for(unsigned i = 0; i < coord.size(); i++){
        coord[i].setX(k*coord[i].getX());
        coord[i].setY(k*coord[i].getY());
    }
}

void Hexagon::print(std::ostream& out){
    out << "Hexagon #" << id << ' ';
    out << colour;
    out << "a = " << a;
    out << " P = " << perimetr();
    out << " S = " << area();
    out << " radius = " << radius << std::endl;
    out << "Coordinates: ";
    for(unsigned i = 0; i < coord.size(); i++){
        out << coord[i];
    }
    out << std::endl;

}
