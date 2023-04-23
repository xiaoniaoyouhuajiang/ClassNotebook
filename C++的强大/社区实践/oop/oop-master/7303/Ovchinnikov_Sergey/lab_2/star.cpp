#include "star.h"
#include <cmath>

Star::Star(const Point &center,const Color& color, double _r1, double _r2,double angle):
    Shape(center,color),
    radius1(_r1),
    radius2(_r2){
    Turn(angle);
}

Star::Star(const Star& star):
    Shape(star.pos,star.color,star.angle),
    tops1(star.tops1),
    tops2(star.tops2),
    radius1(star.radius1),
    radius2(star.radius2){

}

 Star Star::operator+(const Star& star){
     Point point_temp((this->pos.x + star.pos.x)/2.0,(this->pos.y + star.pos.y)/2.0);
     double angle_temp = (this->angle + star.angle)/2.0;
     Color color_temp((this->color.red + star.color.red)/2,
                        (this->color.green + star.color.green)/2,
                        (this->color.blue + star.color.blue)/2 );
    double temp_r1 = (this->radius1 + star.radius1) /2.0;
    double temp_r2 = (this->radius2 + star.radius2) /2.0;

    return Star(point_temp,color_temp,temp_r1,temp_r2,angle);
 }

void Star::Turn(double _angle){
    this->angle += _angle;

    if( angle>360.0 ){
        int z = angle/360.0;
        angle = angle - z*360.0;
    }
    
    double x1, y1,x2,y2;
    tops1.clear();
    tops2.clear(); 

    for(int i = 0; i<=4; i++){
        double fi1 = ( angle + 36 + 72 * i) * M_PI/180;
        double fi2 = (angle + 72 * i ) * M_PI/180;

        x1 =  radius1 * sin(fi1);
        y1 =   radius1 * cos(fi1);

        x2 =  radius2 * sin(fi2);
        y2 =   radius2 * cos(fi2);

        tops1.push_back( Point(x1,y1) + pos );
        tops2.push_back( Point(x2,y2) + pos );

    }  
}

void Star::Move(const Point& p){
    pos = p;
    Turn(0);

}

void Star::Scale(double scale){
    radius1*= scale;
    radius2*= scale;

    Turn(0);
}

double Star::get_radius1() const{
    return radius1;
}

double Star::get_radius2() const{
    return radius2;
}

std::ostream& operator<<(std::ostream& out,const Star& star){
    out << "\n<---Star--->\n";
    out << (Shape&)star;
    out << "radius1: " << star.get_radius1() << "\n";
    out << "radius2: " << star.get_radius2() << "\n";
    out << "inner points:\n"; 
    for(auto& el : star.tops1){
        out<<"( "<<el.x<<"; "<<el.y<<" )\n";
    }
    out << "outer points:\n"; 
    for(auto& el : star.tops2){
        out<<"( "<<el.x<<", "<<el.y<<" )\n";
    }
    out << "<---Star--->\n";
    return out;

}