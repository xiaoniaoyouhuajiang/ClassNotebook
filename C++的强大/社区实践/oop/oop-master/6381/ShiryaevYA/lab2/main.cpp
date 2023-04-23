#include <iostream>
#include <cstring>
#include <string>
#include <math.h>

#define PI 3.14159265358979323846264338279502884197169399375


using namespace std;

struct Point{
	double x;
	double y;
};

class Shape {
protected:

	string color;
	int angle;

public:
	virtual void move(double x, double y) = 0;
	virtual void scale(double coef) = 0;
	virtual void turn(int anglein) = 0;
	virtual ~Shape() {};
	//virtual Shape() {};
	virtual void sec_menu(){
		int choice;
		double x, y;
		double angle = 0;
		double coeff = 0;
		string color;
		cout << "what do you want to do?" << endl;
		cout << "1 - To move" << endl;
		cout << "2 - To turn" << endl;
		cout << "3 - To scale" << endl;
		cout << "4 - Change color" << endl;
		cout << "5 - Exit" << endl;
		cin >> choice;
		switch (choice){
			case 1:
				cout << "enter new coordinates of the center" << endl;
				cin >> x >> y;
				this->move(x,y);
				//Circle c(0,0,1);
				cout << *this;
				this->sec_menu();
				break;
			case 2:
				cout << "Enter the angle" << endl;
				cin >> angle;
				this->turn(angle);
				cout << *this;
				this->sec_menu();
				break;
			case 3:
				cout << "Enter the coefficient" << endl;
				cin >> coeff;
				this->scale(coeff);
				cout << *this;
				this->sec_menu();
			case 4:
				cout << "Enter the color" << endl;
				cin >> color;
				this->setColor(color);
				cout << *this;
				this->sec_menu();
			case 5:
				this->~Shape();
				return;
				break;
			default:
				cout << "Use only 1, 2, 3, 4, 5 keys" << endl;
				sec_menu();
		}
	}
	void setColor(string a){
		color = a;
	}
	string getColor(){
		return color;
	}
	virtual void printOUT(ostream& out) = 0; 
	friend std::ostream& operator<<(std::ostream& outStream, Shape& shape) {
		shape.printOUT(outStream);
		return outStream;
	}
};

class Circle : public Shape {

	Point center;
	Point right;
	Point top;
	Point left;
	Point bottom;
	double radius = 0;

public:
	Circle(double a, double b, double r){
		center = {a, b};
		radius = r;
		right = {a + r, b};
		top = {a, b + r};
		left = {a - r, b};
		bottom = {a, b - r};
		color = "black";
		angle = 0;
		cout << "circle created" << endl;
	}
	~Circle() = default;
	void printOUT(ostream& out){
		out << "center " << "(" << center.x << ";" << center.y << ")" << endl;
    	out << "right" << "(" << right.x << ";" << right.y << ")" << endl;
    	out << "top" << "(" << top.x << ";" << top.y << ")" << endl;
    	out << "left" << "(" << left.x << ";" << left.y << ")" << endl;
    	out << "bottom" << "(" << bottom.x << ";" << bottom.y << ")" << endl;
    	out << "color " << color << endl; 
	}
	void move(double x, double y) {
		double diffX, diffY;
		diffX = center.x - x;
		diffY = center.y - y;
		center = {x, y};
		right = {right.x - diffX, right.y - diffY};
		top = {top.x - diffX, top.y - diffY};
		left = {left.x - diffX, left.y - diffY};
		bottom = {bottom.x - diffX, bottom.y - diffY};
	}
	void turn(int anglein){
		if (angle == 0){
			angle = anglein % 360;
		}
		else{
			angle = (angle + (anglein % 360)) % 360;
		}
		
		cout << angle << endl;
		right = 	{(center.x + radius*cos(angle*PI/180)), (center.y + radius*sin(angle*PI/180))};
		top = 		{(center.x - radius*sin((angle)*PI/180)), (center.y + radius*sin((90 - angle)*PI/180))};
		left = 		{(center.x - radius*cos(angle*PI/180)), (center.y - radius*sin(angle*PI/180))};
		bottom = 	{(center.x + radius*sin((angle)*PI/180)), (center.y - radius*sin((90 - angle)*PI/180))};
	}
	void scale(double coeff){
		radius = radius * coeff;
		cout << radius << endl;
		right = 	{(center.x + radius*cos(angle*PI/180)), (center.y + radius*sin(angle*PI/180))};
		top = 		{(center.x - radius*sin((angle)*PI/180)), (center.y + radius*sin((90 - angle)*PI/180))};
		left = 		{(center.x - radius*cos(angle*PI/180)), (center.y - radius*sin(angle*PI/180))};
		bottom = 	{(center.x + radius*sin((angle)*PI/180)), (center.y - radius*sin((90 - angle)*PI/180))};
	}
};

