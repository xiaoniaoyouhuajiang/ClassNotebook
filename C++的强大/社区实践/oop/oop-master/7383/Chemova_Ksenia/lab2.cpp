#include <iostream>
#include <cmath>
#include <string>

enum Color {red, orange, yellow, green, blue, violet, white, black, grey};

class Shape {
protected:
  int id; //индентефикатор
  double x, y; //координаты центра
  Color color;

public:
  Shape(double x, double y, Color color, int &id)
  : x(x), y(y), color(color), id(id)
  {
    id++;
  };

  virtual ~Shape(){};

  virtual void move(double x, double y) {
    this->x = x;
    this->y = y;
  }

  virtual void rotate(double new_angle) {}

  std::string get_color() const {
    switch(color) {
      case red: return "Red";
      case orange: return "Orange";
      case green: return "Green";
      case blue: return "Blue";
      case violet: return "Violet";
      case white: return "White";
      case black: return "Black";
      case grey: return "Gray";
      default: return "Unknown";
    }
  }

  virtual void scaling (double k){}

  friend std::ostream & operator <<(std::ostream &out, Shape &shape) {
    out << "Object id: " << shape.id << ", shape;" << std::endl;
    out << "The coordinates of the center: (" << shape.x << "; " << shape.y << ");" << std::endl;
    out << "Color: " << shape.get_color() << "." << std::endl;
    return out;
  }

};

class Circle : public Shape {
protected:
  int R;

public:
  Circle(double x, double y, Color color, double R, int &id)
  : Shape(x, y, color, id), R(R)
  {
    id++;
  };

  void scaling(double k) override {
    R *= k;
  }

  virtual void move(double x, double y) {
    this->x = x;
    this->y = y;
  }

  friend std::ostream & operator << (std:: ostream & out, Circle &circle) {
    out << "Object id: " << circle.id << ", circle;" << std::endl;
    out << "The coordinates of the center: (" << circle.x << "; " << circle.y << ");" << std::endl;
    out << "R: " << circle.R << ";" << std::endl;
    out << "Color: " << circle.get_color() << "." << std::endl;
  }
};


class Parallelogram : public Shape {
  double side_a;
  double side_b;
  double sides_angle;
  double x1, x2, x3, x4;
  double y1, y2, y3, y4;
  double rad_sides_angle;

public:
  Parallelogram(double x, double y, Color color, double side_a, double side_b, double sides_angle, int &id)
  : Shape(x, y, color, id), side_a(side_a), side_b(side_b), sides_angle(sides_angle)
  {
    rad_sides_angle = 3.14/180*sides_angle; //переводим углы в радианы
    id++;
    x1 = x - (side_a+side_b*cos(rad_sides_angle))/2;
    y1 = y - side_b*sin(rad_sides_angle)/2;
    x2 = x + (side_a-side_b*cos(rad_sides_angle))/2;
    y2 = y - side_b*sin(rad_sides_angle)/2;
    x3 = x + (side_a+side_b*cos(rad_sides_angle))/2;
    y3 = y + side_b*sin(rad_sides_angle)/2;
    x4 = x - (side_a-side_b*cos(rad_sides_angle))/2;
    y4 = y + side_b*sin(rad_sides_angle)/2;
  };

  virtual ~Parallelogram(){};

  void scaling(double k) override {
    side_a *= k;
    side_b *= k;
  }

  virtual void rotate(double angle) override{
    if (angle >= 360.0) angle = angle - int(angle/360)*360;
    double rad_angle = 3.14/180*angle;
    double x1_n, y1_n, x2_n, y2_n, x3_n, y3_n, x4_n, y4_n;
    x1_n = x1*cos(rad_angle) - y1*sin(rad_angle);
    y1_n = x1*sin(rad_angle) + y1*cos(rad_angle);
    x2_n = x2*cos(rad_angle) - y2*sin(rad_angle);
    y2_n = x2*sin(rad_angle) + y2*cos(rad_angle);
    x3_n = x3*cos(rad_angle) - y3*sin(rad_angle);
    y3_n = x3*sin(rad_angle) + y3*cos(rad_angle);
    x4_n = x4*cos(rad_angle) - y4*sin(rad_angle);
    y4_n = x4*sin(rad_angle) + y4*cos(rad_angle);
    x1 = x1_n;
    y1 = y1_n;
    x2 = x2_n;
    y2 = y2_n;
    x3 = x3_n;
    y3 = y3_n;
    x4 = x4_n;
    y4 = y4_n;
  }

