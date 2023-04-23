#ifndef REGULAR_PENTAGON_HPP
#define REGULAR_PENTAGON_HPP

#include "point.h"
#include "pentagon.hpp"

class RegularPentagon : public PentagonRandom
{
public:
    RegularPentagon(Point cnt = Pzero, Point p = Pzero) : PentagonRandom(){
        center = cnt;
        p = p - cnt;
        pts.clear();
        makePoints(p);
    }
    RegularPentagon(Point cnt, double rad) : PentagonRandom()
    {
        center = cnt;
        Point p;
        p.SetR(rad);
        makePoints(p);
    }
private:
    void makePoints(Point p){
        double ang = 0;
        for (int i = 0; i < 5; i++, ang+=(2*M_PI/5)){
            Point temp = p;
            temp.SetPhi(ang);
            pts[i] = temp;
        }
    }
};

#endif