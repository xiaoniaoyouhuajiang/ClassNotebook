#include "stdafx.h"
#include "Shape.h"
class Rectangle : public Shape {
private:
	double SideX, SideY;
	Rectangle(const Rectangle&);
	void Rectangle::operator=(const Rectangle&);
public:
	Rectangle(double, double, double, double, double, int, string);
	Rectangle(double, double);
	void init();
	vector<Point> side(double, double, vector<Point>);
	friend ostream&operator<<(ostream&a, const Rectangle&b){
		a << "ID фигуры: id=" << b.getId() << "\n";
		a << "Центр фигуры: x=" << b.getX() << "; y=" << b.getY() << "\n";
		a << "Цвет: " << b.getColorFigure() << "\n";
		a << "Угол поворота фигуры: фи=" << b.getAngle() << "\n";
		a << "Масштаб: дельта=" << b.getScale() << "\n";
		a << "Динны сторон с учетом мастаба: Горизонтальная сторона=" << b.SideX*b.getScale() << " Вертикальная сторона = " << b.SideY*b.getScale() << "\n";
		b.outPoint(a,4);
		return a;
	}
	friend ostream&operator<<(ostream&a, const Rectangle*b) {
		a << "ID фигуры: id=" << b->getId() << "\n";
		a << "Центр фигуры: x=" << b->getX() << "; y=" << b->getY() << "\n";
		a << "Цвет: " << b->getColorFigure() << "\n";
		a << "Угол поворота фигуры: фи=" << b->getAngle() << "\n";
		a << "Масштаб: дельта=" << b->getScale() << "\n";
		a << "Динны сторон с учетом мастаба: Горизонтальная сторона=" << b->SideX*b->getScale() << " Вертикальная сторона = " << b->SideY*b->getScale() << "\n";
		b->outPoint(a,4);
		return a;
	}
	
};