class Rectangle: public Shape{

	Point center;
	Point rightT;
	Point rightB;
	Point leftT;
	Point leftB;
	double halfA;
	double halfB;
	double dia;
	double corner;

public:
	Rectangle(double a, double b){
		center 	= {0	, 0};
		rightT 	= {a/2 	, b/2};
		rightB 	= {a/2	, -b/2};
		leftT 	= {-a/2	, b/2};
		leftB 	= {-a/2	, -b/2};
		color = "black";
		angle = 0;
		halfA = a/2;
		halfB = b/2;
		dia = sqrt(pow(halfA,2)+pow(halfB,2));
		corner = atan(((b/2)/(a/2)));//*180/PI);
		//cout << corner << endl;
		corner = corner / PI;
		//cout << corner << endl;
		corner = corner * 180;
		cout << dia << endl;
		cout << halfA << endl;
		cout << halfB << endl;
		cout << angle << endl;
		// cout << corner << endl;
		//cout << corner << endl;

	}
	~Rectangle() = default;
	void move(double x, double y) {
		double diffX, diffY;
		diffX = center.x - x;
		diffY = center.y - y;
		center = {x, y};
		rightT = {rightT.x - diffX, rightT.y - diffY};
		rightB = {rightB.x - diffX, rightB.y - diffY};
		leftT = {leftT.x - diffX, leftT.y - diffY};
		leftB = {leftB.x - diffX, leftB.y - diffY};
	}
	void turn(int anglein){
		// НА СКОЛЬКО УМЕНЬШАЕШЬ НА СТОЛЬКО И УВЕЛИЧИВАЕШЬ С ПРОТИВОПОЛОЖНОЙ СТОРОНЫ!!!!!!
		if (angle == 0){
			angle = anglein % 360;
		}
		else{
			angle = (angle + (anglein % 360)) % 360;
		}
		rightT = 	{(center.x + dia*cos((angle + corner)*PI/180)), (center.y + dia*sin((angle + corner)*PI/180))};
		rightB = 	{(center.x + dia*cos((angle - corner)*PI/180)), (center.y - dia*sin((-angle + corner)*PI/180))};
		leftT = 	{(center.x - dia*cos((angle - corner)*PI/180)), (center.y + dia*sin((-angle + corner)*PI/180))};
		leftB = 	{(center.x - dia*cos((angle + corner)*PI/180)), (center.y - dia*sin((angle + corner)*PI/180))};
	}
	void scale(double coeff){
		dia *= coeff;
		// halfB = halfB * coeff;
		// halfA = halfA * coeff;
		// cout << halfA << " " << halfB << endl;
		rightT = 	{(center.x + dia*cos((angle + corner)*PI/180)), (center.y + dia*sin((angle + corner)*PI/180))};
		rightB = 	{(center.x + dia*cos((angle - corner)*PI/180)), (center.y - dia*sin((-angle + corner)*PI/180))};
		leftT = 	{(center.x - dia*cos((angle - corner)*PI/180)), (center.y + dia*sin((-angle + corner)*PI/180))};
		leftB = 	{(center.x - dia*cos((angle + corner)*PI/180)), (center.y - dia*sin((angle + corner)*PI/180))};
	}
	void printOUT(ostream& out){
		out << "center " << "(" << center.x << ";" << center.y << ")" << endl;
    	out << "right top" << "(" << rightT.x << ";" << rightT.y << ")" << endl;
    	out << "right bottom" << "(" << rightB.x << ";" << rightB.y << ")" << endl;
    	out << "left top" << "(" << leftT.x << ";" << leftT.y << ")" << endl;
    	out << "left bottom" << "(" << leftB.x << ";" << leftB.y << ")" << endl;
    	out << "color " << color << endl; 
	}
};

