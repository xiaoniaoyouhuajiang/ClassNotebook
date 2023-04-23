#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "shape.h"

class Triangle: public Shape{
public:
    Triangle(Point p1, Point p2, Point p3): p1(p1), p2(p2), p3(p3) {
          this->id = id++;
        this->countang = 3;
    }

    bool check(){
      double a = sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
      double b = sqrt((p3.x - p1.x)*(p3.x - p1.x) + (p3.y - p1.y)*(p3.y - p1.y));
      double c = sqrt((p2.x - p3.x)*(p2.x - p3.x) + (p2.y - p3.y)*(p2.y - p3.y));
      if((a >= b+c)||(b >= a+c)||(c >= a+b)){
          std::cout<<"Not a triangle"<<std::endl;
          return 0;
        }
      return 1;
    }

    void move(double x, double y) {
        p1.x += x; p2.x += x; p3.x += x;
        p1.y += y; p2.y += y; p3.y += y;
    }

    void scale(double k){
        p1.x *= k; p2.x *= k; p3.x *= k;
        p1.y *= k; p2.y *= k; p3.y *= k;
    }

    void rotate(int ang){
    Point center;
    center.x = (p1.x+p2.x+p3.x)/3; center.y = (p1.y+p2.y+p3.y)/3;
    std::cout<<"Id = "<< id <<" center is"<< center << std::endl;
    double a = sqrt((center.x - p1.x)*(center.x - p1.x) + (center.y - p1.y)*(center.y - p1.y));
    double b = sqrt((p2.x - center.x)*(p2.x - center.x) + (p2.y - center.y)*(p2.y - center.y));
    double c = sqrt((p3.x - center.x)*(p3.x - center.x) + (p3.y - center.y)*(p3.y - center.y));
    this->angle += ang;

    p1.x = p1.x + sin(this->angle*M_PI/180)*a;
    p1.y = p1.y + a - cos(this->angle*M_PI/180)*a;

    p2.x = p2.x + sin(this->angle*M_PI/180)*b;
    p2.y = p2.y + b - cos(this->angle*M_PI/180)*b;

    p3.x = p3.x + sin(this->angle*M_PI/180)*b;
    p3.y = p3.y + c - cos(this->angle*M_PI/180)*c;
    }

    friend std::ostream& operator<<(std::ostream& out, Triangle& t);

private:
    Point p1;
    Point p2;
    Point p3;
};

std::ostream& operator<<(std::ostream& out, Triangle& t) {

  return out <<"Id = "<< t.id << t.p1 << t.p2 << t.p3;
}
#endif // TRIANGLE_H
