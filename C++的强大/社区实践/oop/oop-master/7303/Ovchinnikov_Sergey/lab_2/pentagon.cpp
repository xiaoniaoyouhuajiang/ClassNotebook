#include "pentagon.h"
#include <cmath>

Pentagon::Pentagon(const Point &center,const Color& color, double _radius):
    Shape(center,color),
    radius(_radius){

    Turn(0);
}

Pentagon::Pentagon(const Pentagon& pentagon):
    Shape(pentagon.pos,pentagon.color,pentagon.angle),
    tops(pentagon.tops),
    radius(pentagon.radius){
}

void Pentagon::Turn(double _angle){
    this->angle += _angle;

    if( angle>360.0 ){
        int z = angle/360.0;
        angle = angle - z*360.0;
    }

    double x, y,fi;
    tops.clear();

    for(int i = 0; i<=4; i++){
        fi = (angle + 72 * i) * M_PI/180;

        x =  radius * sin(fi);
        y =   radius * cos(fi);

        tops.push_back( Point(x,y) + pos );
    } 
}

void Pentagon::Move(const Point& p){
    pos = p;
    Turn(0);
}

void Pentagon::Scale(double scale){
    radius*= scale;
    Turn(0);
}

double Pentagon::get_radius() const{
    return radius;
}

std::ostream& operator<<(std::ostream& out,const Pentagon& pentagon){
    out << "\n<---Pentagon--->\n";
    out << (Shape&) pentagon;
    out << "radius: " << pentagon.get_radius() << "\n";
    out << "points:\n"; 
    for(auto& el : pentagon.tops){
        out<<"( "<<el.x<<", "<<el.y<<" )\n";
    }
    out << "<---Pentagon--->\n";
    return out;

}