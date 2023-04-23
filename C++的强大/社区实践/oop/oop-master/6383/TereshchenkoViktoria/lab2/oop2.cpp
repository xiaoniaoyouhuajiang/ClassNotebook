// oop2.cpp
// 5. Эллипс, сектор эллипса, параллелограмм
/*Необходимо спроектировать систему классов для моделирования геометрических фигур 
(в соответствии с полученным индивидуальным заданием). Задание предполагает использование виртуальных 
функций в иерархии наследования, проектирование и использование абстрактного базового класса.  
Разработанные классы должны быть наследниками абстрактного класса Shape, содержащего 
методы для перемещения в указанные координаты, поворота на заданный угол, масштабирования на заданный 
коэффициент, установки и получения цвета, а также оператор вывода в поток.
Необходимо также обеспечить однозначную идентификацию каждого объекта.*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Point
{
	double x;
	double y;
public:
	Point()
	{
		this->x = 0;
		this->y = 0;
	}

	Point(double x, double y)
	{
		this->x = x;
		this->y = y;
	}

	int getX()
	{
		return x;
	}

	int getY()
	{
		return y;
	}

	void setX(double x)
	{
		this->x = x;
	}
	
	void setY(double y)
	{
		this->y = y;
	}

	friend ostream& operator << (ostream &out, Point &po){
		out << "(" << po.x << "; " << po.y << ")" << endl;
		return out;
	}
};

class Shape
{
protected:
	Point center;
	int angle;
	string color = "black";
	vector<Point> points;

public:
	void move(Point newCenter) 
	{
		int changeX = newCenter.getX() - center.getX(), changeY = newCenter.getY() - center.getY();
		for (int i = 0; i < points.size(); i++)
		{
			points[i].setX(points[i].getX() + changeX);
			points[i].setY(points[i].getY() + changeY);
		}
	}

	void turn(int angle)
	{
		this->angle += angle%360;
		double angleRad = angle*3.14 / 180;
		for (int i = 0; i < points.size(); i++)
		{
			points[i].setX(points[i].getX()*cos(angleRad) - points[i].getY()*sin(angleRad));
			points[i].setY(points[i].getX()*sin(angleRad) + points[i].getY()*cos(angleRad));
		}
	}
	
	// virtual void scale(int k) = 0;	//чем отличается от {}
									// чистая виртуальная реализация
									// а {} - используется главным образом для деструкторов, чтобы не было утечки памяти
	virtual void scale(int k){};

	void setColor(string color) {
		this->color = color;
		cout << color << endl;
	}

	string getColor()
	{
		return color;
	}

	Shape(Point center)
	{
		this->center = center;
		this->angle = 0;
		this->color = "black";
	}

	friend ostream& operator << (ostream &out, Shape &sh){
		out << endl << "Shape: " << sh.center << ", " << sh.angle << ", " << sh.color << endl;
		// out << sh.points[0] << sh.points[1] << sh.points[2] << sh.points[3];
		return out;
	}
};

class Ellipse : public Shape // закомментить
{

protected:
    int radiusX;
	int radiusY;
	// vector<Point> points;	// добавить
								// и не использовать функции из класса Shape или скопировать их сюда и добавить поля соотв.

public:	
    Ellipse(Point center, int radiusX, int radiusY) : Shape(center) // если убрать Shape(center), надо чтобы скомпилировалось
    {
        this->radiusX = radiusX;
        this->radiusY = radiusY;
        points.push_back(Point((center.getX() - radiusX), center.getY()));
        points.push_back(Point(center.getX(), (center.getY() + radiusY)));
        points.push_back(Point((center.getX() + radiusX), center.getY()));
        points.push_back(Point(center.getX(), (center.getY() - radiusY)));
    }

    void scale(int k) 
    {
        int newRadiusX = radiusX*k;
        int newRadiusY = radiusY*k;
        points[0].setX(points[0].getX() - (k-1)*radiusX);   
        points[1].setY(points[1].getY() + (k-1)*radiusY);
        points[2].setX(points[2].getX() + (k-1)*radiusX);   
        points[3].setY(points[3].getY() - (k-1)*radiusY);
        radiusX = newRadiusX;
        radiusY = newRadiusY;    
    }

	friend ostream& operator << (ostream &out, Ellipse &sh){
		out << endl << "Ellipse: " << sh.radiusX << ", " << sh.radiusY /*<< ", " << sh.color */<< endl;
		out << sh.points[0] << sh.points[1] << sh.points[2] << sh.points[3];
		return out;
	}
};

