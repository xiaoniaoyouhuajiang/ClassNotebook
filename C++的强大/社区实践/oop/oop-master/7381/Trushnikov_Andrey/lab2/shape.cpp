#include "shape.h"
unsigned long long Shape::counter = 1;

void Shape::setColour(Colour colour){
    this->colour = colour;
}

Colour::Colour(int r = 0, int g = 0, int b = 0):r(r),g(g),b(b){

}

void Shape::setPoints(std::vector <Point> coord){
    this->coord = coord;
}
Point::Point(double x = 0.0, double y = 0.0):x(x),y(y){}

void Shape::rotate(double fi){
    Point relative;
    for (unsigned int i = 0; i < this->coord.size(); ++i) {
        relative = coord[i];
        coord[i].rotate_p(fi,relative);
    }
}

void Shape::move(Point coord){
    for (unsigned int i = 0; i < this->coord.size(); ++i) {
        this->coord[i].setX(this->coord[i].getX() + coord.getX());
        this->coord[i].setY(this->coord[i].getY() + coord.getY());
    }
}

void Point::rotate_p(double fi, Point relative){
    x = relative.getX()*cos(fi) - relative.getY()*sin(fi);
    y = relative.getX() * sin(fi) + relative.getY() * cos(fi);
}

void Point::setX(double x){
    this->x = x;
}

void Point::setY(double y){
    this->y = y;
}

double Point::getX(){
    return x;
}

double Point::getY(){
    return y;
}

std::ostream& operator<<(std::ostream& out,  Point point){
    out << "(" << point.x << "," << point.y << ")";
    return out;
}

void Colour::setRed(int r){
    this->r = r;
}

void Colour::setGreen(int g){
    this->g = g;
}

void Colour::setBlue(int b){
    this->b = b;
}

int Colour::getRed(){
    return r;
}

int Colour::getGreen(){
    return g;
}

int Colour::getBlue(){
    return b;
}

std::ostream& operator<<(std::ostream& out, Colour colour){
    out << "Colour " << "r: " << colour.r << " g: " << colour.g << " b: " << colour.b << " ";
    return out;
}
