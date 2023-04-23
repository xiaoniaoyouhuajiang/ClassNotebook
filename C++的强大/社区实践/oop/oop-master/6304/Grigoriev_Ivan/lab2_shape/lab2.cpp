#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>
#include <exception>

using namespace std;

static const double Pi = 3.14159265358979323846264338327950288419717;

struct Dot
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
    int angle;
    RGB color;
    Dot centre;
    double scale_factor;
public:
    Shape(double _x, double _y)
    {
        centre.x = _x;
        centre.y = _y;
        scale_factor = 1;
        angle = 0;
        color = {0,0,0};
    }

    virtual ~Shape() {}

    virtual void MoveFigure(double other_x, double other_y) = 0;
    virtual void SetTurnAngle(int other_angle) = 0;
    virtual void Scaling(double k) = 0;

    void SetColor(int new_R, int new_G, int new_B) {
        color = {new_R, new_G, new_B};
    }

    void PrintShapeInfo(ostream& out) {
        out.precision(2);
        out <<"Figure centre: (" <<centre.x <<", " <<centre.y <<")\n";
        out <<"Angle of rotation = " <<angle <<endl;
        out <<"Color (RGB): (" <<color.R <<", " <<color.G <<", " <<color.B <<")\n";
        out <<"Scale factor = " <<scale_factor <<endl;
        out <<endl;
    }
    friend ostream& operator<<(ostream& out, Shape& sh)
    {
        sh.PrintShapeInfo(out);
        return out;
    }
};

class paralelogram : public Shape {
protected:
    double l1, l2;
    int alpha;
    Dot A, B, C, D;
public:
    paralelogram(double _x, double _y, double _l1, double _l2, int _alpha)
        : Shape(_x, _y), l1(_l1), l2(_l2), alpha(_alpha)
    {
        identify_dots();
    }

    void identify_dots() {
        double rad = alpha * Pi / 180;
        double h = l1 * sin(rad);

        A.x = centre.x - l2/2 - h/(2*tan(rad));
        A.y = centre.y - h/2;

        B.x = centre.x - l2/2 + h/(2*tan(rad));
        B.y = centre.y + h/2;

        C.x = centre.x + l2/2 + h/(2*tan(rad));
        C.y = B.y;

        D.x = centre.x + l2/2 - h/(2*tan(rad));
        D.y = A.y;
    }

    void MoveFigure(double new_x, double new_y) {
        centre.x = new_x;
        centre.y = new_y;
        identify_dots();
    }

    void SetTurnAngle(int new_angle) {
        angle += new_angle;
        angle %= 360;
        double rad = angle * Pi / 180;

        vector<Dot> dots;
        dots.push_back(A); dots.push_back(B);
        dots.push_back(C); dots.push_back(D);

        for(auto& dot : dots) {
            Dot tmp_dot = dot;
            dot.x = tmp_dot.x * cos(rad) - tmp_dot.y * sin(rad);
            dot.y = tmp_dot.y * cos(rad) + tmp_dot.y * sin(rad);
        }

        A = dots[0]; C = dots[2];
        B = dots[1]; D = dots[3];
    }

    void Scaling(double k) {
        scale_factor *= k;
        centre.x *= k;
        centre.y *= k;

        A.x *= k; B.x *= k;
        A.y *= k; B.y *= k;

        C.x *= k; D.x *= k;
        C.y *= k; D.y *= k;
    }

    friend ostream& operator<<(ostream& out, paralelogram& paral)
    {
        out <<"PARALELOGRAM" <<endl;
        paral.PrintShapeInfo(out);
        out <<"Sides length: l1 = " <<paral.l1 <<" l2 = " <<paral.l2 <<endl;
        out <<"Angle between l1 and l2 = " <<paral.alpha <<endl;
        out <<"DOTS COORDINATES:\n";
        out <<"Dot A: (" <<paral.A.x <<", " <<paral.A.y <<")\n";
        out <<"Dot B: (" <<paral.B.x <<", " <<paral.B.y <<")\n";
        out <<"Dot C: (" <<paral.C.x <<", " <<paral.C.y <<")\n";
        out <<"Dot D: (" <<paral.D.x <<", " <<paral.D.y <<")\n";
        out <<"-----------------------------------------------";
        out <<endl;
        return out;
    }
};

class ellipse : public Shape {
protected:
    double big_semiaxis;
    double small_semiaxis;
    double FOCUS;
    Dot A, B, C, D;
public:
    ellipse(double _x, double _y, double R1, double R2)
        : Shape(_x, _y), big_semiaxis(max(R1,R2)), small_semiaxis(min(R1,R2))
    {
        FOCUS = 2 * sqrt(abs(big_semiaxis*big_semiaxis - small_semiaxis*small_semiaxis));
        identify_dots();
    }

    void identify_dots() {
        A.x = centre.x;
        A.y = centre.y - small_semiaxis;

        B.x = centre.x - big_semiaxis;
        B.y = centre.y;

        C.x = centre.x;
        C.y = centre.y + small_semiaxis;

        D.x = centre.x + big_semiaxis;
        D.y = centre.y;
    }

    virtual void MoveFigure(double new_x, double new_y) {
        centre.x = new_x;
        centre.y = new_y;
        identify_dots();
    }

    virtual void SetTurnAngle(int new_angle) {
        angle += new_angle;
        angle %= 360;
        double rad = angle * Pi / 180;

        vector<Dot> dots;
        dots.push_back(A); dots.push_back(B);
        dots.push_back(C); dots.push_back(D);

        for(auto& dot : dots) {
            Dot tmp_dot = dot;
            dot.x = tmp_dot.x * cos(rad) - tmp_dot.y * sin(rad);
            dot.y = tmp_dot.y * cos(rad) + tmp_dot.y * sin(rad);
        }

        A = dots[0]; C = dots[2];
        B = dots[1]; D = dots[3];
    }

