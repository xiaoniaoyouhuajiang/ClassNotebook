#include "Shape.h"
#include <utility>
#include <chrono>
#include <random>

size_t Shape::counter = 0; // инициализация статического поля


						   //оператор вывода
std::ostream& operator <<(std::ostream& OS, const Shape& smth)//оператор вывода
{
	smth.print(OS);
	return OS;
}
//установить цвет
void Shape::set_color(Color color) {//установить цвет

	this->color = color;

}

//получить цвет фигуры
Color Shape::get_color() const { //получить цвет

	return color;

}
//получить айди
size_t Shape::getId() const
{
	return id;
}

//передвинуть
void Shape::move(Dot &new_v0) {
	double dx = corners[0].x - new_v0.x;
	double dy = corners[0].y - new_v0.y;
	for (int i = 0; i < corners.size(); i++) {
		corners[i].x -= dx;
		corners[i].y -= dy;
	}
}
//расстянуть
void  Shape::scale(double scale) {
	if (scale < 0) {
		throw std::invalid_argument("Масштаб не может быть отрицательным");
	}
	for (int i = 0; i < corners.size(); i++) {
		corners[i].x *= scale;
		corners[i].y *= scale;
	}
}
//повернуть фигуру
void Shape::rotate(double new_angle) {
	Dot old_v0 = corners[0];
	move(Dot(0, 0));

	for (int i = 0; i < corners.size(); i++) {
		corners[i].rotate(new_angle);
	}
	move(old_v0);
}

bool Shape::common_side(Shape* other) {

	//std::vector<Dot>common_dots; // общие точки
	Dot cdot1;
	Dot cdot2;
	int dots = 0;


	bool flag1 = false;
	bool flag2 = false;

	for (int i = 0; i < this->corners.size(); i++) {
		for (int j = 0; j < other->corners.size(); j++)
		{
			//находим общие точки
			if (this->corners[i] == other->corners[j]) {
				if (dots == 0) {
					cdot1 = corners[i];
					++dots;
				}
				else if (dots == 1) {
					cdot2 = corners[i];
					++dots;
				}
			}
		}
	}
	if (dots != 2) {
		return false; // если не нашли, то стороны не пересекаются
	}

	for (int i = 0; i < other->corners.size(); i++) {
		if ((corners[i] == cdot1 && corners[(i + 1) % corners.size()] == cdot2) ||
			(corners[i] == cdot2 && corners[(i + 1) % corners.size()] == cdot1)) {
			flag1 = true;
		}
	}

	for (int i = 0; i < other->corners.size(); i++) {
		if ((other->corners[i] == cdot1 && other->corners[(i + 1) % corners.size()] == cdot2) ||
			(other->corners[i] == cdot2 && other->corners[(i + 1) % corners.size()] == cdot1)) {
			flag2 = true;
		}
	}

	return (flag1 && flag2);


}
Dot& Shape::min_y(Dot& a, Dot& b) const {
	if (a.y < b.y) {
		return a;
	}
	else {
		return b;
	}
}
Dot& Shape::max_y(Dot& a, Dot& b) const {
	if (a.y > b.y) {
		return a;
	}
	else {
		return b;
	}
}

