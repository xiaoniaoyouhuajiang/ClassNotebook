#ifndef MYFIGURES_H
#define MYFIGURES_H

#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>
#include <exception>

using namespace std;

static const double Pi = 3.14159265358979323846264338327950288419717;

struct Dot
{
    double x;
    double y;
};

struct RGB
{
    int R;
    int G;
    int B;
};

class Shape {
protected:
    int angle;
    RGB color;
    Dot centre;
    double scale_factor;
public:
    Shape(double _x, double _y)
    {
        centre.x = _x;
        centre.y = _y;
        scale_factor = 1;
        angle = 0;
        color = { 0,0,0 };
    }

    virtual ~Shape() {}

    virtual void MoveFigure(double other_x, double other_y) = 0;
    virtual void SetTurnAngle(int other_angle) = 0;
    virtual void Scaling(double k) = 0;

    void SetColor(int new_R, int new_G, int new_B) {
        color = { new_R, new_G, new_B };
    }

    void PrintShapeInfo(ostream& out) {
        out.precision(2);
        out << "Figure centre: (" << centre.x << ", " << centre.y << ")\n";
        out << "Angle of rotation = " << angle << endl;
        out << "Color (RGB): (" << color.R << ", " << color.G << ", " << color.B << ")\n";
        out << "Scale factor = " << scale_factor << endl;
        out << endl;
    }

    Dot getCentre() {
        return centre;
    }

    friend ostream& operator<<(ostream& out, Shape& sh)
    {
        sh.PrintShapeInfo(out);
        return out;
    }
};

class Rectangle : public Shape {
protected:
    double l1, l2;
    Dot A, B, C, D;
public:
    Rectangle(double _x, double _y, double _l1, double _l2)
        : Shape(_x, _y), l1(_l1), l2(_l2)
    {
        A.x = centre.x - l2 / 2;
        A.y = centre.y - l1 / 2;
        B.x = centre.x - l2 / 2;
        B.y = centre.y + l1 / 2;
        C.x = centre.x + l2 / 2;
        C.y = B.y;
        D.x = centre.x + l2 / 2;
        D.y = A.y;
    }

    void MoveFigure(double new_x, double new_y) {
        A.x += new_x - centre.x;
        A.y += new_y - centre.y;
        B.x += new_x - centre.x;
        B.y += new_y - centre.y;
        C.x += new_x - centre.x;
        C.y = B.y;
        D.x += new_x - centre.x;
        D.y = A.y;
        centre.x = new_x;
        centre.y = new_y;

    }

    void SetTurnAngle(int new_angle) {
        angle += new_angle;
        angle %= 360;
        double rad = angle * Pi / 180;

        vector<Dot> dots;
        dots.push_back(A); dots.push_back(B);
        dots.push_back(C); dots.push_back(D);

        for (auto& dot : dots) {
            Dot tmp_dot = dot;
            dot.x = tmp_dot.x * cos(rad) - tmp_dot.y * sin(rad);
            dot.y = tmp_dot.y * cos(rad) + tmp_dot.y * sin(rad);
        }

        A = dots[0]; C = dots[2];
        B = dots[1]; D = dots[3];
    }

    void Scaling(double k) {
        scale_factor *= k;
        centre.x *= k;
        centre.y *= k;
        B.x *= k;
        B.y *= k;
        C.x *= k;
        C.y *= k;
        D.x *= k;
        D.y *= k;
    }

    void PrintInfoAboutFigure(ostream& out)
    {
        out << "RECTANGLE" << endl;
        PrintShapeInfo(out);
        out << "Sides length: l1 = " << l1 << " l2 = " << l2 << endl;
        out << "DOTS COORDINATES:\n";
        out << "Dot A: (" << A.x << ", " << A.y << ")\n";
        out << "Dot B: (" << B.x << ", " << B.y << ")\n";
        out << "Dot C: (" << C.x << ", " << C.y << ")\n";
        out << "Dot D: (" << D.x << ", " << D.y << ")\n";
        out << "-----------------------------------------------";
        out << endl;
    }
};
class Pentagon : public Shape {
protected:
    Dot A, B, C, D, E;
public:
    Pentagon(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5)
        : Shape((x1 + x2 + x3 + x4 + x5) / 5, (y1 + y2 + y3 + y4 + y5) / 5) {
        A.x = x1;
        A.y = y1;
        B.x = x2;
        B.y = y2;
        C.x = x3;
        C.y = y3;
        D.x = x4;
        D.y = y4;
        E.x = x5;
        E.y = y5;
    }

    void MoveFigure(double new_x, double new_y) {
        A.x += new_x - centre.x;
        A.y += new_y - centre.y;
        B.x += new_x - centre.x;
        B.y += new_y - centre.y;
        C.x += new_x - centre.x;
        C.y += new_y - centre.y;
        D.x += new_x - centre.x;
        D.y += new_y - centre.y;
        E.x += new_x - centre.x;
        E.y += new_y - centre.y;
        centre.x = new_x;
        centre.y = new_y;

    }

