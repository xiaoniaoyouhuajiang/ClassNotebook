#ifndef POLYGON_H
#define POLYGON_H

#include <stdexcept>
#include <cmath>
#include <numeric>
#include <vector>

#include "shape.h"
#include "point2d.h"


class Polygon : public Shape
{
public:
    Polygon() : Shape(), vertices() {}
    Polygon(const std::vector<Point2d>& v) : Shape(), vertices(v) {}

    void translate2d(const Point2d& dp);
    void rotate(double angle = 0);
    void scale(double scale = 1);

    Point2d getCenter() const;

protected:
    // Вершины многоугольника
    std::vector<Point2d> vertices;

    void print(std::ostream &os) const override;
};

#endif // POLYGON_H
