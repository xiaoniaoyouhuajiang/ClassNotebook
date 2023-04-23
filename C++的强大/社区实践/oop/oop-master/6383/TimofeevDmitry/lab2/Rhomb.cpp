#include "Rhomb.h"
Rhomb::Rhomb(std::string color,double width, double height):Parallelogram(color){
    if(fmin(width,height)<0)throw "Rhomb init error: negative width or height\n";
    pts.push_back(Point(width,0));
    pts.push_back(Point(0,height));
    pts.push_back(Point(-width,0));
    pts.push_back(Point(0,-height));
    onTransformed();
}
std::string Rhomb::toString() const {
    return std::string("Shape = Rhomb\n")
           +"id = "+std::to_string(getId())+"\ncolor = "+getColor().def+"\n"+"vertexes:\n"
           +"\t"+std::to_string(pts[0].x)+" "+std::to_string(pts[0].y)+"\n"+
           +"\t"+std::to_string(pts[1].x)+" "+std::to_string(pts[1].y)+"\n"+
           +"\t"+std::to_string(pts[2].x)+" "+std::to_string(pts[2].y)+"\n"+
           +"\t"+std::to_string(pts[3].x)+" "+std::to_string(pts[3].y)+"\n";
}