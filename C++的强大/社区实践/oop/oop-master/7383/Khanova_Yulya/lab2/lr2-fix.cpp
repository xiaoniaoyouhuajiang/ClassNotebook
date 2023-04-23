#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>

using namespace std;

static int count = 0;

struct Point{
    double x;
    double y;
    Point():x(0),y(0){}
    Point(double _x, double _y):x(_x), y(_y){}
};

struct Color{
    unsigned red;
    unsigned green;
    unsigned blue;
    Color(): red(0), green(0),blue(0){}
    Color(unsigned r, unsigned g, unsigned b) : red(r), green(g), blue(b){}
};

class Shape{
public:

  Shape():id(count),angle(0), color(), center(){
      count++;
  }

  Shape(int id, double _angle, Color _color, Point _point):id(count), angle(_angle), color(_color), center(_point){
      count++;
  }

  double get_angle(){
      return angle;
  }

  Point get_cntr(){
      return center;
  }

  int get_id(){
      return id;
  }

  Color get_color(){
      return color;
  }

  void set_color(unsigned r,unsigned g,unsigned b){
      color.red = r;
      color.green = g;
      color.blue = b;
  }

  void set_cntr(double absc, double ord){
      center.x = absc;
      center.y = ord;
  }

  virtual ~Shape(){
      id--;
  }

virtual void move(const Point p) = 0;
virtual void rotate(int _angle) = 0;
virtual void scale(double k) = 0;
virtual void print(ostream &out) = 0;
virtual void sides_of_shape() = 0;
virtual double area() = 0;
friend ostream& operator << (ostream& out, Shape* shape);

protected:
  double angle;
  int id;
  Color color;
  Point center;

};

ostream& operator << (ostream& out, Shape* shape){

    out << "!Information!"<<endl;
    out << "Center: " <<"("<< shape->get_cntr().x << ";" << shape->get_cntr().y << ")" << endl;
    out << "Colour (RGB): " <<"("<< shape->get_color().red << ","<< shape->get_color().green << ","<< shape->get_color().blue << ")" << endl;
    out << "Angle: " << shape->get_angle() << endl;
    out << "Id: " << shape->get_id() << endl;
    out << "Area: " << shape->area() << endl;
    shape->print(out);
    out << "---------------------------------------------------------------------"<<endl;
    return out;
}

class Triangle : public Shape{
protected:
  Point A;
  Point B;
  Point C;
  vector <double> sides;
public:
    Triangle(const Point _A, const Point _B, const Point _C, const Color _color) : Shape(count,0 ,_color, Point((_A.x+_B.x+_C.x)/3, (_A.y+_B.y+_C.y)/3)){
      id++;
      Point A = _A;
      Point B = _B;
      Point C = _C;
      sides_of_shape();
    }

    void sides_of_shape() override{
      sides.clear();
      double a = sqrt(pow((A.x - B.x) , 2.0) + pow((A.y - B.y) , 2.0));
      double b = sqrt(pow((B.x - C.x) , 2.0) + pow((B.y - C.y) , 2.0));
      double c = sqrt(pow((C.x - A.x) , 2.0) + pow((C.y - A.y) , 2.0));
      sides.push_back(a);
      sides.push_back(b);
      sides.push_back(c);
    }

    double area()override{
      double AC = sides[0];
      double BC = sides[1];
      double AB = sides[2];
      double p = AC+BC+AB/2;
      double area = sqrt(p*(p-AC)*(p-BC)*(p-AB));
      return area;
    }


    void scale(double k)override{
      Point start;
      start.x = center.x;
      start.y = center.y;
        A.x *= k;
        A.y *= k;
        B.x *= k;
        B.y *= k;
        C.x *= k;
        C.y *= k;
      center.x = (A.x+B.x+C.x)/3;
      center.y = (A.y+B.y+C.y)/3;
      move(start);
    }