    virtual void Scaling(double k) {
        scale_factor *= k;
        centre.x *= k;
        centre.y *= k;

        A.x *= k; B.x *= k;
        A.y *= k; B.y *= k;

        C.x *= k; D.x *= k;
        C.y *= k; D.y *= k;
        FOCUS *= k;
    }

    void PrintEllipseInfo(ostream& out) {
        out <<"ELLIPSE" <<endl;
        PrintShapeInfo(out);
        out <<"Big semiaxis length = " <<big_semiaxis <<endl;
        out <<"Small semiaxis length = " <<small_semiaxis <<endl;
        out <<"Focus distance = " <<FOCUS <<endl;
        out <<"DOTS COORDINATES:\n";
        out <<"Dot A: (" <<A.x <<", " <<A.y <<")\n";
        out <<"Dot B: (" <<B.x <<", " <<B.y <<")\n";
        out <<"Dot C: (" <<C.x <<", " <<C.y <<")\n";
        out <<"Dot D: (" <<D.x <<", " <<D.y <<")\n";
    }
    friend ostream& operator<<(ostream& out, ellipse& ellipse)
    {
        ellipse.PrintEllipseInfo(out);
        out <<"-----------------------------------------------";
        out <<endl;
        return out;
    }
};

class ellipseSECTOR : public ellipse {
protected:
    Dot point1, point2;
    double edge1, edge2;
public:
    ellipseSECTOR(double _x, double _y, double R1, double R2, Dot _point1, Dot _point2)
        : ellipse(_x, _y, R1, R2),
        point1(_point1), point2(_point2)
    {
        double x1 = point1.x - centre.x;
        double y1 = point1.y - centre.y;
        double x2 = point2.x - centre.x;
        double y2 = point2.y - centre.y;
        double _edge1 = sqrt(x1*x1 + y1*y1);
        double _edge2 = sqrt(x2*x2 + y2*y2);
        if(!((_edge1 >= small_semiaxis && _edge1 <= big_semiaxis)
            && (_edge2 >= small_semiaxis && _edge2 <= big_semiaxis)))
        {
            throw runtime_error("this is not the point of an ellipse");
        }
        edge1 = _edge1;
        edge2 = _edge2;
    }

    void MoveFigure(double new_x, double new_y) {
        point1.x += centre.x - new_x; point1.y += centre.y - new_y;
        point2.x += centre.x - new_x; point2.y += centre.y - new_y;
        centre.x = new_x;
        centre.y = new_y;
    }

    void SetTurnAngle(int new_angle) {
        angle += new_angle;
        angle %= 360;
        double rad = angle * Pi / 180;
        Dot tmp_dot1 = point1;
        Dot tmp_dot2 = point2;
        point1.x = tmp_dot1.x * cos(rad) - tmp_dot1.y * sin(rad);
        point1.y = tmp_dot1.y * cos(rad) + tmp_dot1.y * sin(rad);
        point2.x = tmp_dot2.x * cos(rad) - tmp_dot2.y * sin(rad);
        point2.y = tmp_dot2.y * cos(rad) + tmp_dot2.y * sin(rad);
    }

    void Scaling(double k) {
        scale_factor *= k;
        centre.x *= k; centre.y *= k;
        point1.x *= k; point1.y *= k;
        point2.x *= k; point2.y *= k;
        edge1 *= k; edge2 *= k;
    }

    friend ostream& operator<<(ostream& out, ellipseSECTOR& ellipseSECT)
    {
        out <<"ELLIPSE(SECTOR)" <<endl;
        ellipseSECT.PrintShapeInfo(out);
        out <<"Edge1 lengtth = " <<ellipseSECT.edge1 <<endl;
        out <<"Edge2 lengtth = " <<ellipseSECT.edge2 <<endl;
        out <<"DOTS COORDINATES:\n";
        out <<"Dot point1: (" <<ellipseSECT.point1.x <<", " <<ellipseSECT.point1.y <<")\n";
        out <<"Dot point2: (" <<ellipseSECT.point2.x <<", " <<ellipseSECT.point2.y <<")\n";
        out <<"-----------------------------------------------";
        out <<endl;
        return out;
    }
};


int main ( )
{
    Shape *sh; /* создание указателя базового типа */

    //Testing paral
    paralelogram p(0, 0, 4, 3, 30);
    sh = &p;
    cout << p;
    sh -> MoveFigure(1,1);
    cout << p;
    sh -> MoveFigure(0,0);
    sh -> SetColor(1,1,1);
    sh -> SetTurnAngle(180);
    cout << p;
    sh -> Scaling(2);
    cout << p;

    //Testing ellipse
    ellipse el(0,0,2,4);
    sh = &el;
    cout << el;
    sh -> MoveFigure(1,1);
    cout << el;
    sh -> MoveFigure(0,0);
    sh -> SetColor(3,2,2);
    sh -> SetTurnAngle(60);
    cout << el;
    sh -> Scaling(3);
    cout << el;

    //Testing ellipse(sect)
    ellipseSECTOR el_s(0,0,2,4,{1,2},{0,3});
    sh = &el_s;
    cout << el_s;
    sh -> MoveFigure(1,1);
    cout << el_s;
    sh -> MoveFigure(0,0);
    sh -> SetColor(3,2,2);
    sh -> SetTurnAngle(60);
    cout << el_s;
    sh -> Scaling(2.5);
    cout << el_s;

    ellipseSECTOR el_s2(0,0,2,4,{5,10},{10,5});

return 0;
}