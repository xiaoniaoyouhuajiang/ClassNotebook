#include "TrapeziumFactory.h"

// метод для создания трапеции
// coord - вектор координат
// center - центра
// возвращаем новую трапецию с заданными значениями
AbstractShape* TrapeziumFactory::createShape(std::vector<Point> & coord, Point & center, int dots, std::string figure) {
	return new Trapezium(coord, center);
}