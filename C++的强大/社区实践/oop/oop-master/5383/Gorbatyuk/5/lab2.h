#ifndef LAB2_H
#define LAB2_H

#include <cmath>
#include <string>
#include <iostream>

// для 5 лабораторной
#include <limits>
#include <random>
#include <functional>
#include <chrono>

using namespace std;

// для 5 лабораторной
const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
static const int magicborder = 1 << 8;

struct CS
{
    double x;
    double y;
};

struct Color
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
    Color(int _r = 0, int _g = 0, int _b = 0) {
        r = _r;
        g = _g;
        b = _b;
    }
};

class Shape
{
protected:
    static int counter;
    int id;
    CS center;
    Color currentColor;
    double AB;
    double BC;
    double AC;
private:

public:
    Shape(Color _color);
    virtual ostream &put(ostream& out) const = 0;
    virtual void Move(double _x, double _y) = 0;
    virtual void Rotate(double _angle) = 0;
    virtual void Scale(double _scale) = 0;
    //virtual void SetColor(string _color);
    //virtual Color GetColor();
    virtual bool IsInsideOfAnother(const Shape& other);

    // создает случайную фигуру
    static Shape* createRandomShape();
};

class Quadrate :
    public Shape
{
    friend class IsoscelesTriangle;
    friend class RightTriangle;
private:
    CS points[4];
    double sides[4];
    double diagonals[2];
    double angles[4];
    void IsItQuadrate(double _ax, double _ay, double _bx, double _by, double _cx, double _cy, double _dx, double _dy);
    void NewQuadrateCenter();
    void NewSizes();
    double Angle(CS p1, CS p2, CS p3);
public:
    Quadrate(double _ax, double _ay, double _bx, double _by, double _cx, double _cy, double _dx, double _dy, Color _color);
    void Move(double _x, double _y);
    void Rotate(double _angle);
    void Scale(double _scale);
    //void SetColor(string _color);
    //string GetColor();
    ostream &put(ostream &out) const;
    bool IsInsideOfAnother(const Shape &other);
    ~Quadrate();

    // создает случайную фигуру
    static Quadrate* createRandomShape();
};

class IsoscelesTriangle ://равнобедренный
    public Shape
{
    friend class RightTriangle;
    friend class Quadrate;
private:
    CS points[3];
    void IsItIsoscelesTriangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy);
    void IsItTriangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy);
public:
    IsoscelesTriangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy, Color _color);
    ~IsoscelesTriangle();
    void Move(double _x, double _y);
    void Rotate(double _angle);
    void Scale(double _scale);
    bool IsInsideOfAnother(const Shape &other);
    ostream &put(ostream &out) const;

    // создает случайную фигуру
    static IsoscelesTriangle* createRandomShape();
};

class RightTriangle ://прямоугольный
    public Shape
{
    friend ostream &operator<< (ostream &out, Shape &a);
    friend class IsoscelesTriangle;
    friend class Quadrate;
private:
    CS points[3];
    void IsItRightTriangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy);
    void IsItTriangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy);
public:
    RightTriangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy, Color _color);
    ~RightTriangle();
    void Move(double _x, double _y);
    void Rotate(double _angle);
    void Scale(double _scale);
    ostream &put(ostream &out) const;
    bool IsInsideOfAnother(const Shape &other);

    // создает случайную фигуру
    static RightTriangle* createRandomShape();
};

void RotateShape(CS *_points, CS _center, double _angle, int _size);
void MoveShape(CS *_points, CS _center, double _x, double _y, int _size);
void NewTriangleCenter(CS * _points, CS & _center);
void ScaleShape(CS * _points, CS _center, double _scale, int _size);
int ShapeTest(CS *_points, const CS *_shapePoints, int size, int i);
double Length(double _ax, double _ay, double _bx, double _by);


#endif // LAB2_H
