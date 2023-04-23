#include "stdafx.h"
#include "Shape.h"
int Shape::ID = 0;
Shape::Shape(){
	setId(ID);
	ID++;
}
Shape::~Shape(){
	Tops.clear();
}
void Shape::MoveFigure(double dx, double dy) {

	X = X + dx;
	Y = Y + dy;
};
void Shape::TurnFigure(int angle) {

	Angle = angle;
}
void Shape::ScaleFigure(double scale) {

	Scale = scale;
}
string  Shape::getColorFigure() const {

	return Color;
}
void Shape::setColorFigure(string color) {

	Color = color;
}
void  Shape::setAngle(int angle) {
	Angle = angle;
}
int  Shape::getAngle()const {
	return Angle;
}
void  Shape::setScale(double scale) {
	Scale = scale;
}
double  Shape::getScale()const {
	return Scale;
}
void  Shape::setId(int id) {
	Id = id;
}
int  Shape::getId() const {
	return Id;
}
double  Shape::getX() const {
	return X;
}
double  Shape::getY()const {
	return Y;
}
void Shape::setPoints(vector<Point> temp){
	Tops = temp;
}
vector<Point> Shape::getPoints() const{
	return Tops;
}
double Shape::getKoeff()const{
	return koeff;
}
void Shape::outPoint(ostream& a,int b)const{
	vector<Point> p = getPoints();
	for (int i = 0; i < b; i++){
		a << "Точка " << i + 1 << " :x= " << p[i].getX() << " ,y= " << p[i].getY() << "\n";
	}

}

bool Shape::hasCommonSide(const Shape& other){
	int lengOther = other.Tops.size();
	int lengMy= Tops.size();
	for (int i = lengOther; i <2* lengOther; i++){
		for (int j = lengMy; j <2* lengMy; j++){
			if (other.Tops[i % lengOther] == Tops[j % lengMy]){
				if (other.Tops[(i + 1) % lengOther] == Tops[(j + 1) % lengMy]) return true;
				if (other.Tops[(i - 1) % lengOther] == Tops[(j - 1) % lengMy]) return true;
				if (other.Tops[(i - 1) % lengOther] == Tops[(j + 1) % lengMy]) return true;
				if (other.Tops[(i + 1) % lengOther] == Tops[(j - 1) % lengMy]) return true;
			}
		}
	}
	return false;
}