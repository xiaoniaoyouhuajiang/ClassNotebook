#include "square.h"
#include <cmath>

Square::Square(const Point &center,const Color& color, double _a):
    Shape(center,color), 
    a(_a){
    Turn(0);
}

Square::Square(const Square& square):
    Shape(square.pos,square.color,square.angle),
    tops(square.tops),
    a(square.a){
}

void Square::Turn(double _angle){
    this->angle += _angle;

    if( angle>360.0 ){
        int z = angle/360.0;
        angle = angle - z*360.0;
    }

    double x, y;
    double _x,_y;
    double fi = angle *M_PI/180;

    tops.clear();
    for(int i = 1;i<= 4;i++){
        switch (i){
            case 1:x = y = -a/2;break;
            case 2:x = -a/2; y = -x; break;
            case 3:x = y = a/2;break;
            case 4:x = a/2; y = -x; break;
        }

        _x = x *cos(fi) - y*sin(fi);
        _y = x *sin(fi) + y * cos(fi);

        tops.push_back(Point(_x,_y) + pos);
    }
}

void Square::Move(const Point& p){
	pos = p;
    Turn(0);
}
void Square::Scale(double scale){
	a*=scale;
    Turn(0);
}

double Square::get_a() const{
    return a;
}

std::ostream& operator<<(std::ostream& out,const Square& square){
    out << "\n<---Square--->\n";
    out << (Shape&)square;
    out << "a: " << square.get_a() << "\n";
    out << "Points:\n"; 
    for(auto& el : square.tops){
        out<<"( "<<el.x<<", "<<el.y<<" )\n";
    }
    out << "<---Square--->\n";
    return out;
}