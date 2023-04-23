#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>
#include <exception>

using namespace std;

const double PI = 3.14159265358979323846264338327950288419717;

struct Point
{
    double x;
    double y;
};

struct RGB
{
    int R;
    int G;
    int B;
};
class Shape {

protected:
    static int i;
    vector<Point> points;
    int angle;
    RGB color;
    Point center;
    double scale;
    Point t;

public:

    Shape()
    {
        center={0, 0};
        color = {0, 0, 0};
        scale = 1;
        angle = 0;
        i++;

    }

    void MoveFigure(Point new_center){
        double dx = new_center.x - center.x;
        double dy = new_center.y - center.y;
        for(int i = 0;i<points.size();i++){
            points[i].x = points[i].x+dx;
            points[i].y = points[i].y+dy;
        }
        center = new_center;
    }

    void SetTurnAngle(int new_angle) {
        angle = new_angle;
        new_angle%=360;
        double a = new_angle*PI/180;

        double _x, _y;

        for (unsigned int i = 0; i < points.size(); ++i) {
            _x = points[i].x;
            _y = points[i].y;
            points[i].x = ( _x - center.x ) * cos(a) - ( _y - center.y ) * sin(a) + center.x;
            points[i].y = ( _x - center.x ) * sin(a) + ( _y - center.y ) * cos(a) + center.y;
            if(points[i].x<0.000001)
                points[i].x = 0;
            if(points[i].y<0.000001)
                points[i].y = 0;
        }

    }

    virtual void Scaling(double k) = 0;

    void SetColor(int new_R, int new_G, int new_B) {
        color.R = new_R;
        color.G = new_G;
        color.B = new_B;
    }

    void PrintShapeInfo(ostream& out) {
        out.precision(2);
        out<<"ID = "<<i<<endl;
        out << "Figure centre: (" << center.x << ", " << center.y << ")\n";
        out << "Angle of rotation = " << angle << endl;
        out << "Color (RGB): (" << color.R << ", " << color.G << ", " << color.B << ")\n";
        out << "Scale factor = " << scale << endl;
        out << endl;
    }
    friend ostream& operator<<(ostream& out, Shape& sh)
    {
        sh.PrintShapeInfo(out);
        return out;
    }
    virtual ~Shape(){}
};

class Rectangle : public Shape {
private:
    Point t;
    double a, b;
public:
    Rectangle(double a, double b)
        : a(a), b(b)
    {
        makecoord();
    }
    void makecoord(){
        t = {-a/2, b/2};
        points.push_back(t);
        t = {a/2, b/2};
        points.push_back(t);
        t = {a/2, -b/2};
        points.push_back(t);
        t = {-a/2, -b/2};
        points.push_back(t);
    }
    void Scaling(double k) {
        a*=k;
        b*=k;
        scale*=k;
        points.clear();
        makecoord();
    }
    ~Rectangle(){
        i--;
    }
};

class TRAPEZOID : public Shape{
protected:
    double a, b, c, d, h;
        Point t;
public:
    TRAPEZOID(double a, double b, double c, double d, double h): a(a), b(b), c(c), d(d), h(h){
        makecoord();
    }
    void makecoord(){
        center.x = b/2+(2*a+b)*(c*c-d*d)/(6*(b*b-a*a));
        center.y = h*(b+2*a)/(3*(a+b));
        points.clear();
        t={0, 0};
        points.push_back(t);
        t={sqrt(c*c-h*h), h};
        points.push_back(t);
        t={b-sqrt(d*d-h*h), h};
        points.push_back(t);
        t={b, 0};
        points.push_back(t);
        MoveFigure(center);
    }
    void Scaling(double k){
        c*=k;
        h*=k;
        d*=k;
        b*=k;
        a*=k;
        makecoord();
    }

    ~TRAPEZOID()  {
        i--;
    }

};

class ITRAPEZOID:public TRAPEZOID{
public:
    ITRAPEZOID(double a, double b, double c):TRAPEZOID(a, b, c, c,sqrt(c*c- (b-a)/2*(b-a)/2)){};
    ~ITRAPEZOID(){
        i--;
    }
};

int Shape::i = 0;

int main()
{
    Shape *sh; /* создание указателя базового типа */

     //Testing rectangle
    Rectangle p(4, 3);
    sh = &p;
    cout << p;
    sh->SetColor(1, 1, 1);
    sh->SetTurnAngle(90);
    cout << p;
    sh->Scaling(2);
    cout << p;
    TRAPEZOID t(3, 9, 5, 5, 4);
    sh=&t;
    sh->SetColor(1,1,1);
    //sh->MoveFigure({1,1});
    cout<<t;
    //sh->Scaling(2);
    cout<<t;
    sh->SetTurnAngle(180);
    cout<<t;
    ITRAPEZOID q(3, 9, 5);
    sh=&q;
    cout<<q;
    return 0;
}
