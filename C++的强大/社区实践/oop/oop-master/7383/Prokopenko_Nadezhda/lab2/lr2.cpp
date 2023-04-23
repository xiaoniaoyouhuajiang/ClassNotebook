#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;
static int count = 0, angle =  0;

struct Point{
    double x;
    double y;
    Point(): x(0), y(0) {}
    Point(double _x, double _y): x(_x), y(_y) {}
};

struct Color{
    unsigned red;
    unsigned green;
    unsigned blue;
    Color(): red(0), green(0), blue(0) {}
    Color(unsigned r, unsigned g, unsigned b) : red(r), green(g), blue(b) {}
};

class Shape{
protected:
    int id;
    Color color;
public:
    Shape(): id(count), color(){
        count++;
    }
    Shape(int id, Color _color): id(count), color(_color){
        count++;
    }
    int get_id(){
        return id;
    }
    Color get_color(){
        return color;
    }
    void set_color(unsigned r, unsigned g, unsigned b){
        color.red = r;
        color.green = g;
        color.blue = b;
    }
    virtual ~Shape(){
        id--;
    }
    friend ostream &operator<<(ostream &out, Shape *shape);
    virtual void print(ostream &out) = 0;
    virtual double area() = 0;
    virtual void sides_of_shape() = 0;
    virtual void rotate(int _angle) = 0;
    virtual void scale(double coefficient) = 0;
    virtual void move(const Point p) = 0;
};

ostream &operator<<(ostream &out, Shape *shape){
    out << setw(45) << right  << "!Информация о фигуре!" << endl;
    out << "Цвет фигуры: " << "(" << shape->get_color().red << "," << shape->get_color().green << "," << shape->get_color().blue << ")" << endl;
    out << "Id фигуры: " << shape->get_id() << endl;
    out << "Площадь: " << shape->area() << endl;
    shape->print(out);
    out << "____________________________________" << endl;
    return out;
}

class Trapezium : public Shape{
private:
    vector <double> sides;
    vector <Point> points;
    Point center;
public:
    Trapezium(const Point A, const Point B, double x1, double x2, const Color _color) : Shape(count,  _color){
        id++;
        points.clear();
        center =  Point((A.x + B.x + x1 + x2) / 4, (2 * (A.y + B.y)) / 4);
        Point D = Point(x1, A.y);
        Point C = Point(x2, B.y);
        points.push_back(A);
        points.push_back(B);
        points.push_back(C);
        points.push_back(D);
    }
    void sides_of_shape() override{
        sides.clear();
        double a = sqrt(pow((points[0].x - points[1].x), 2.0) + pow((points[0].y - points[1].y), 2.0));
        double b = sqrt(pow((points[1].x - points[2].x), 2.0) + pow((points[1].y - points[2].y), 2.0));
        double c = sqrt(pow((points[2].x - points[3].x), 2.0) + pow((points[2].y - points[3].y), 2.0));
        double d = sqrt(pow((points[3].x - points[0].x), 2.0) + pow((points[3].y - points[0].y), 2.0));
        sides.push_back(a);
        sides.push_back(b);
        sides.push_back(c);
        sides.push_back(d);
    }
    double area()override{
        sides_of_shape();
        double a = sides[1];
        double b = sides[3];
        double h = points[0].y - points[1].y;
        double area = h * (a + b) / 2;
        return abs(area);
    }
    void print(ostream &out) override{
        sides_of_shape();
        out << "Основания: " << sides[1] << ", " << sides[3] << endl;
        out << "Боковые стороны: " << sides[0] << ", " << sides[2] << endl;
        out << "Координаты фигуры: " ;
        for(int i = 0; i < points.size(); i++){
            out << i << ": (" << points[i].x << "; " << points[i].y << "); ";
        }
        out << endl;
        out << "Центр фигуры: " << "(" << center.x << ";" << center.y << ")" << endl;
        out << "Угол: " << angle << endl;
    }
    void move(const Point p) override{
        double dx = p.x - center.x;
        double dy = p.y - center.y;
        center.x += dx;
        center.y += dy;
        for(size_t i = 0; i < points.size(); i++){
            points[i].x += dx;
            points[i].y += dy;
        }
    }
    void rotate(int _angle) override{
        angle= _angle % 360;
        double angle = _angle * M_PI / 180.0;
        for(size_t i = 0; i < points.size(); i++){
            double x = center.x + (points[i].x - center.x) * cos(angle) - (points[i].y - center.y) * sin(angle);
            double y = center.y + (points[i].x - center.x) * sin(angle) + (points[i].y - center.y) * cos(angle);
            points[i].x = x;
            points[i].y = y;
        }
    }
    void scale(double coefficient) override{
        double x;
        double y;
        for(size_t i = 0; i < points.size(); i++){
            x = center.x + (points[i].x - center.x) * coefficient;
            y = center.y + (points[i].y - center.y) * coefficient;
            points[i].x = x;
            points[i].y = y;
        }
    }
    ~Trapezium(){
        sides.clear();
        points.clear();
    }
};

