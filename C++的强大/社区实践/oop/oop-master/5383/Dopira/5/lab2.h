#ifndef LAB2_H
#define LAB2_H

#include <iostream>
#include <ostream>
#include <functional>
#include <random>
#include <chrono>

const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
static const int magicborder = 1 << 8;


struct Point {
    int x;
    int y;

    Point(int _x, int _y) : x(_x), y(_y) {}

    bool operator==(const Point &p) const { return (x == p.x && y == p.y); }
    friend std::ostream& operator<<(std::ostream &os, const Point& p)
    {
        os << "(" << p.x << "; " << p.y << ")";
        return os;
    }
};

class Color {
public:
    unsigned int red;
    unsigned int green;
    unsigned int blue;

    Color(unsigned int _red, unsigned int _green, unsigned int _blue) :
            red(_red), green(_green), blue(_blue) {}

    bool operator==(const Color &other) const {
        return (red == other.red &&
                green == other.green &&
                blue == other.blue);
    }

    friend std::ostream& operator<<(std::ostream &os, const Color& p)
    {
        os << "(" << p.red << "; " << p.green << "; " << p.blue << ")";
        return os;
    }
};
class Shape{
private:
    static size_t counter;
    Color color;
public:
    static Shape* createRandomShape();


    Shape(Color color) : color(color), id(counter++) {}
    virtual ~Shape(){}
    virtual void move(int dx, int dy)=0;
    virtual void rotate(int angle)=0;
    virtual void scale(int k)=0;
    Color getColor() const;
    void setColor(Color color);
    const bool operator ==(const Shape& other) const;
    friend std::ostream&operator<<(std::ostream& os, Shape& p);
    virtual void print(std::ostream& os) = 0;
protected:
    unsigned int id;

};

class Ellipse : public Shape {
protected:
    unsigned int a;
    unsigned int b;
    unsigned int fi;
    Point center;
public:
    Ellipse(Color color, Point center, unsigned int a=0, unsigned int b=0, unsigned int fi=0) :
            Shape(color), a(a), b(b), fi(fi%360), center(center) {}
    ~Ellipse() {}

    // create Random Ellipse
    static Ellipse* createRandomShape();


    void move(int dx, int dy) override;
    void rotate(int angle) override;
    void scale(int k) override;
    Point getCenter() const;
    unsigned int getAAxis();
    unsigned int getBAxis();
    unsigned int getAngle();

    void print(std::ostream& os) override;
protected:

};

class SectorOfEllipse : public Ellipse {
private:
    int f1;
    int f2;
public:
    SectorOfEllipse (Color color = Color(0, 0, 0), Point center = Point(0, 0), int a=0, int b=0, unsigned int fi=0, unsigned int f1 = 0, unsigned int f2 = 0) :
            Ellipse (color,center,a,b, fi),
            f1(f1%360),
            f2(f2%360)
    {
    }
    ~SectorOfEllipse(){}

    // create random Sector
    static SectorOfEllipse* createRandomShape();


    static void split (Ellipse* ellipse, SectorOfEllipse* s1, SectorOfEllipse* s2, SectorOfEllipse* s3);

    bool operator == (const SectorOfEllipse &other) const;

    void print(std::ostream& os) override;
protected:

};


class Parallelogram : public Shape {
private:
    Point a;
    Point b;
    Point c;
    Point d;
public:
    Parallelogram(Color color, Point a, Point b, Point c, Point d) : Shape (color), a(a), b(b), c(c), d(d) {}
    ~Parallelogram(){}

    // create random Parallelogram
    static Parallelogram* createRandomShape();

    bool checkParallelogram(Point a, Point b, Point c, Point d);
    void move(int dx, int dy) override;
    void rotate(int angle) override;
    void scale(int k) override;

    void print(std::ostream& os) override;

protected:

};



#endif //OOPLAB5VALERIA_2_H