class Pie : public Ellipse
{
	int angleP;

public:	

	Pie (Point center, int radiusX, int radiusY, int angleP) : Ellipse (center, radiusX, radiusY)
	{
		this->angleP = angleP%360;
		double anglePRad = angleP*3.14 / 180;
		double R = (radiusX*radiusY)/sqrt( (pow(radiusX, 2)*pow(sin(anglePRad), 2)) + (pow(radiusY, 2)*pow(cos(anglePRad), 2)) );
		double r = cos(anglePRad)*R;
		double h = sin(anglePRad)*R;
		// cout << R << endl;
		points.push_back(Point(center.getX(), center.getY()));
		points.push_back(Point((center.getX() + radiusX), center.getY()));
		if (90 >= angleP >= 0) points.push_back(Point((center.getX() + r), (center.getY() + h)));
		if (180 >= angleP >= 90) points.push_back(Point((center.getX() - r), (center.getY() + h)));
		if (270 >= angleP >= 180) points.push_back(Point((center.getX() - r), (center.getY() - h)));
		if (360 >= angleP >= 270) points.push_back(Point((center.getX() + r), (center.getY() - h)));
	}

	void scale(int k)
	{
		int newRadiusX = radiusX*k;
		int newRadiusY = radiusY*k;
		double anglePRad = angleP*3.14 / 180;
		
		points[2].setX(points[2].getX() + (k-1)*radiusX);
		double R = (radiusX*radiusY)/sqrt( (pow(radiusX, 2)*pow(sin(anglePRad), 2)) + (pow(radiusY, 2)*pow(cos(anglePRad), 2)) );
		double r = cos(anglePRad)*R;
		double h = sin(anglePRad)*R;
		double newR = (newRadiusX*newRadiusY)/sqrt( (pow(newRadiusX, 2)*pow(sin(anglePRad), 2)) + (pow(newRadiusY, 2)*pow(cos(anglePRad), 2)) );
		double newr = cos(anglePRad)*newR;
		double newh = sin(anglePRad)*newR;

		if (90 >= angleP >= 0)
		{
			points[6].setY(points[6].getY() - h + newh);
			points[6].setX(points[6].getX() - r + newr);
		}

		if (180 >= angleP >= 90 )
		{
			points[6].setX(points[6].getX() + r - newr);
			points[6].setY(points[6].getY() - h + newh);
		}

		if (270 >= angleP > 180)
		{
			points[6].setX(points[6].getX() + r - newr);
			points[6].setY(points[6].getY() + h - newh);
		}

		if (360 >= angleP > 270 ) 
		{
			points[6].setX(points[6].getX() - r + newr);
			points[6].setY(points[6].getY() + h - newh);
		}

		radiusX = newRadiusX;
		radiusY = newRadiusY;
	}

	friend ostream& operator << (ostream &out, Pie &sh){
		out << endl << "Pie: " << sh.radiusX << ", " << sh.radiusY << ", " << sh.angleP /*<< ", " << sh.color */<< endl;
		out << sh.points[4] << sh.points[2] << sh.points[6];
		return out;
	}
};