class Trapeze: public Shape{
	Point center;
	Point rightT;
	Point rightB;
	Point leftT;
	Point leftB;
	double dif1;
	double dif2;
	double height;
	double lenght;
	double dia;// = sqrt(pow(halfA,2)+pow(halfB,2));
	double corner;// = atan(((b/2)/(a/2)));//*180/PI);
	
public:
	Trapeze(double a, double b, double h, int ang){
		center = {0 , 0};
		leftB = {-a/2 , -h/2};
		rightB = {a/2 , -h/2};
		if (ang == 90){
			leftT = {-a/2 , h/2};
			dif1 = 0;
		}
		else{
			leftT = {leftB.x + h/tan(ang*PI/180) , h/2};
			dif1 = h/tan(ang*PI/180);
		}
		rightT = {leftT.x + b , h/2};
		dif2 = a/2 - rightT.x;
		height = h;
		lenght = a;
		angle = 0;
		dia = sqrt(pow((lenght/2),2)+pow((height/2),2));
		corner = atan((b/2)/(a/2)) / PI * 180;
		color = "black";
	}
	void move(double x, double y) {
		double diffX, diffY;
		diffX = center.x - x;
		diffY = center.y - y;
		center = {x, y};
		rightT = {rightT.x - diffX, rightT.y - diffY};
		rightB = {rightB.x - diffX, rightB.y - diffY};
		leftT = {leftT.x - diffX, leftT.y - diffY};
		leftB = {leftB.x - diffX, leftB.y - diffY};
	}
	void turn(int anglein){
		double s = 0;
		if (angle == 0){
			angle = anglein % 360;
		}
		else{
			angle = (angle + (anglein % 360)) % 360;
		}
		rightT = 	{round((center.x + dia*cos((angle + corner)*PI/180) - dif2*cos(angle * PI / 180))*10)/10, 
					 round((center.y + dia*sin((angle + corner)*PI/180) - dif2*sin(angle * PI / 180))*10)/10};
		rightB = 	{round((center.x + dia*cos((angle - corner)*PI/180))*10)/10, 
					 round((center.y - dia*sin((-angle + corner)*PI/180))*10)/10};
		leftT = 	{round((center.x - dia*cos((angle - corner)*PI/180) + dif1*cos(angle * PI / 180))*10)/10, 
					 round((center.y + dia*sin((-angle + corner)*PI/180) + dif1*sin(angle * PI / 180))*10)/10};
		leftB = 	{round((center.x - dia*cos((angle + corner)*PI/180))*10)/10, 
					 round((center.y - dia*sin((angle + corner)*PI/180))*10)/10};
	}
	void scale(double coeff){
		dia *= coeff;
		dif1 *= coeff;
		dif2 *= coeff;
		// halfB = halfB * coeff;
		// halfA = halfA * coeff;
		// cout << halfA << " " << halfB << endl;
		rightT = 	{round((center.x + dia*cos((angle + corner)*PI/180) - dif2*cos(angle * PI / 180))*10)/10, 
					 round((center.y + dia*sin((angle + corner)*PI/180) - dif2*sin(angle * PI / 180))*10)/10};
		rightB = 	{round((center.x + dia*cos((angle - corner)*PI/180))*10)/10, 
					 round((center.y - dia*sin((-angle + corner)*PI/180))*10)/10};
		leftT = 	{round((center.x - dia*cos((angle - corner)*PI/180) + dif1*cos(angle * PI / 180))*10)/10, 
					 round((center.y + dia*sin((-angle + corner)*PI/180) + dif1*sin(angle * PI / 180))*10)/10};
		leftB = 	{round((center.x - dia*cos((angle + corner)*PI/180))*10)/10, 
					 round((center.y - dia*sin((angle + corner)*PI/180))*10)/10};
	}
	void printOUT(ostream& out){
		out << "center " << "(" << center.x << ";" << center.y << ")" << endl;
    	out << "right top" << "(" << rightT.x << ";" << rightT.y << ")" << endl;
    	out << "right bottom" << "(" << rightB.x << ";" << rightB.y << ")" << endl;
    	out << "left top" << "(" << leftT.x << ";" << leftT.y << ")" << endl;
    	out << "left bottom" << "(" << leftB.x << ";" << leftB.y << ")" << endl;
    	out << "color " << color << endl; 
	}
};

void menu();

int main(){
	menu();
	return 0;
}

void menu(){
	int choice;
	cout << "what shape do you want to create?" << endl;
	cout << "1 - Circle" << endl;
	cout << "2 - Rectangle" << endl;
	cout << "3 - Trapeze" << endl;
	cout << "4 - Exit" << endl;
	cin >> choice;
	switch (choice){
		case 1:{
			Circle c(0,0,2);
			Shape *s = &c;
			//Circle * ptr = &c;
			cout << c;
			s->sec_menu();
			menu();
			break;	
		}
		case 2:{
			Rectangle r(2,1);
			Shape *s = &r;
			cout << r;
			s->sec_menu();
			menu();
			break;	
		}
		case 3:{
			Trapeze t(2,1,1,90);
			Shape *s = &t;
			cout << t;
			s->sec_menu();
			menu();
			break;
		}
		case 4:
			cout << "Good Bye" << endl;
			return;
			break;
	}
}