    void rotate(int _angle)override
    {
        angle += _angle;
        _angle %= 360;
        double rad = _angle*M_PI/180;
        double x, y;
            x = A.x;
            y = A.y;
            A.x =(x - center.x) * cos(rad) - (y - center.y) * sin(rad) + center.x;
            A.y = (x - center.x) * sin(rad) + (y - center.y) * cos(rad) + center.y;
            x = B.x;
            y = B.y;
            B.x =(x - center.x) * cos(rad) - (y - center.y) * sin(rad) + center.x;
            B.y = (x - center.x) * sin(rad) + (y - center.y) * cos(rad) + center.y;
            x = C.x;
            y = C.y;
            C.x =(x - center.x) * cos(rad) - (y - center.y) * sin(rad) + center.x;
            C.y = (x - center.x) * sin(rad) + (y - center.y) * cos(rad) + center.y;

    }

    void move(const Point p)override{
        double dx = p.x - center.x;
        double dy = p.y - center.y;
        center.x += dx;
        center.y += dy;
            A.x += dx;
            A.y += dy;
            B.x += dx;
            B.y += dy;
            C.x += dx;
            C.y += dy;
    }

    void print(ostream &out) override{
      out << "Sides: " ;
      for(int i = 0; i < sides.size(); i++){
        out << i << ": " << sides[i] << ", ";
      }
      out << endl;
      out << "Points: " ;
      out << 1 << ": (" << A.x << "; " << A.y << "), " << 2 << ": (" << B.x << "; " << B.y << "), " << 3 << ": (" << C.x << "; " << C.y << "), ";
      out << endl;
    }

    ~Triangle(){
      sides.clear();
    }
};

class Trapezium : public Triangle{
private:
  Point D;
public:
  Trapezium(double x, const Color _color) : Triangle(Point(A), Point(B), Point(C), _color){
    id++;
    Point D = Point(B.x+x, B.y);
    Point C = Point(C.x+x, A.y);
    sides_of_shape();
  }

  void sides_of_shape() override{
    sides.clear();
    double a = sqrt(pow((A.x - B.x) , 2.0) + pow((A.y - B.y) , 2.0));
    double b = sqrt(pow((B.x - D.x) , 2.0) + pow((B.y - D.y) , 2.0));
    double c = sqrt(pow((D.x - C.x) , 2.0) + pow((D.y - C.y) , 2.0));
    double d = sqrt(pow((C.x - A.x) , 2.0) + pow((C.y - A.y) , 2.0));
    sides.push_back(a);
    sides.push_back(b);
    sides.push_back(c);
    sides.push_back(d);
  }

  double area()override{
    double a = sides[1];
    double b = sides[3];
    double h = abs(A.y-B.y);
    double area = h*(a+b)/2;
    return area;
  }

  void print(ostream &out) override{
    out << "Sides: " << endl;
    out << "Bases: " << sides[1] << ", " << sides[3] << endl;
    out << "Lateral: " << sides[0] << ", " << sides[2] << endl;
    out << "Points: " ;
    out << 1 << ": (" << A.x << "; " << A.y << "), " << 2 << ": (" << B.x << "; " << B.y << "), " ;
    out << 3 << ": (" << C.x << "; " << C.y << "), " << 4 << ": (" << D.x << "; " << D.y << "), " ;
    out << endl;
  }

  void scale(double k)override{
    Point start;
    start.x = center.x;
    start.y = center.y;
      A.x *= k;
      A.y *= k;
      B.x *= k;
      B.y *= k;
      C.x *= k;
      C.y *= k;
      D.x *= k;
      D.y *= k;
    center.x = (A.x+B.x+C.x+D.x)/4;
    center.y = (A.y+B.y+C.y+D.y)/4;
    move(start);
  }

