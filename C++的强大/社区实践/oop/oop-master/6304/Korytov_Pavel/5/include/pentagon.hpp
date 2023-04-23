#ifndef PENTAGON_HPP
#define PENTAGON_HPP

#include "point.h"
#include <vector>
#include <stdexcept>

using std::vector;

class PentagonRandom : public Shape{
public:
    PentagonRandom() : Shape(){
        for (int i = 0; i < 5; i++)
            pts.push_back(Point(0,0));
    }

    vector<Point> points(){
        vector<Point> res;
        for (auto it : pts){
            Point p = it;
            p.AdjustR(mult);
            p.AdjustPhi(angle);
            p = p + center;
            res.push_back(p);
        }
        return res;
    }
    Point getPoint(int n){
        if ((n >= 0) && (n < 5)){
            Point p = pts[n];
            p.AdjustR(mult);
            p.AdjustPhi(angle);
            p = p + center;
            return p;
        }
        else{
            throw std::out_of_range("Out of range");
        }
    }
    double square(){
        double a=0; double b=0; double xp=pts[0].GetX()*mult; double yp=pts[0].GetY()*mult;
        for (vector<Point>::iterator it = ++pts.begin(); it < pts.end(); it++){
            a = a + xp * it->GetY()*mult;
            b = b + yp * it->GetX()*mult;
            xp = it->GetX()*mult;
            yp = it->GetY()*mult;
        }
        a = a + xp * pts[0].GetY()*mult;
        b = b + yp * pts[0].GetX()*mult;
        return abs((a-b)/2);
    }
    friend ostream& operator<<(ostream& os, const PentagonRandom& dt){
        os << "C: " << dt.center;
        for (auto it : dt.pts){
            os << " P " << it;
        }
        return os;
    }

protected:
    Point calculateCenter(){
        Point cnt;
        for (auto it : pts){
            cnt = cnt + it;
        }
        cnt = cnt / 5;
        return cnt;
    }
    void adjustPoints(){
        center = calculateCenter();
        for (vector<Point>::iterator it = pts.begin(); it < pts.end(); it++){
            *it = *it - center;
        }
    }
    vector<Point> pts;
};

class Pentagon : public PentagonRandom{
public:
    Pentagon() : PentagonRandom()
    {}
    Pentagon(vector<Point> points) : PentagonRandom() {
        pts = points;
        adjustPoints();
    }
    Pentagon(Point p1, Point p2, Point p3, Point p4, Point p5) : PentagonRandom(){
        pts = {p1, p2, p3, p4, p5};
        adjustPoints();
    }
    Pentagon(int min, int max) : PentagonRandom() {
        center = Point().Rand(min, max);
        int rd = (max - min) / 10;
        double PhiDeg = 0;
        pts.clear();
        for (int i = 0; i < 5; i++){
            PhiDeg = 72*i + rand() % 72;
            double PhiRad = PhiDeg/180*M_PI;
            Point p;
            p.SetR(rand()%rd + rd/2);
            p.SetPhi(PhiRad);
            p = p + center;
            pts.push_back(p);
        }
        adjustPoints();
    }
};
#endif