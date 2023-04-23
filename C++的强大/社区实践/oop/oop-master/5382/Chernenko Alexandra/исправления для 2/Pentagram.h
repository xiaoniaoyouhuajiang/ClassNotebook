#include "stdafx.h"
#include "Shape.h"
class Pentagram : public Shape {
private:
	double  Side;
	Pentagram(const Pentagram&);
	void Pentagram::operator=(const Pentagram&);
public:
	Pentagram(double, double, double, double, int, string);
	Pentagram(double);
	void init();
	friend ostream&operator<<(ostream&a, const Pentagram*b){
		a << "ID фигуры: id=" << b->getId() << "\n";
		a << "Центр фигуры: x=" << b->getX() << "; y=" << b->getY() << "\n";
		a << "Цвет: " << b->getColorFigure() << "\n";
		a << "Угол поворота фигуры: фи=" << b->getAngle() << "\n";
		a << "Масштаб: дельта=" << b->getScale() << "\n";
		a << "Динны сторон с учетом мастаба: Сторона пентограммы=" << b->Side*b->getScale() << "\n";
		b->outPoint(a,5);
		return a;
	}
	friend ostream&operator<<(ostream&a, const Pentagram&b) {
		a << "ID фигуры: id=" << b.getId() << "\n";
		a << "Центр фигуры: x=" << b.getX() << "; y=" << b.getY() << "\n";
		a << "Цвет: " << b.getColorFigure() << "\n";
		a << "Угол поворота фигуры: фи=" << b.getAngle() << "\n";
		a << "Масштаб: дельта=" << b.getScale() << "\n";
		a << "Динны сторон с учетом мастаба: Сторона пентограммы=" << b.Side*b.getScale() << "\n";
		b.outPoint(a,5);
		return a;
	}
};
