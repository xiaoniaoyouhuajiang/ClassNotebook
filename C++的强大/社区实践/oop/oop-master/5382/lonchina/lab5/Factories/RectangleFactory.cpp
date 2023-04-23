#include "RectangleFactory.h"

// метод для создания треугольника
// coord - вектор координат
// center - центра
// возвращаем новый треугольник с заданными значениями
AbstractShape* RectangleFactory::createShape(std::vector<Point> & coord, Point & center, int dots, std::string figure) {
	return new Rectangle(coord, center);
}
