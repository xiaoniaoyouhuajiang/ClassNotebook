
#include <iostream>
#include <string>
using namespace std;

int id = 1;

class Shape
{
	protected:
		string Colour;//цвет
		int ID;//идентификационный номер
		double Angle;//угол поворота в градусах
	public:
		Shape(): ID(id++), Colour("White"), Angle(0.0){};
		
		~Shape(){};
		
		virtual void Move(double, double)=0;//перемещение в указанные координаты
		
		void Rotation(double angle){//вращение на заданный угол
			if (angle >= 360.0) {
				while (angle >= 360.0)
					angle -= 360.0;
			}
			if (angle < 0.0) {
				while (angle < 0.0)
					angle += 360.0;
			}
			Angle = Angle + angle;
			while(Angle >= 360)
				Angle = Angle - 360;
			cout << "New angle is " << Angle <<endl;
		}

		virtual void Scaling(double)=0;//масштабирование 
		
		void setColour(string colour){//установка цвета
			Colour = colour;
			cout << "New colour is " << Colour <<endl;
		}
		
		string getColour() const{//получение цвета
			return Colour;
		}

		friend ostream & operator << (ostream&out, Shape &figure) { //оператор вывода в поток вывода
			figure.Shape::display(out);
			figure.display(out);
			return out;
	    }

	    virtual void display(ostream &out){
	    	out << "-------------------------------------------------------" << endl;
			out << "Base class output:" << endl;
			out << "ID = " << ID << endl;
			out << "Colour: " << Colour << endl;
			out << "Angle of rotation: " << Angle << endl;
			out << "-------------------------------------------------------" << endl;
		}
};

class Circle :public Shape
{
	private:
		double X0;
		double Y0;//координаты центра
		double R;//длина радиуса
	public:
		Circle():X0(0.0), Y0(0.0), R(1.0){};
		Circle(double x, double y, double a):X0(x), Y0(y), R(a){};
		~Circle(){};

		void Move(double x, double y) override{//перемещение в указанные координаты
			X0 = x;
			Y0 = y;
			cout << "The shape has been moved to a point: (" << x << "," << y << ")" <<std::endl;
		}

		void Scaling(double zoom) override{//масштабирование 
			if (zoom > 0.0) {
				R *= zoom;
				cout << "The shape " <<"has been scaled to: " << zoom << std::endl;
		}
			else
				cout << "Zoom <= 0!!!" << std::endl;
		}	

		void display(ostream &out) override{
			out << "Shape type: Circle" << endl;
			out << "Coordinates of the center: (" << X0 << "," << Y0 << ")" << endl;
			out << "Radius: " << R << endl;
			out << "-------------------------------------------------------" << endl;
		}
};

class Ellipse :public Shape
{
	protected:
		double X0;
		double Y0;//координаты центра
		double R1;//длина первого радиуса
		double R2;//длина второго радиуса
	public:
		Ellipse():X0(0.0), Y0(0.0), R1(1.0),R2(1.0){};
		Ellipse(double x, double y, double a, double b):X0(x), Y0(y), R1(a),R2(b){};
		~Ellipse(){};

		void Move(double x, double y) override{//перемещение в указанные координаты
			X0 = x;
			Y0 = y;
			cout << "The shape has been moved to a point: (" << x << "," << y << ")" <<std::endl;
		}

		void Scaling(double zoom) override{//масштабирование 
			if (zoom > 0.0) {
				R1 *= zoom;
				R2 *= zoom;
				cout << "The shape " <<"has been scaled to: " << zoom << std::endl;
		}
			else
				cout << "Zoom <= 0!!!" << std::endl;
		}	

		void display(ostream &out) override{
			out << "Shape type: Ellipse" << endl;
			out << "Coordinates of the center: (" << X0 << "," << Y0 << ")" << endl;
			out << "First radius: " << R1 << endl;
			out << "Second radius: " << R2 << endl;
			out << "-------------------------------------------------------" << endl;
		}
};

class SectorEllipse : public Ellipse{
private:
	double Angle1;//угол между первой стороной сектора и осью ОХ
	double Angle2;//угол между второй стороной сектора и осью ОХ
public:
	SectorEllipse():Ellipse(0.0,0.0,1.0,1.0), Angle1(1.0), Angle2(2.0){};
	SectorEllipse(double x, double y, double a, double b, double angle1, double angle2):Ellipse(x,y,a,b){
		Angle1 = angle1;
		if (Angle1 >= 360.0) {
			while (Angle1 >= 360.0)
				Angle1 -= 360.0;
			}
		if (Angle1 < 0.0) {
			while (Angle1 < 0.0)
				Angle1 += 360.0;
			}

		Angle2 = angle2;
		if (Angle2 >= 360.0) {
			while (Angle2 >= 360.0)
				Angle2 -= 360.0;
			}
		if (Angle2 < 0.0) {
			while (Angle2 < 0.0)
				Angle2 += 360.0;
		}

		if (Angle2 < Angle1) {
			double temp = Angle1;
			Angle1 = Angle2;
			Angle2 = temp;
		}
	};

	~SectorEllipse(){};

	void display(ostream &out) override{
		out << "Shape type: Sector of ellipse" << endl;
		out << "Coordinates of the center: (" << X0 << "," << Y0 << ")" << endl;
		out << "First radius: " << R1 << endl;
		out << "Second radius: " << R2 << endl;
		out << "Angle between the x-axis and the first side: " << Angle1 << std::endl;
		out << "Angle between the x-axis and the second side: " << Angle2 << std::endl;
		out << "-------------------------------------------------------" << endl;
	}
};

void test1() {
	Circle P1{};
	Circle P2(3.4, 8.3, 76.9);
	cout << P1 << P2<< endl;
	P1.Move(0.2, 11.0);
	P1.setColour("Blue");
	P2.Rotation(-340.0);
	cout << endl << P1 << P2 << endl;
}

void test2() {
	Ellipse E1{};
	Ellipse E2(5.0, 7.0, 3.1, 2.0);
	cout << E1 << E2<< endl;
	E1.Move(-134.2, 32.0);
	E1.setColour("Orange");
	E2.Rotation(78.0);
	cout << endl << E1 << E2 << endl;
}

void test3() {
	SectorEllipse S1{};
	SectorEllipse S2(-54.9, -48.3, 5.5, 5.5, 31.0, 90.0);
	cout << S1 << S2<< endl;
	S1.Move(56.8, -117.56);
	S1.setColour("Red");
	S2.Rotation(0.0);
	cout << endl << S1 << S2 << endl;
}

int main(){
	test1();
	test2();
	test3();
	return 0;
}