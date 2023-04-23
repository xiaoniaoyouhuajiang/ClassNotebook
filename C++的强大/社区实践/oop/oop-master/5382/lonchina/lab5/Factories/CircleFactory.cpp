#include "CircleFactory.h"

// метод для создания круга
// coord - вектор координат
// center - центра
// возвращаем новый круг с заданными значениями
/**
* @return
*/
AbstractShape* CircleFactory::createShape(std::vector<Point> & coord, Point & center, int dots, std::string figure) {
	return new Circle(coord, center);
}