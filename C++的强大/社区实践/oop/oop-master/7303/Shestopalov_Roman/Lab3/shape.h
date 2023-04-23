#ifndef SHAPE_H
#define SHAPE_H
#include <cmath>
#pragma once
#include <iostream>
#include <vector>
#include <cmath>
const double M_PI = 3.14;

class Point {
public:
  Point(double x = 0, double y = 0): x(x), y(y) {}

  double x = 0;
  double y = 0;
};

std::ostream& operator<<(std::ostream& out, Point& p) {
  return out << "{x: " << p.x << ", y: " << p.y << "}";
}

class Shape {

protected:
  struct rgb {
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
  } color;

public:
  Shape(){
    static int id_glob = 0;
    id = id_glob++;
    countang = 0;
  }
   virtual void move(double x, double y) = 0;
   virtual void rotate(int angle) = 0;
   virtual void scale(double k) = 0;
   void setColor(rgb color) {
     this->color = color;
   }
   friend std::ostream& operator<<(std::ostream& out, Shape& shape);

  int angle = 0;
  int id;
  int countang;
  Point p;
};
#endif // SHAPE_H
