#include "Shape.hpp"

std::ostream& operator<<(std::ostream &st, const Shape& s){
    return s.print(st,s);
}

double Ellipse::getAngle() const{
    return angle;
}

double Ellipse::getMaxRad() const{
    return max_rad;
}

double Ellipse::getMinRad() const{
    return min_rad;
}

double Square::getSide() const{
    return side;
}

double Square::getAngle() const{
    return angle;
}

double Rectangle::getSideX() const{
    return side_x;
}

double Rectangle::getSideY() const{
    return side_y;
}

double Rectangle::getAngle() const{
    return angle;
}

void Shape::setX(double new_x){
    x=new_x;
}

void Shape::setY(double new_y){
    y=new_y;
}

void Shape::setXY(double new_x, double new_y){
    x=new_x;
    y=new_y;
}

double Shape::getX() const{
    return x;
}

double Shape::getY() const{
    return y;
}

std::ostream& Rectangle::print(std::ostream &st, const Shape &r) const{
    st<<"Shape: rectangle\n";
    st<<"Coordinates: ("<<getX()<<";"<<getY()<<")\n";
    st<<"Color: "<<getColor()<<std::endl;
    st<<"Side lenths: "<<getSideX()<<", "<<getSideY()<<std::endl;
    st<<"Angle: "<<getAngle()<<" rad\n";
    return st;
}


std::ostream& Square::print(std::ostream &st, const Shape &s) const{
    st<<"Shape: sqare\n";
    st<<"Coordinates: ("<<getX()<<";"<<getY()<<")\n";
    st<<"Color: "<<getColor()<<std::endl;
    st<<"Side lenth: "<<getSide()<<std::endl;
    st<<"Angle: "<<getAngle()<<" rad\n";
    return st;
}

std::ostream& Ellipse::print(std::ostream &st, const Shape &e) const{
    st<<"Shape: ellipse\n";
    st<<"Coordinates: ("<<getX()<<";"<<getY()<<")\n";
    st<<"Color: "<<getColor()<<std::endl;
    st<<"Major radius: "<<getMaxRad()<<std::endl;
    st<<"Minor radius: "<<getMinRad()<<std::endl;
    st<<"Angle: "<<getAngle()<<" rad\n";
    return st;
}

void Square::scale(double n){
    side *= n;
}

void Square::rotate(double alf){
    angle += alf;
    while(angle >= M_PI/2){
        angle -= M_PI/2;
    }
    while(angle < 0){
        angle += M_PI/2;
    }
}

Square::Square(double a, double b){
    side=a;
    angle=b;
}

Square::Square(){
    side=0;
    angle=0;
}

void Ellipse::scale(double n){
    max_rad *= n;
    min_rad *= n;
}

void Ellipse::rotate(double alf){
    angle += alf;
    while(angle > M_PI){
        angle -= M_PI;
    }
    while(angle <= 0){
        angle += M_PI;
    }
}

Ellipse::Ellipse(){
    max_rad=0;
    max_rad=0;
    angle=0;
}

Ellipse::Ellipse(double a, double b, double c){
    max_rad= a > b ? a : b;
    min_rad= a > b ? b : a;
    angle=c;
}

void Shape::setColor(std::string new_color){
    color = new_color;
}

std::string Shape::getColor() const{
    return color;
}

void Shape::move(double to_x, double to_y){
    x = to_x;
    y = to_y;
}

void Rectangle::scale(double n){
    side_x *= n;
    side_y *= n;
}

void Rectangle::rotate(double alf){
    angle += alf;
    while(angle > M_PI){
        angle -= M_PI;
    }
    while(angle <= 0){
        angle += M_PI;
    }
}

Rectangle::Rectangle(){
    side_x=0;
    side_y=0;
    angle=0;
}

Rectangle::Rectangle(double a, double b, double c){
    side_x=a;
    side_y=b;
    angle=c;
}



Shape::Shape(){
    x=0;
    y=0;
    color="none";
}

bool Square::biggerSquare(double a){
    return a < getSquare();
};

bool Rectangle::biggerSquare(double a){
    return a < getSquare();
};

bool Ellipse::biggerSquare(double a){
    return a < getSquare();
};

double Square::getSquare(){
    return side * side;
}

double Rectangle::getSquare(){
    return side_x * side_y;
}

double Ellipse::getSquare(){
    return max_rad * min_rad * M_PI;
}

std::string Square::getShape(){
    return std::string("square   ");
}

std::string Rectangle::getShape(){
    return std::string("rectangle");
}

std::string Ellipse::getShape(){
    return std::string("ellipse   ");
}
