#ifndef OOP_LAB1_POINT_H
#define OOP_LAB1_POINT_H

class Point {

 public:
  int x, y;

  Point();
  Point(int x, int y);

  bool operator!=(Point &other);
  bool operator!=(Point other);
  bool operator==(Point &other);
  bool operator==(Point other);
};

#endif //OOP_LAB1_POINT_H