  void rotate(int _angle)override
  {
      angle += _angle;
      _angle %= 360;
      double rad = _angle*M_PI/180;
      double x, y;
          x = A.x;
          y = A.y;
          A.x =(x - center.x) * cos(rad) - (y - center.y) * sin(rad) + center.x;
          A.y = (x - center.x) * sin(rad) + (y - center.y) * cos(rad) + center.y;
          x = B.x;
          y = B.y;
          B.x =(x - center.x) * cos(rad) - (y - center.y) * sin(rad) + center.x;
          B.y = (x - center.x) * sin(rad) + (y - center.y) * cos(rad) + center.y;
          x = C.x;
          y = C.y;
          C.x =(x - center.x) * cos(rad) - (y - center.y) * sin(rad) + center.x;
          C.y = (x - center.x) * sin(rad) + (y - center.y) * cos(rad) + center.y;
          x = D.x;
          y = D.y;
          D.x =(x - center.x) * cos(rad) - (y - center.y) * sin(rad) + center.x;
          D.y = (x - center.x) * sin(rad) + (y - center.y) * cos(rad) + center.y;
  }

  void move(const Point p)override{
      double dx = p.x - center.x;
      double dy = p.y - center.y;
      center.x += dx;
      center.y += dy;
          A.x += dx;
          A.y += dy;
          B.x += dx;
          B.y += dy;
          C.x += dx;
          C.y += dy;
          D.x += dx;
          D.y += dy;
  }

  ~Trapezium(){
    sides.clear();
  }
};

class Eq_pentagon : public Shape{
private:
  vector <Point> points;
  double sides;
public:
    Eq_pentagon(const Point cntr, double r, const Color _color) : Shape(count,0 ,_color, Point(cntr)){
      id++;
      Point A = Point(cntr.x, cntr.y+r);
      int counter = 0;
      Point tmp;
      tmp.x = A.x;
      tmp.y = A.y;
      while (counter < 4){
        points.push_back(rotate_point(tmp));
        counter++;
      }
      sides_of_shape();
    }

    Point rotate_point(Point& P)
    {
        double rad = 72*M_PI/180;
        double x, y;
        x = P.x;
        y = P.y;
        P.x =(x - center.x) * cos(rad) - (y - center.y) * sin(rad) + center.x;
        P.y = (x - center.x) * sin(rad) - (y - center.y) * cos(rad) + center.y;
        return P;
    }

    void sides_of_shape()override{
    double n = sqrt(pow((points[0].x - points[1].x) , 2.0) + pow((points[0].y - points[1].y) , 2.0));
    sides = n;
    }

    double area()override{
      double area = 5*pow(sides, 2.0)/(tan(M_PI/5)*4);
      return abs(area);
    }

    void print(ostream &out) override{
      int i = 0;
      out << "Sides: " << sides << endl;
      out << "Points: " ;
      for(int i = 0; i < points.size(); i++){
        out << i << ": (" << points[i].x << "; " << points[i].y << "), ";
      }
      out << endl;

    }

    void scale(double k)override{
      Point start;
      start.x = center.x;
      start.y = center.y;
      double X =0, Y = 0;
      for(auto& pnt : points){
        pnt.x *= k;
        X += pnt.x;
        pnt.y *= k;
        Y += pnt.y;
      }
      center.x = X/5;
      center.y = Y/5;
      move(start);
    }

    void rotate(int _angle)override
    {
        angle += _angle;
        _angle %= 360;
        double rad = _angle*M_PI/180;
        double x, y;
        for(auto& pnt : points){
            x = pnt.x;
            y = pnt.y;
            pnt.x =(x - center.x) * cos(rad) - (y - center.y) * sin(rad) + center.x;
            pnt.y = (x - center.x) * sin(rad) + (y - center.y) * cos(rad) + center.y;
        }
    }

    void move(const Point p){
        double dx = p.x - center.x;
        double dy = p.y - center.y;
        center.x += dx;
        center.y += dy;
        for(auto& pnt : points){
            pnt.x += dx;
            pnt.y += dy;
        }
    }

    ~Eq_pentagon(){
      points.clear();
    }
};

int main(){
  Shape* test1 = new Triangle ({0,0}, {2,1}, {1,3}, {0, 0, 1} );
	cout << test1;
	test1->rotate(30);
	cout << test1;
	Shape* test2 = new Trapezium (5, {0, 1, 0});
	cout << test2;
	test2->scale(5);
	cout << test2;
  Shape* test3 = new Eq_pentagon ({5,7}, 5, {1, 0, 0});
	cout << test3;
	test3->move({10, 12});
	cout << test3;
  return 0;
}
