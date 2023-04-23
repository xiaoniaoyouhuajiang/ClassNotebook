#include "Triangle.h"

Triangle::Triangle(std::string color,const Point& a,const Point& b, const Point& c):Shape(color){
    pts.push_back(a);
    pts.push_back(b);
    pts.push_back(c);
    onTransformed();
}
void Triangle::applyForAnyPoint(std::function<void(Point&)> const & f) {
    for(Point& p:pts)f(p);
};
std::string Triangle::toString() const  {
    return std::string("Shape = Triangle\n")
           +"id = "+std::to_string(getId())+"\ncolor = "+getColor().def+"\n"+"vertexes:\n"
           +"\t"+std::to_string(pts[0].x)+" "+std::to_string(pts[0].y)+"\n"+
           +"\t"+std::to_string(pts[1].x)+" "+std::to_string(pts[1].y)+"\n"+
           +"\t"+std::to_string(pts[2].x)+" "+std::to_string(pts[2].y)+"\n";

}

double Triangle::getAB() { return ab;}
double Triangle::getAC() { return ac;}
double Triangle::getBC() { return bc;}

void Triangle::onTransformed() {
    ab=length(pts[0],pts[1]);
    ac=length(pts[0],pts[2]);
    bc=length(pts[1],pts[2]);
}
