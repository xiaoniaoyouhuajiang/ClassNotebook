#ifndef TRAP_H
#define TRAP_H
#include "shape.h"

class Trap: public Shape{
public:
    Trap(Point p1, Point p2, Point p3, Point p4): p1(p1), p2(p2), p3(p3), p4(p4) {
    this->id = id++;
      }

    bool check(){
      if(! ( ((p1.x - p2.x) == (p3.x - p4.x)) || ((p1.y - p2.y) == (p3.y - p4.y)) ) ){
      std::cout<<"Not a trap"<<std::endl;
      return 0;
     }
      return 1;
     }
    void move(double x, double y) {
        p1.x += x; p2.x += x; p3.x += x; p4.x +=x;
        p1.y += y; p2.y += y; p3.y += y; p4.y +=y;
    }

    void scale(double k){
        p1.x *= k; p2.x *= k; p3.x *= k; p4.x *= k;
        p1.y *= k; p2.y *= k; p3.y *= k; p4.y *= k;
    }

    void rotate(int ang){
    Point center;
    center.x = (p1.x+p2.x+p3.x+p4.x)/4; center.y = (p1.y+p2.y+p3.y+p4.y)/4;
    std::cout<<"Id = "<< id <<" center is"<< center << std::endl;
    double a = sqrt((center.x - p1.x)*(center.x - p1.x) + (center.y - p1.y)*(center.y - p1.y));
    double b = sqrt((p2.x - center.x)*(p2.x - center.x) + (p2.y - center.y)*(p2.y - center.y));
    double c = sqrt((p3.x - center.x)*(p3.x - center.x) + (p3.y - center.y)*(p3.y - center.y));
    double d = sqrt((p4.x - center.x)*(p4.x - center.x) + (p4.y - center.y)*(p4.y - center.y));
    this->angle += ang;

    p1.x = p1.x + sin(this->angle*M_PI/180)*a;
    p1.y = p1.y + a - cos(this->angle*M_PI/180)*a;

    p2.x = p2.x + sin(this->angle*M_PI/180)*b;
    p2.y = p2.y + b - cos(this->angle*M_PI/180)*b;

    p3.x = p3.x + sin(this->angle*M_PI/180)*c;
    p3.y = p3.y + c - cos(this->angle*M_PI/180)*c;

    p4.x = p4.x + sin(this->angle*M_PI/180)*d;
    p4.y = p4.y + d - cos(this->angle*M_PI/180)*d;
    }

    friend std::ostream& operator<<(std::ostream& out, Trap& tr);

    private:
        Point p1;
        Point p2;
        Point p3;
        Point p4;

    };
std::ostream& operator<<(std::ostream& out, Trap& tr) {

  return out <<"Id = "<< tr.id << tr.p1 << tr.p2 << std::endl
             << tr.p3 << tr.p4;
        }
#endif // TRAP_H