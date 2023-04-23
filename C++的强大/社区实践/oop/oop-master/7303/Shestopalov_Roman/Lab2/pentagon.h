#ifndef PENTAGON_H
#define PENTAGON_H
#include "shape.h"

class RegularPentagon: public Shape {
public:
  RegularPentagon(Point c, double a): center(c), a(a) {
  this->id = id++;
  }

  std::vector<Point> get_points() {
    int old_angle = angle;
    rotate(-angle);

    std::vector<Point> points(5);
    double dy18 = sin(M_PI/10)*a;//18 градусов
    double dx18 = cos(M_PI/10)*a;
    double dy36 = sin(M_PI/5)*a;//36 градусов
    double dx36 = cos(M_PI/5)*a;
    //по часовой
    points[0] = Point(center.x, center.y + a);
    points[1] = Point(center.x + dx18, center.y + dy18);
    points[2] = Point(center.x + dy36, center.y - dx36);
    points[3] = Point(center.x - dy36, center.y - dx36);
    points[4] = Point(center.x - dx18, center.y + dy18);

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

  friend std::ostream& operator<<(std::ostream& out, RegularPentagon& h);

private:

  Point center;
  double a;
};

std::ostream& operator<<(std::ostream& out, RegularPentagon& p) {
  std::vector<Point> points = p.get_points();
  return out <<"Id = "<< p.id << points[0] << points[1] << points[2] << std::endl
             << points[3] << points[4];
}
#endif // PENTAGON_H