  virtual void move(double x, double y) override{
    if (x >= this->x) {
      this->x1 += (x-this->x);
      this->x2 += (x-this->x);
      this->x3 += (x-this->x);
      this->x4 += (x-this->x);
    }
    else {
      this->x1 -= (this->x-x);
      this->x2 -= (this->x-x);
      this->x3 -= (this->x-x);
      this->x4 -= (this->x-x);
    }
    if (x >= this->y) {
      this->y1 += (y-this->y);
      this->y2 += (y-this->y);
      this->y3 += (y-this->y);
      this->y4 += (y-this->y);
    }
    else {
      this->y1 -= (this->y-y);
      this->y2 -= (this->y-y);
      this->y3 -= (this->y-y);
      this->y4 -= (this->y-y);
    }
    this->x = x;
    this->y = y;
  }

  friend std::ostream & operator << (std::ostream & out, Parallelogram &parall) {
    out << "Object id: " << parall.id << ";" << std::endl;
    out << "Side a: " << parall.side_a << std::endl;
    out << "Side b: " << parall.side_b << std::endl;
    out << "Side's angle: " << parall.sides_angle << std::endl;
    out << "The coordinates of the center: (" << parall.x << "; " << parall.y << ");" << std::endl;
    out << "The coordinates of the vertices:" << std::endl;
    out << "  (x1;y1): (" << parall.x1 << " ; " << parall.y1 << "),"<< std::endl;
    out << "  (x2;y2): (" << parall.x2 << " ; " << parall.y2 << "),"<< std::endl;
    out << "  (x3;y3): (" << parall.x3 << " ; " << parall.y3 << "),"<< std::endl;
    out << "  (x4;y4): (" << parall.x4 << " ; " << parall.y4 << "),"<< std::endl;
    out << "Color: " << parall.get_color() << "." << std::endl;
    return out;
  }

};

class Regular_hexagon : public Circle {
protected:
  double x1, x2, x3, x4, x5, x6;
  double y1, y2, y3, y4, y5, y6;

public:
  Regular_hexagon(double x, double y, Color color, double R, int &id)
  : Circle(x, y, color, R, id)
  {
    id++;
    x1 = x+R;
    y1 = y4 = y;
    x2 = x6 = x+R*cos(3.14/3); //60 degrees
    y2 = y6 = y+R*sin(3.14/3);
    x3 = x5 = x-R*cos(3.14/3);
    y3 = y5 = y-R*sin(3.14/3);
    x4 = x-R;
  };

  virtual ~Regular_hexagon(){};

  virtual void rotate(double angle) override{
    if (angle >= 360.0) angle = angle - int(angle/360)*360;
    double rad_angle = 3.14/180*angle;
    double x1_n, y1_n, x2_n, y2_n, x3_n, y3_n, x4_n, y4_n, x5_n, y5_n, x6_n, y6_n;
    x1_n = x1*cos(rad_angle) - y1*sin(rad_angle);
    y1_n = x1*sin(rad_angle) + y1*cos(rad_angle);
    x2_n = x2*cos(rad_angle) - y2*sin(rad_angle);
    y2_n = x2*sin(rad_angle) + y2*cos(rad_angle);
    x3_n = x3*cos(rad_angle) - y3*sin(rad_angle);
    y3_n = x3*sin(rad_angle) + y3*cos(rad_angle);
    x4_n = x4*cos(rad_angle) - y4*sin(rad_angle);
    y4_n = x4*sin(rad_angle) + y4*cos(rad_angle);
    x5_n = x5*cos(rad_angle) - y5*sin(rad_angle);
    y5_n = x5*sin(rad_angle) + y5*cos(rad_angle);
    x6_n = x6*cos(rad_angle) - y6*sin(rad_angle);
    y6_n = x6*sin(rad_angle) + y6*cos(rad_angle);
    x1 = x1_n;
    y1 = y1_n;
    x2 = x2_n;
    y2 = y2_n;
    x3 = x3_n;
    y3 = y3_n;
    x4 = x4_n;
    y4 = y4_n;
    x5 = x5_n;
    y5 = y5_n;
    x6 = x6_n;
    y6 = y6_n;
  }