    void SetTurnAngle(int new_angle) {
        angle += new_angle;
        angle %= 360;
        double rad = angle * Pi / 180;

        vector<Dot> dots;
        dots.push_back(A); dots.push_back(B);
        dots.push_back(C); dots.push_back(D);
        dots.push_back(E);

        for (auto& dot : dots) {
            Dot tmp_dot = dot;
            dot.x = tmp_dot.x * cos(rad) - tmp_dot.y * sin(rad);
            dot.y = tmp_dot.y * cos(rad) + tmp_dot.y * sin(rad);
        }

        A = dots[0]; C = dots[2];
        B = dots[1]; D = dots[3];
        E = dots[4];
    }

    void Scaling(double k) {
        scale_factor *= k;
        centre.x *= k;
        centre.y *= k;

        B.x *= k;
        B.y *= k;
        C.x *= k;
        C.y *= k;
        D.x *= k;
        D.y *= k;
        E.x *= k;
        E.y *= k;
    }

    void PrintInfoAboutFigure(ostream& out)
    {
        out << "PENTAGON" << endl;
        PrintShapeInfo(out);
        out << "DOTS COORDINATES:\n";
        out << "Dot A: (" << A.x << ", " << A.y << ")\n";
        out << "Dot B: (" << B.x << ", " << B.y << ")\n";
        out << "Dot C: (" << C.x << ", " << C.y << ")\n";
        out << "Dot D: (" << D.x << ", " << D.y << ")\n";
        out << "Dot E: (" << E.x << ", " << E.y << ")\n";
        out << "-----------------------------------------------";
        out << endl;
    }
};


class Pentagrama : public Shape {
protected:
    Dot A, B, C, D, E;
public:
    Pentagrama(double x1, double y1, double radius)
        : Shape(x1, y1) {

        double angle = 2 * Pi / 5;
        A.x = x1 + radius * cos(angle * 0);
        A.y = y1 + radius * sin(angle * 0);
        B.x = x1 + radius * cos(angle * 1);
        B.y = y1 + radius * sin(angle * 1);
        C.x = x1 + radius * cos(angle * 2);
        C.y = y1 + radius * sin(angle * 2);
        D.x = x1 + radius * cos(angle * 3);
        D.y = y1 + radius * sin(angle * 3);
        E.x = x1 + radius * cos(angle * 4);
        E.y = y1 + radius * sin(angle * 4);


    }

    void MoveFigure(double new_x, double new_y) {
        A.x += new_x - centre.x;
        A.y += new_y - centre.y;
        B.x += new_x - centre.x;
        B.y += new_y - centre.y;
        C.x += new_x - centre.x;
        C.y += new_y - centre.y;
        D.x += new_x - centre.x;
        D.y += new_y - centre.y;
        E.x += new_x - centre.x;
        E.y += new_y - centre.y;
        centre.x = new_x;
        centre.y = new_y;

    }

    void SetTurnAngle(int new_angle)
    {
        angle += new_angle;
        angle %= 360;
        double rad = angle * Pi / 180;

        vector<Dot> dots;
        dots.push_back(A); dots.push_back(B);
        dots.push_back(C); dots.push_back(D);
        dots.push_back(E);

        for (auto& dot : dots) {
            Dot tmp_dot = dot;
            dot.x = tmp_dot.x * cos(rad) - tmp_dot.y * sin(rad);
            dot.y = tmp_dot.y * cos(rad) + tmp_dot.y * sin(rad);
        }

        A = dots[0];
        C = dots[2];
        B = dots[1];
        D = dots[3];
        E = dots[4];
    }

    void Scaling(double k) {
        scale_factor *= k;
        centre.x *= k;
        centre.y *= k;

        B.x *= k;
        B.y *= k;
        C.x *= k;
        C.y *= k;
        D.x *= k;
        D.y *= k;
        E.x *= k;
        E.y *= k;
    }

    void PrintInfoAboutFigure(ostream& out)
    {
        out << "Pentagrama" << endl;
        PrintShapeInfo(out);
        out << "DOTS COORDINATES:\n";
        out << "Dot A: (" << A.x << ", " << A.y << ")\n";
        out << "Dot B: (" << B.x << ", " << B.y << ")\n";
        out << "Dot C: (" << C.x << ", " << C.y << ")\n";
        out << "Dot D: (" << D.x << ", " << D.y << ")\n";
        out << "Dot E: (" << E.x << ", " << E.y << ")\n";
        out << "-----------------------------------------------";
        out << endl;
    }
};


#endif //MYFIGURES_H
