#include <iostream>
#include <cmath>

using namespace std;


#define PI 3.141592653


class Color {
public:
    explicit Color(unsigned r = 255, unsigned g = 255, unsigned b = 255) : red(r % 256), green(g % 256),
                                                                           blue(b % 256) {}

    unsigned getR() const { return red; };

    unsigned getG() const { return blue; };

    unsigned getB() const { return green; };

    Color &operator=(Color const &color) = default;

    friend ostream &operator<<(ostream &out, Color const &color) {
        out << "(" << color.red << "," << color.green << "," << color.blue << ")";
        return out;
    }

private:
    unsigned red, green, blue;
};


class Coord {
public:
    explicit Coord(double x = 0, double y = 0) : x(x), y(y) {}

    double getX() const { return x; }

    double getY() const { return y; }

    Coord &operator=(Coord const &new_coord) = default;

    friend ostream &operator<<(ostream &out, Coord const &coord) {
        out << "(" << coord.x << "," << coord.y << ")";
        return out;
    }

    friend Coord operator+(Coord const &c1, Coord const &c2) {
        return Coord(c1.getX() + c2.getX(), c1.getY() + c2.getY());
    }

private:
    double x, y;
};


class Shape {
public:
    static unsigned id;

    explicit Shape(Coord p = Coord(0, 0), Color c = Color(255, 255, 255), double a = 0) : position(p), color(c),
                                                                                          angle(a) {
        id++;
    }

    virtual void move(Coord new_position) {
        position = new_position;
    }

    virtual void rotate(double rotation_angle) {
        angle += rotation_angle;
    }

    virtual void setColor(Color new_color) {
        color = new_color;
    }

    virtual Color getColor() {
        return color;
    }

    virtual void scale(double) = 0;

    virtual void getPointCoords() = 0;

    friend ostream &operator<<(ostream &out, Shape const &shape) {
        cout << "Shape ID: " << shape.id << endl <<
             "Color: " << shape.color << endl <<
             "Position of the center: " << shape.position << endl <<
             "Clockwise rotation angle: " << shape.angle << endl;

        return out;
    }

protected:
    Color color;
    Coord position;
    double angle;
};

unsigned Shape::id = 0;

class Parallelogram : public Shape {
public:
    Parallelogram(double w, double h, double wha = 3.141592653, double a = 0, Color c = Color(255, 255, 255),
                  Coord p = Coord(0, 0)) : Shape(p, c, a),
                                           width(w), height(h), wh_angle(wha) {
        x1 = Coord(-w/2, h*cos(wha)/2);
        x2 = Coord(w/2, h*cos(wha)/2);
        x3 = Coord(-w/2+h*cos(wha), -h*cos(wha)/2);
        x4 = Coord(w/2+h*cos(wha), -h*cos(wha)/2);
    }

    void scale(double factor) override {
        height *= factor;
        width *= factor;
    }

    void getPointCoords() override {
        Coord x1_real(x1.getX()*cos(angle)-x1.getY()*sin(angle), x1.getX()*sin(angle)+x1.getY()*cos(angle));
        Coord x2_real(x2.getX()*cos(angle)-x2.getY()*sin(angle), x2.getX()*sin(angle)+x2.getY()*cos(angle));
        Coord x3_real(x3.getX()*cos(angle)-x3.getY()*sin(angle), x3.getX()*sin(angle)+x3.getY()*cos(angle));
        Coord x4_real(x4.getX()*cos(angle)-x4.getY()*sin(angle), x4.getX()*sin(angle)+x4.getY()*cos(angle));
        cout << "x1: " << x1_real + position  << endl
             << "x2: " << x2_real + position << endl
             << "x3: " << x3_real + position << endl
             << "x4: " << x4_real + position << endl;

    }

    friend ostream &operator<<(ostream &out, Parallelogram const &parallelogram) {

        cout << dynamic_cast<Shape const &>(parallelogram) << "Shape type: Parallelogram" << endl
             << "Width: " << parallelogram.width << endl <<
             "Height: " << parallelogram.height << endl <<
             "Angle between width and height: " << parallelogram.wh_angle << endl;

        return out;
    }


protected:
    double width, height, wh_angle;
    Coord x1, x2, x3, x4;
};

