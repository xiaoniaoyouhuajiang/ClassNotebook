#include "polygon.h"

Point2d Polygon::getCenter() const
{
    Point2d center = std::accumulate(vertices.begin(), vertices.end(), Point2d());
    center.scale(1 / (double) vertices.size());

    return center;
}


void Polygon::translate2d(const Point2d &dp)
{
    for (auto& p : vertices)
        p.translate2d(dp);
}


void Polygon::rotate(double angle)
{
    Point2d center = getCenter();

    // переносим в начало координат
    translate2d(-center);

    // поворачиваем
    for (auto& p : vertices)
        p.rotate(angle);

    // возвращаем назад
    translate2d(center);
}


void Polygon::scale(double scale)
{
    Point2d center = getCenter();

    // переносим в начало координат
    translate2d(-center);

    // масштабируем
    for (auto& p : vertices)
        p.scale(scale);

    // возвращаем
    translate2d(center);
}


void Polygon::print(std::ostream& os) const
{
    os << "Id: " << m_id << std::endl;
    os << "Color: { r=" << (int) m_color.r << ", g=" << (int) m_color.g << ", b=" << (int) m_color.b << " }" << std::endl;

    os << "Area: " << area() << std::endl;
    os << "Perimeter: " << perimeter() << std::endl;

    os << "Vertices: " << std::endl;

    for (auto it = vertices.begin(); it != vertices.end(); it++)
    {
        os << "\t{ x = " << it->x << "; y = " << it->y << " }" << std::endl;
    }
}
