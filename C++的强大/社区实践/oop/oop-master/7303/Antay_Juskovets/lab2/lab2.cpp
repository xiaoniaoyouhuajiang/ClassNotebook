#include <iostream>
#include <vector>
#include <cmath>

class Point {
public:
  Point(double x = 0, double y = 0): x(x), y(y) {}

  void to(double x, double y) {
    this->x = x;
    this->y = y;
  }

  void move(double x, double y) {
    this->x += x;
    this->y += y;
  }

  double x = 0;
  double y = 0;
};

std::ostream& operator<<(std::ostream& out, Point& p) {
  return out << "{x: " << p.x << ", y: " << p.y << "}";
}

class Shape {
public:
   virtual void move(double x, double y) = 0;
   virtual void rotate(int angle) = 0;
   virtual void scale(double k) = 0;
   void setColor(rgb color) {
     this->color = color;
   }
   friend std::ostream& operator<<(std::ostream& out, Shape& shape);

protected:
  struct rgb {
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
  } color;

  int angle = 0;
};

class Circle: public Shape {
public:
  Circle(Point c = Point(), double r = 0): center(c), r(r) {}

  void move(double x, double y) {
    center.move(x, y);
  }

  void rotate(int angle) {
    this->angle = (this->angle + angle) % 360;
  }

  void scale(double k) {
    r *= k;
  }

  friend std::ostream& operator<<(std::ostream& out, Circle& circle);

private:
  double r;
  Point center;
};

std::ostream& operator<<(std::ostream& out, Circle& c) {
  return out << "{c: " << c.center << ", r: " << c.r << "}";
}

class Parallelogram: public Shape {
public:
  Parallelogram(Point left_top, Point right_bottom, size_t width):
      left_top(left_top), width(width),
      right_bottom(right_bottom) {
    right_top = Point(left_top.x + width, left_top.y);
    left_bottom = Point(right_bottom.x - width, right_bottom.y);
    height = left_top.y - right_bottom.y;

    center = Point((left_top.x + right_bottom.x)/2, (left_top.y + right_bottom.y)/2);
  }

  void move(double x, double y) {
    Point old_center = center;
    center.to(x, y);

    left_top.move(x - old_center.x, y - old_center.y);
    right_top.move(x - old_center.x, y - old_center.y);
    right_bottom.move(x - old_center.x, y - old_center.y);
    left_bottom.move(x - old_center.x, y - old_center.y);
  }

  void rotate(int angle) {
    Point old_coord = center;
    move(0, 0);

    this->angle = (this->angle + angle) % 360;
    std::vector<Point> points = {left_top, right_top, right_bottom, left_bottom};

		double angleRad = angle*M_PI / 180;
		for (int i = 0; i < points.size(); i++){
			double newX = points[i].x*cos(angleRad) - points[i].y*sin(angleRad);
			double newY = points[i].x*sin(angleRad) + points[i].y*cos(angleRad);
			points[i].x = newX;
			points[i].y = newY;
		}

    left_top = points[0];
    right_top = points[1];
    right_bottom = points[2];
    left_bottom = points[3];

    move(old_coord.x, old_coord.y);
  }

  void scale(double k) {
    int old_angle = angle;
    Point old_center = center;
    rotate(-angle);
    move(0, 0);

    width *= k;
    height *= k;

    int dx = abs(left_top.x - left_bottom.x)/2 * k;
    if (abs(right_bottom.x - left_top.x)*k > width) {
      left_top.to(center.x-width/2 - dx, center.y+height/2);
      right_top.to(left_top.x + width, left_top.y);
      right_bottom.to(right_top.x + dx*2, left_top.y - height);
      left_bottom.to(left_top.x + dx*2, left_top.y - height);
    }
    else {
      left_top.to(center.x-width/2 + dx, center.y+height/2);
      right_top.to(left_top.x + width, left_top.y);
      right_bottom.to(right_top.x - dx*2, left_top.y - height);
      left_bottom.to(left_top.x - dx*2, left_top.y - height);
    }

    move(old_center.x, old_center.y);
    rotate(angle);
  }

  friend std::ostream& operator<<(std::ostream& out, Parallelogram& p);

private:
  Point left_top;
  Point right_top;
  Point right_bottom;
  Point left_bottom;
  Point center;
  size_t width;
  size_t height;
};

std::ostream& operator<<(std::ostream& out, Parallelogram& p) {
  return out << p.left_top << p.right_top << std::endl << p.left_bottom << p.right_bottom;
}

class RegularHexagon: public Shape {
public:
  RegularHexagon(Point c, double a): center(c), a(a) {}

  // clockwise
  std::vector<Point> get_points() {
    int old_angle = angle;
    rotate(-angle);

    std::vector<Point> points(6);
    double m = sin(M_PI/3)*a;

    points[0] = Point(center.x - a, center.y);
    points[1] = Point(center.x - a/2, center.y+m);
    points[2] = Point(center.x + a/2, center.y+m);
    points[3] = Point(center.x + a, center.y);
    points[4] = Point(center.x + a/2, center.y-m);
    points[5] = Point(center.x - a/2, center.y-m);

    // rotate on old_angle
    double angleRad = old_angle*M_PI / 180;
		for (int i = 0; i < points.size(); i++){
			double newX = points[i].x*cos(angleRad) - points[i].y*sin(angleRad);
			double newY = points[i].x*sin(angleRad) + points[i].y*cos(angleRad);
			points[i].x = newX;
			points[i].y = newY;
		}

    rotate(old_angle);

    return points;
  }

  void move(double x, double y) {
    center.x = x;
    center.y = y;
  }

  void scale(double k) {
    a *= k;
  }

  void rotate(int angle) {
    this->angle = (this->angle + angle) % 360;
  }

  friend std::ostream& operator<<(std::ostream& out, RegularHexagon& h);

private:

  Point center;
  double a;
};

std::ostream& operator<<(std::ostream& out, RegularHexagon& h) {
  std::vector<Point> points = h.get_points();
  return out << points[0] << points[1] << points[2] << std::endl
             << points[3] << points[4] << points[5];
}

int main() {
  Parallelogram p({-2, 2}, {2, -2}, 6);
  std::cout << p << std::endl;

  p.scale(2);
  std::cout << p << std::endl;

  RegularHexagon h({0, 0}, 2);
  std::cout << h << std::endl;

  h.move(2, 2);
  std::cout << h << std::endl;
}
