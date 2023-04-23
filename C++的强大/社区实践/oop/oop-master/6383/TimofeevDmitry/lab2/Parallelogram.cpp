#include "Parallelogram.h"

Parallelogram::Parallelogram(std::string color,double angle, double a, double b):Shape(color){
    if(fmin(a,b)<0)throw "Parallelogram init error: negative a or b\n";
    pts.push_back(Point(0,0));
    pts.push_back(Point(a,0));
    pts.push_back(Point(a+cos(angle)*b,sin(angle)*b));
    pts.push_back(Point(cos(angle)*b,sin(angle)*b));
    onTransformed();
}
void Parallelogram::applyForAnyPoint(std::function<void(Point&)> const & f) {
    for(Point& p:pts)f(p);
};
std::string Parallelogram::toString() const {
    return std::string("Shape = Parallelogram\n")
           +"id = "+std::to_string(getId())+"\ncolor = "+getColor().def+"\n"+"vertexes:\n"
           +"\t"+std::to_string(pts[0].x)+" "+std::to_string(pts[0].y)+"\n"+
           +"\t"+std::to_string(pts[1].x)+" "+std::to_string(pts[1].y)+"\n"+
           +"\t"+std::to_string(pts[2].x)+" "+std::to_string(pts[2].y)+"\n"+
           +"\t"+std::to_string(pts[3].x)+" "+std::to_string(pts[3].y)+"\n";
}
Parallelogram::Parallelogram(std::string color):Shape(color){}

double Parallelogram::getA() {
    return a;
}

double Parallelogram::getB() {
    return b;
}

void Parallelogram::onTransformed() {
    a=length(pts[0],pts[1]);
    b=length(pts[0],pts[3]);
}
