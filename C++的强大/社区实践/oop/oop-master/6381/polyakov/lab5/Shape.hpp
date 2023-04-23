#include <iostream>
#include <string>
#include <cmath>

class Shape{
protected:
    double x;
    double y;
    std::string color;
public:
    virtual void rotate(double) =0;
    virtual void scale(double) =0;
    virtual bool biggerSquare(double) =0;
    virtual double getSquare() =0;
    virtual std::string getShape() =0;
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
    virtual ~Shape(){};
};


class Rectangle : public Shape{
private:
    double side_x;
    double side_y;
    double angle;
public:
    void rotate(double);
    void scale(double);
    bool biggerSquare(double);
    double getSquare();
    std::string getShape();
    Rectangle();
    Rectangle(double,double,double);
    std::ostream& print(std::ostream &, const Shape &) const;
    double getSideX() const;
    double getSideY() const;
    double getAngle() const;
    ~Rectangle(){};
};

class Square : public Shape{
private:
    double side;
    double angle;
public:
    void rotate(double);
    void scale(double);
    bool biggerSquare(double);
    double getSquare();
    std::string getShape();
    Square();
    Square(double,double);
    std::ostream& print(std::ostream &, const Shape &) const;
    double getSide() const;
    double getAngle() const;
    ~Square(){};
};

class Ellipse : public Shape{
private:
    double max_rad;
    double min_rad;
    double angle;
public:
    void rotate(double);
    void scale(double);
    bool biggerSquare(double);
    double getSquare();
    std::string getShape();
    Ellipse();
    Ellipse(double,double,double);
    std::ostream& print(std::ostream &, const Shape &) const;
    double getAngle() const;
    double getMaxRad() const;
    double getMinRad() const;
    ~Ellipse(){};
};
