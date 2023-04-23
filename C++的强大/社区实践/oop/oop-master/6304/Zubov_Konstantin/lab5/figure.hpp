#ifndef figure_hpp
#define figure_hpp

#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdint>

namespace last
{
struct point
{
    double x;
    double y;
};

class Shape
{
public:

    Shape( double x, double y ) : x(x), y(y),angle(0),color(0,0,0){}

    double L;

    void set_Position( double x1, double y1 )
    {

        for(auto& pnt : vec_of_points)
        {
            pnt.x += x1 - x;
            pnt.y += y1 - y;
        }
        this->x = x1;
        this->y = y1;

    }

    virtual void scaling(double k)=0;
    virtual double getlength()=0;
    void for_scale(double k){
            for(auto& pnt : vec_of_points)
        {
            pnt.x *= k;
            pnt.y *= k;
        }
    }

    void changeColour(int r, int g, int b){
        color={r,g,b};
    }
    void getcentr(double& s,double& d){
        s==x;
        d==y;
    }


    virtual void turn_to_Angle( double user_angle )
    {
        if( user_angle == 360||user_angle == 0 )
                return;

        angle+=user_angle;
        angle%=360;
        double new_x;
        double new_y;
        double to_rad=angle*M_PI/180;
        for(auto& bt: vec_of_points){
                new_x=bt.x*cos(to_rad)-bt.y*sin(to_rad);
                new_y=bt.y*cos(to_rad)+bt.x*sin(to_rad);
                bt.x=new_x;
                bt.y=new_y;
        }
    }
        void print(std::ostream& out)
    {
        out <<  "---------------"<<std::endl;
        out << "Center: " <<x<<','<<y<<std::endl;
        out << "Angle: " <<angle<<'\n';
        out << "Point number: " <<vec_of_points.size()<<std::endl;
        out << "Color: "<<color.r<<" "<<color.g<<" "<<color.b<<std::endl;
        for(auto p : vec_of_points)
            out << "x: " << p.x << " y: " << p.y << std::endl;

   }
        virtual void print_unique_pmts(std::ostream& out)=0;
        friend std::ostream& operator<<(std::ostream& out, Shape& in){
        in.print(out);
        in.print_unique_pmts(out);
        return out;
    }
    std::string shape_type(){
	return this->type;
}
        virtual ~Shape(){}



protected:
    struct Color{
    int r;
    int g;
    int b;
    Color (int r, int g, int b):r(r),g(g),b(b){}
};
    std::vector<point> vec_of_points;
    double x;
    double y;
    int angle; // ugol povorota;
    Color color;
    std::string type;

 };


class Ellipse : public Shape{
public:
    Ellipse(double x, double y, double R, double r) : Shape(x,y), R(R), r(r){
        vec_of_points.insert(vec_of_points.end(),{x+R,y});
        vec_of_points.insert(vec_of_points.end(),{x,y+r});
        vec_of_points.insert(vec_of_points.end(),{x-R,y});
        vec_of_points.insert(vec_of_points.end(),{x,y-r});
        using namespace std;
        focus = max(R,r)*sqrt(1-(min(R,r)*min(R,r))/(max(R,r)*max(R,r)));
        L=2*3.14*sqrt((pow(R,2)+pow(r,2))/2);
        this->type="Ellipse";
    }

    void scaling(double k){
        for_scale(k);
        r*=k;
        R*=k;
        focus*=k;
    }

    double getlength(){

        return L;
    }

    void print_unique_pmts(std::ostream& out){
        out<<"R: "<<R<<std::endl;
        out<<"r: "<<r<<std::endl;
        out<<"F: "<<focus<<std::endl;
        out<<"L: "<<L<<std::endl;
        out <<  "---------------"<<std::endl;
    }

 protected:
    double R, r;
    double focus;
    double L;
};

class Circle : public Shape{
public:
    Circle(double x, double y, double R): Shape(x,y), R(R){
        vec_of_points.insert(vec_of_points.end(),{x+R,y});
        L=2*M_PI*R;
        this->type="Circle";
    }
        void scaling(double k){
        for_scale(k);
        R*=k;
        L*=k;

    }
        double getlength(){
        return L;
    }
       void print_unique_pmts(std::ostream& out){
        out<<"R: "<<R<<std::endl;
        out<<"L: "<<L<<std::endl;
        out <<  "---------------"<<std::endl;
    }
  protected:
   double R;
   double L;
};

class Arc : public Shape {
public:
    Arc(double x, double y, double R, int ang1,int ang2): Shape(x,y), R(R), ang1(ang1), ang2(ang2){
       vec_of_points.insert(vec_of_points.end(),{x+R,y});
       ang1%=360;
       ang2%=360;
       L=(R*M_PI*(abs(ang1-ang2)))/180;
       this->type="Arc";
    }
    double getlength(){
        return L;
    }
    void scaling(double k){
        for_scale(k);
        R*=k;
        L*=k;
}
        void print_unique_pmts(std::ostream& out){
        out<<"R: "<<R<<std::endl;
        out<<"L: "<<L<<std::endl;
        out <<  "---------------"<<std::endl;
    }
protected:
int ang1,ang2; // ang1- ugol nachala dugi, ang2 - ugol konca dugi.
double L; // dlina dugi
double R;
};
}
#endif //figure_hpp
