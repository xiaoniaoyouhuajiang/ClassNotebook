#include "stdafx.h"
#include "Shape.h"
class Pentagon : public Shape {
private:
	double  Side;
	Pentagon(const Pentagon&);
	void Pentagon::operator=(const Pentagon&);
public:
	Pentagon(double, double, double, double, int, string);
	Pentagon(double);
	void init();
	friend ostream&operator<<(ostream&a, const Pentagon*b){
		a << "ID фигуры: id=" << b->getId() << "\n";
		a << "Центр фигуры: x=" << b->getX() << "; y=" << b->getY() << "\n";
		a << "Цвет: " << b->getColorFigure() << "\n";
		a << "Угол поворота фигуры: фи=" << b->getAngle() << "\n";
		a << "Масштаб: дельта=" << b->getScale() << "\n";
		a << "Длины сторон с учетом масштаба: Сторона пятиугольника=" << b->Side*b->getScale() << "\n";
		b->outPoint(a,5);
		return a;
	}
	friend ostream&operator<<(ostream&a, const Pentagon&b) {
		a << "ID фигуры: id=" << b.getId() << "\n";
		a << "Центр фигуры: x=" << b.getX() << "; y=" << b.getY() << "\n";
		a << "Цвет: " << b.getColorFigure() << "\n";
		a << "Угол поворота фигуры: фи=" << b.getAngle() << "\n";
		a << "Масштаб: дельта=" << b.getScale() << "\n";
		a << "Динны сторон с учетом масштаба: Сторона пятиугольника=" << b.Side*b.getScale() << "\n";
		b.outPoint(a,5);
		return a;
	}
};
