#include "pentagon.h"
#include <iostream>
#include <math.h>

using namespace std;

pentagon::pentagon(const point (&vertexes)[5], const Color &color) : figure(color) {
    copy(vertexes, vertexes + 5, this->vertexes);
}

pentagon::pentagon(const pentagon& other) : pentagon(other.vertexes, other.m_color) {}

pentagon& pentagon::operator=(const pentagon& other) {
    copy(other.vertexes, other.vertexes + 5, vertexes);
    m_color = other.m_color;
    return *this;
}

point pentagon::get_center() const {
    point center;
    for (auto x : vertexes) {
        center += x;
    }
    return center / 5;
}


void pentagon::scale(double num) {
    point center = get_center();
    for (auto &x : vertexes) {
        x = (x - center) * num + center;
    }
}



void pentagon::turn(double angle) {
    point center = get_center();
    double cosa = cos(angle);
    double sina = sin(angle);
    for (auto &x : vertexes) {
        x -= center;
        x = point(x.getX() * cosa + x.getY() * sina, x.getX() * -sina + x.getY() * cosa) + center;
    }
}

void pentagon::shift(double num1,double num2){
    point shift_point(num1, num2);
    for (auto &x : vertexes) {
        x += shift_point;
    }
}

double scal(point a, point b, point c) {
    a -= c;
    b -= c;
    return a.getX() * b.getX() + a.getY() * b.getY();
}

double pentagon::distance(int x, int y) {
    double dist = INFINITY;
    point p(x, y);
    for (int i = 0; i < 5; ++i) {
        point l = vertexes[i];
        point r = vertexes[(i + 1) % 5];

        dist = min(min(dist, (l - p).len()), (r - p).len());

        if (scal(l, r, p) < 0) {
            double a = r.getY() - l.getY();
            double b = l.getX() - r.getX();
            double c = -l.getX() * a - l.getY() * b;
            dist = min(dist, abs(a * x + b * y + c) / sqrt(a * a + b * b));
        }
    }
    return dist;
}


void pentagon::print(std::ostream &os)
{
    for (int i = 0; i < 5; ++i) {
        os << "Координаты точки " << char('A' + i) << " =(" << vertexes[i].getX() << " , " << vertexes[i].getY() << ")" << std::endl;
    }
	os << "цвет фигуры " << m_color.r << ' ' << m_color.g << ' ' << m_color.b << "\n\n";

}