  virtual void move(double x, double y) override{

    if (x >= this->x) {
      this->x1 += (x-this->x);
      this->x2 += (x-this->x);
      this->x3 += (x-this->x);
      this->x4 += (x-this->x);
      this->x5 += (x-this->x);
      this->x6 += (x-this->x);
    }
    else {
      this->x1 -= (this->x-x);
      this->x2 -= (this->x-x);
      this->x3 -= (this->x-x);
      this->x4 -= (this->x-x);
      this->x5 -= (this->x-x);
      this->x6 -= (this->x-x);
    }
    if (x >= this->y) {
      this->y1 += (y-this->y);
      this->y2 += (y-this->y);
      this->y3 += (y-this->y);
      this->y4 += (y-this->y);
      this->y5 += (y-this->y);
      this->y6 += (y-this->y);
    }
    else {
      this->y1 -= (this->y-y);
      this->y2 -= (this->y-y);
      this->y3 -= (this->y-y);
      this->y4 -= (this->y-y);
      this->y5 -= (this->y-y);
      this->y6 -= (this->y-y);
    }
    this->x = x;
    this->y = y;
  }

  friend std::ostream & operator << (std::ostream & out, Regular_hexagon &hexagon) {
    out << "Object id: " << hexagon.id << ";" << std::endl;
    out << "R: " << hexagon.R << std::endl;
    out << "The coordinates of the center: (" << hexagon.x << "; " << hexagon.y << ");" << std::endl;
    out << "The coordinates of the vertices:" << std::endl;
    out << "  (x1;y1): (" << hexagon.x1 << " ; " << hexagon.y1 << "),"<< std::endl;
    out << "  (x2;y2): (" << hexagon.x2 << " ; " << hexagon.y2 << "),"<< std::endl;
    out << "  (x3;y3): (" << hexagon.x3 << " ; " << hexagon.y3 << "),"<< std::endl;
    out << "  (x4;y4): (" << hexagon.x4 << " ; " << hexagon.y4 << "),"<< std::endl;
    out << "  (x5;y5): (" << hexagon.x5 << " ; " << hexagon.y5 << "),"<< std::endl;
    out << "  (x6;y6): (" << hexagon.x6 << " ; " << hexagon.y6 << "),"<< std::endl;
    out << "Color: " << hexagon.get_color() << "." << std::endl;
    return out;
  }
};

int main() {
  int id = 0;
  Shape shape(5, 7, blue, id);
  Circle circle(1, 1, red, 7, id);
  Parallelogram parall (8, 9, black, 2, 4, 90, id);
  Regular_hexagon hex (0, 0, white, 5, id);
  std::cout << "Shape" << std::endl << shape;
  std::cout << std::endl << "Cicrle" << std::endl << circle;
  std::cout << std::endl << "Parallelogram" << std::endl << parall;
  parall.move(1, 1);
  std::cout << std::endl << "Parallelogram" << std::endl << parall;
  parall.scaling(7);
  std::cout << std::endl << "Parallelogram" << std::endl << parall;
  std::cout << std::endl << "Regular_hexagon" << std::endl << hex;
  hex.rotate(60);
  std::cout << std::endl << "Regular_hexagon" << std::endl << hex;
  return 0;
}