class Parallelogram : public Shape
{
    int sideA;
	int sideB;
	int heightA;
	int heightB;   // B == down/low, A == laterally

public:
    Parallelogram(Point center, int sideA, int sideB, int heightA, int heightB) : Shape(center)
    {
        this->sideA = sideA;
        this->sideB = sideB;
        this->heightA = heightA;
        this->heightB = heightB;
        points.push_back(Point((center.getX() - (sideB - sqrt(pow(sideA, 2) - pow(heightB, 2)))/2 - sqrt(pow(sideA, 2) - pow(heightB, 2))), (center.getY() - heightB/2)));
        points.push_back(Point((center.getX() - (sideB - sqrt(pow(sideA, 2) - pow(heightB, 2)))/2), (center.getY() + heightB/2)));
        points.push_back(Point((center.getX() + (sideB - sqrt(pow(sideA, 2) - pow(heightB, 2)))/2 + sqrt(pow(sideA, 2) - pow(heightB, 2))), (center.getY() + heightB/2)));
        points.push_back(Point((center.getX() + (sideB - sqrt(pow(sideA, 2) - pow(heightB, 2)))/2), (center.getY() - heightB/2)));
    }

    void scale(int k)
    {
        int newSideA = k*sideA;
        int newSideB = k*sideB;
        int newHeightA = k*heightA;
        int newHeightB = k*heightB;    
        points[0].setX(points[0].getX() - sideB/k - sqrt(pow(sideA, 2) - pow(heightB, 2))/k);
        points[0].setY(points[0].getY() - (newHeightB - heightB)/k);
        points[1].setX(points[1].getX() - (sideB/k - sqrt(pow(sideA, 2) - pow(heightB, 2))/k));
        points[1].setY(points[1].getY() + (newHeightB - heightB)/k);
        points[2].setX(points[2].getX() + sideB/k + sqrt(pow(sideA, 2) - pow(heightB, 2))/k);
        points[2].setY(points[2].getY() + (newHeightB - heightB)/k);
        points[3].setX(points[3].getX() + (sideB/k - sqrt(pow(sideA, 2) - pow(heightB, 2))/k));
        points[3].setY(points[3].getY() - (newHeightB - heightB)/k);
        sideA = newSideA;
        sideB = newSideB;
        heightA = newHeightA;
        heightB = newHeightB;
    }

	friend ostream& operator << (ostream &out, Parallelogram &sh){
		out << endl << "Paralleloram: " << sh.sideA << ", " << sh.sideB /*<< ", " << sh.color */<< endl;
		out << sh.points[0] << sh.points[1] << sh.points[2] << sh.points[3];
		return out;
	}
};


int main()
{
	Shape sh({});
	sh.scale(2);
	cout << sh;
	Ellipse el({}, 8, 4);
	// el.move({2, 2});
	// el.turn(30);
	// el.scale(2);
	cout << el;
	Pie pi({}, 2, 1, 30);
	// pi.move({2, 2});
	// pi.turn(60);
	// pi.scale(2);
	// cout << pi;
	// Parallelogram pa({}, 4, 6, 2, 2.3);
	// pa.move({1, 1});
	// pa.turn(30);
	// pa.scale(2);	
	// cout << pa;
    return 0;
}




























/*%2F%2F Cool Class Diagram, [Point| double x; double y|Point()]<>->[Shape], 
[Shape| Point center; int angle; string color; vertor<Point> points| void move(Point newCenter); void turn(int angle); virtual void scale(int k); void setColor(string color); string gerColor(); Shape(Point center)]++->[Ellipse| int radiusX; int radiusY | Ellipse(); void scale(int k)], [Shape| Point center; int angle; string color; vertor<Point> points| void move(Point newCenter); void turn(int angle); virtual void scale(int k); void setColor(string color); string gerColor(); Shape(Point center)]++->[Pie|int radiusX; int radiusY; int angleP|Pie(); void scale(int k)],[Shape| Point center; int angle; string color; vertor<Point> points| void move(Point newCenter); void turn(int angle); virtual void scale(int k); void setColor(string color); string gerColor(); Shape(Point center)]++->[Parallelogram|int sideA; int sideB; int heightA; int heightB|Parallelogram(); void scale(int k)]*/