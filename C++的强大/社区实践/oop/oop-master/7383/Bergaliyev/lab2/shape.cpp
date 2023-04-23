#include "shape.hpp"

unsigned int Shape::count = 1;

void Shape::scale(double scale_ratio){
    double r1, r2, r3, r4;
    double angle1, angle2, angle3, angle4;
    r1 = center.distance(v1);
    angle1 = asin((v1.y - center.y) / r1);
    if(std::abs(v1.x - center.x) < eps)
	angle1 = M_PI - angle1;
    v1.y = center.y + scale_ratio * r1 * sin(angle1);
    v1.x = center.x + scale_ratio * r1 * cos(angle1); 
    r2 = center.distance(v2);
    angle2 = asin((v2.y - center.y) / r2);
    if(std::abs(v2.x - center.x) < eps)
	angle2 = M_PI - angle2;
    v2.y = center.y + scale_ratio * r2 * sin(angle2);
    v2.x = center.x + scale_ratio * r2 * cos(angle2); 
    r3 = center.distance(v3);
    angle3 = asin((v3.y - center.y) / r3);
    if(std::abs(v3.x - center.x) < eps)
	angle3 = M_PI - angle3;
    v3.y = center.y + scale_ratio * r3 * sin(angle3);
    v3.x = center.x + scale_ratio * r3 * cos(angle3); 
    r4 = center.distance(v4);
    angle4 = asin((v4.y - center.y) / r4);
    if(std::abs(v4.x - center.x) < eps)
	angle4 = M_PI - angle4;
    v4.y = center.y + scale_ratio * r4 * sin(angle4);
    v4.x = center.x + scale_ratio * r4 * cos(angle4); 
}

void Shape::relocate(Point new_center){
    v1.x += new_center.x - center.x;
    v1.y += new_center.y - center.y;
    v2.x += new_center.x - center.x;
    v2.y += new_center.y - center.y;
    v3.x += new_center.x - center.x;
    v3.y += new_center.y - center.y;
    v4.x += new_center.x - center.x;
    v4.y += new_center.y - center.y;
    center = new_center;
}

void Shape::rotate(double angle){
    double r1, r2, r3, r4;
    double angle1, angle2, angle3, angle4;
    r1 = center.distance(v1);
    angle1 = asin((v1.y - center.y) / r1);
    if(std::abs(v1.x - center.x) < eps)
	angle1 = M_PI - angle1;
    angle1 -= angle;
    v1.y = center.y + r1 * sin(angle1);
    v1.x = center.x + r1 * cos(angle1); 
    r2 = center.distance(v2);
    angle2 = asin((v2.y - center.y) / r2);
    if(std::abs(v2.x - center.x) < eps)
	angle2 = M_PI - angle1;
    angle2 -= angle;
    v2.y = center.y + r2 * sin(angle2);
    v2.x = center.x + r2 * cos(angle2); 
    r3 = center.distance(v3);
    angle3 = asin((v3.y - center.y) / r3);
    if(std::abs(v3.x - center.x) < eps)
	angle3 = M_PI - angle3;
    angle3 -= angle;
    v3.y = center.y + r3 * sin(angle3);
    v3.x = center.x + r3 * cos(angle3); 
    r4 = center.distance(v4);
    angle4 = asin((v4.y - center.y) / r4);
    if(std::abs(v4.x - center.x) < eps)
	angle4 = M_PI - angle4;
    angle4 -= angle;
    v4.y = center.y + r4 * sin(angle4);
    v4.x = center.x + r4 * cos(angle4); 
}

std::ostream & operator<<(std::ostream & ostream, Point const & p){    
    return ostream << "(" << (std::abs(p.x) < eps ? 0 : p.x) << ", " << (std::abs(p.y) < eps ? 0 : p.y) << ") ";
}

std::ostream & operator<<(std::ostream & ostream, Color const & color){
    return ostream << "R=" << (int)color.red << " G=" << (int)color.green << " B=" << (int)color.blue;
}

std::ostream & operator<<(std::ostream & ostream, Shape const & shape) {
    return shape.print(ostream) << "id=" << shape.get_id() << std::endl << shape.get_color() << std::endl << "Vertices: " << shape.get_v1() << shape.get_v2() << shape.get_v3() << shape.get_v4() << std::endl << std::endl;
}
