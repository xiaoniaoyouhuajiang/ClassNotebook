#ifndef FIGURE
#define FIGURE
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

//Color ----------------------------------------------------------------
class Color {
 private:
  unsigned long color;
 public:

  Color(unsigned long n = 0)
      : color(n) {
  }
 
  void set(unsigned long newcolor) {
    color = newcolor;
  }

  unsigned long get() {
    return color;
  }
  
  friend std::ostream& operator<<(std::ostream& os, const Color& tr);
};


//Point ----------------------------------------------------------------
class Point {
 private:
  double X, Y;

 public:
  Point(double Xn = 0, double Yn = 0)
      : X(Xn)
      , Y(Yn)
  {
  }

  void scale(double coef) {
    X *= coef;
    Y *= coef;
  }

  void rotate(double angle) {
    double oldX = X; 
    X = X*cos(angle) - Y*sin(angle);
    Y = oldX*sin(angle) + Y*cos(angle);
  }

    
  Point operator+(Point const& t) const;
  
  double getX() const{
    return X;
  }

  double getY() const{
    return Y;
  }

  void setX(double a) {
    X = a;
  }

  void setY(double a) {
    Y = a;
  }

  friend std::ostream& operator<<(std::ostream& os, const Point& tr);
};



//Shape ----------------------------------------------------------------
class Shape {
 public:
  Shape()
      : color(Color(0))
      , id(++nextid) {
  }

  virtual ~Shape() {}
  void move(Point const& newcord) {
    cord = newcord;
  }

  int ID() const {
    return id;
  }
  
  void rotate(double angle);

  void scale(double coef);

  Color getColor() {
    return color;
  }
  
  bool pointLocal(Point const& a);

  bool isInsideOfAnother(const Shape& other);
  
  void setColor(Color const& newcolour) {
    color = newcolour;
  }
  
  virtual std::ostream& print(std::ostream& os) const = 0;
  friend std::ostream& operator<<(std::ostream& os, const Shape& tr) {
    return tr.print(os);
  }

 protected:
  std::vector<Point> point;
  Point cord;
  Color color;
  const unsigned int id;
  static unsigned int nextid;


  double intersect(Point const& A, Point const& B, Point const& C, Point const& D);
  double rotateLineInfo(Point const& point0, Point const& point1, Point const& c);
};



//Triangle ----------------------------------------------------------------
class Triangle: public Shape {
 public:
  Triangle(double leng, Point const& topp) { 
    cord = Point(0, 0);
    point.push_back(Point(leng, 0));
    point.push_back(topp);
  }

  std::ostream& print(std::ostream& os) const;
};

//Rhombus ----------------------------------------------------------------
class Rhombus: public Shape {
 public:
  Rhombus(double leng, double angle);

  std::ostream& print(std::ostream& os) const;
};



//Parallelogram ----------------------------------------------------------------
class Parallelogram: public Shape {
 public:
  Parallelogram(double width, double height); 

  std::ostream& print(std::ostream& os) const;
};


#endif