class Rhombus : public Shape{
protected:
  double sides;
  Point center;
private:
  vector <Point> points;
  void move(const Point p) override{
      double dx = p.x - center.x;
      double dy = p.y - center.y;
      center.x += dx;
      center.y += dy;
      for(size_t i = 0; i < points.size(); i++){
          points[i].x += dx;
          points[i].y += dy;
      }
  }
  void rotate(int _angle) override{
      angle= _angle % 360;
      double angle = _angle * M_PI / 180.0;
      for(size_t i = 0; i < points.size(); i++){
          double x = center.x + (points[i].x - center.x) * cos(angle) - (points[i].y - center.y) * sin(angle);
          double y = center.y + (points[i].x - center.x) * sin(angle) + (points[i].y - center.y) * cos(angle);
          points[i].x = x;
          points[i].y = y;
      }
  }
  void scale(double coefficient) override{
      double x;
      double y;
      for(size_t i = 0; i < points.size(); i++){
          x = center.x + (points[i].x - center.x) * coefficient;
          y = center.y + (points[i].y - center.y) * coefficient;
          points[i].x = x;
          points[i].y = y;
      }
  }
  void push_points( double dx, double dy) {
    points.clear();
    Point A = Point(center.x + dx, center.y);
    Point B = Point(center.x, center.y + dy);
    Point C = Point(center.x - dx, center.y);
    Point D = Point(center.x, center.y - dy);
    points.push_back(A);
    points.push_back(B);
    points.push_back(C);
    points.push_back(D);
  }
  double area()override{
      sides_of_shape();
      double dx = points[0].x - points[1].x;
      double dy = points[1].y - points[0].y;
      double d1 = 2 * dx;
      double d2 = 2 * dy;
      double area = d1 * d2 / 2;
      return abs(area);
  }
  void sides_of_shape() override{
      sides = sqrt(pow((points[0].x - points[1].x), 2.0) + pow((points[0].y - points[1].y), 2.0));
  }
public:
    Rhombus(const Point _center, double dx, double dy, const Color _color) : Shape(count, _color){
        id++;
        center = _center;
        push_points( dx, dy);
    }
    void print(ostream &out) override{
        out << "Все стороны фигуры равны: " ;
        out << sides << endl;
        out << "Координаты фигуры: " ;
        for(int i = 0; i < points.size(); i++){
            out << i << ": (" << points[i].x << "; " << points[i].y << "); ";
        }
        out << endl;
        out << "Центр фигуры: " << "(" << center.x << ";" << center.y << ")" << endl;
        out << "Угол: " << angle << endl;
    }
    ~Rhombus(){
        points.clear();
    }
};

class Circle : public Rhombus{
public:
    Circle(const Point center, double r, const Color _color) : Rhombus(Point(center), r, r, _color){
    sides = r;
    }
    void move(const Point p) override{
        center.x = p.x;
        center.y = p.y;
    }
    void rotate(int _angle) override{};
    void scale(double coefficient) override{
        sides *=coefficient;
    }
    double area()override{
        double area = M_PI * pow(sides, 2.0);
        return abs(area);
    }
    void print(ostream &out) override{
        out << "Радиус:  " << sides << endl;
        out << "Центр фигуры: " << "(" << center.x << ";" << center.y << ")" << endl;
    }
    ~Circle(){}
};

int main(){
    setlocale(LC_ALL, "Russian");
    Shape* test[3]={ new Rhombus({1, 1}, 4, 6, {0, 0, 1}), new Trapezium({1, 1}, {2, 5}, 5, 3, {0, 1, 0}), new Circle({5, 7}, 3, {1, 0, 0})};
    for(int i=0; i<3; i++){
      cout<<test[i];
      test[i]->rotate(60);
      cout << test[i];
      test[i]->move({10, 12});
      cout << test[i];
      test[i]->scale(3);
      cout << test[i]<<"____________________________________"<<endl;
    }
    return 0;
}
