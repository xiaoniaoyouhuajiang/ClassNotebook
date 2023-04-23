#include <iostream>
#include <string>
#include <cmath>
#include <vector>

class Shape{
protected:
    double x;
    double y;
    std::string color;
public:
    virtual void rotate(double)=0;
    virtual void scale(double)=0;
    virtual std::ostream& print(std::ostream &, const Shape &) const =0;
    std::string getColor() const;
    void move(double, double);
    void setColor(std::string);
    void setX(double);
    void setY(double);
    void setXY(double,double);
    double getX() const;
    double getY() const;
    friend std::ostream& operator<<(std::ostream&, const Shape&);
    Shape();
};


class Rectangle : public Shape{
private:
    double side_x;
    double side_y;
    double angle;
public:
    void rotate(double);
    void scale(double);
    Rectangle();
    Rectangle(double,double,double);
    std::ostream& print(std::ostream &, const Shape &) const;
    double getSideX() const;
    double getSideY() const;
    double getAngle() const;
};

class Square : public Shape{
private:
    double side;
    double angle;
public:
    void rotate(double);
    void scale(double);
    Square();
    Square(double,double);
    std::ostream& print(std::ostream &, const Shape &) const;
    double getSide() const;
    double getAngle() const;
};

class Ellipse : public Shape{
private:
    double max_rad;
    double min_rad;
    double angle;
public:
    void rotate(double);
    void scale(double);
    Ellipse();
    Ellipse(double,double,double);
    std::ostream& print(std::ostream &, const Shape &) const;
    double getAngle() const;
    double getMaxRad() const;
    double getMinRad() const;
};

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

int main(){
    Rectangle *a = new Rectangle(1,2,0);
    Ellipse *b = new Ellipse(1,2,0);
    Square *c = new Square(1,4);
    a->setColor("Red");
    b->setColor("Blue");
    c->setColor("Black");
    a->rotate(0.5);
    b->rotate(0.5);
    c->rotate(-0.1);
    a->setXY(10,100);
    b->setXY(10,100);
    c->setXY(-14,0.5);
    a->scale(2);
    b->scale(2);
    c->scale(4);
    std::vector<Shape*> v={a,b,c};
    for(int i=0;i<3;i++){
        std::cout<<*v[i]<<std::endl;
    }
    return 0;
}