class Rectangle : public Shape {
public:

    Rectangle(double w, double h, double a = 0, Color c = Color(255, 255, 255),
              Coord p = Coord(0, 0)) : Shape(p, c, a), width(w), height(h) {
        x1 = Coord(-w/2, h/2);
        x2 = Coord(w/2, h/2);
        x3 = Coord(-w/2, -h/2);
        x4 = Coord(w/2, -h/2);
    }

    void scale(double factor) override {
        height *= factor;
        width *= factor;
    }

    void getPointCoords() override {
        Coord x1_real(x1.getX()*cos(angle)-x1.getY()*sin(angle), x1.getX()*sin(angle)+x1.getY()*cos(angle));
        Coord x2_real(x2.getX()*cos(angle)-x2.getY()*sin(angle), x2.getX()*sin(angle)+x2.getY()*cos(angle));
        Coord x3_real(x3.getX()*cos(angle)-x3.getY()*sin(angle), x3.getX()*sin(angle)+x3.getY()*cos(angle));
        Coord x4_real(x4.getX()*cos(angle)-x4.getY()*sin(angle), x4.getX()*sin(angle)+x4.getY()*cos(angle));
        cout << "x1: " << x1_real + position  << endl
             << "x2: " << x2_real + position << endl
             << "x3: " << x3_real + position << endl
             << "x4: " << x4_real + position << endl;
    }

    friend ostream &operator<<(ostream &out, Rectangle const &rectangle) {
        cout << dynamic_cast<Shape const &>(rectangle) << "Shape type: Rectangle" << endl <<
             "Width: " << rectangle.width << endl <<
             "Height: " << rectangle.height << endl;

        return out;
    }

protected:
    double width, height;
    Coord x1, x2, x3, x4;
};

class Hexagram : public Shape {
public:
    explicit Hexagram(double h, double a = 0, Color c = Color(255, 255, 255), Coord p = Coord(0, 0)) : Shape(p, c, a),
                                                                                                       height(h) {
        x1 = Coord(0, 2*h/3);
        x2 = Coord(h*tan(30*PI/180), -h/3);
        x3 = Coord(h*tan(30*PI/180), -h/3);
    }

    void scale(double factor) override {
        height *= factor;
    }

    void getPointCoords() override {
        Coord x1_real(x1.getX()*cos(angle)-x1.getY()*sin(angle), x1.getX()*sin(angle)+x1.getY()*cos(angle));
        Coord x2_real(x2.getX()*cos(angle)-x2.getY()*sin(angle), x2.getX()*sin(angle)+x2.getY()*cos(angle));
        Coord x3_real(x3.getX()*cos(angle)-x3.getY()*sin(angle), x3.getX()*sin(angle)+x3.getY()*cos(angle));
        cout << "x1: " << x1_real + position  << endl
             << "x2: " << x2_real + position << endl
             << "x3: " << x3_real + position << endl;
    }

    friend ostream &operator<<(ostream &out, Hexagram const &hexagram) {
        cout << dynamic_cast<Shape const &>(hexagram) << "Shape type: Hexagram" << endl <<
             "The distance between opposing rays: " << hexagram.height << endl;

        return out;
    }

private:
    double height;
    Coord x1, x2, x3;
};


int main() {
    Hexagram hex(120);
    Rectangle rect(120, 130, 0, Color(255, 255, 255), Coord(100, 100));
    Parallelogram para(10, 20);

    cout << hex << endl;
    cout << rect << endl;
    cout << para << endl;

    rect.rotate(PI/3);
    rect.getPointCoords();

    hex.move(Coord(20, 30));
    rect.rotate(PI);
    para.scale(1.2);
    rect.setColor(Color(100, 200, 30));

    cout << "Rectangle color: " << rect.getColor() << endl
         << "Hexagram color: " << hex.getColor() << endl << endl;

    cout << hex << endl;
    cout << rect << endl;
    cout << para << endl;

    return 0;
}