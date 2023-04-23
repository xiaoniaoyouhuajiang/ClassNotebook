#include "figure.h"
size_t Shape::counter = 0;
void Shape::set_color(Color color){
    
    this->color=color;
    
}
Color Shape::get_color(){
    
    return color;
    
}

void Shape::rotate(double _angle)
{
    angle = _angle;
}

std::ostream& operator <<(std::ostream& os,const Shape& p)
{
    p.print(os);
    return os;
}


double Shape::distance(const Point &p) const
{
    Point tmp = p;
    tmp.rotate(-angle);
    std::vector<Point> v = getVertices();
    double minDist = tmp.distance(v[0]);
    for(auto it = v.begin() + 1; it != v.end(); it++)
    {
        double currentDist = tmp.distance(*it);
        minDist = std::min(currentDist, minDist);
    }
    return minDist;
}