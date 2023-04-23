#include "Circle.h"
#include "Ellipse.h"
#include "Arc.h"
using namespace std;
int main() {

	Circle a(5, Point(0, 0), Color(255, 255, 255));
	Ellipse b(Point(2, 0), Point(-2, 0), 4, Point(0, 0), Color(255, 255, 255));
	Arc c(Point(-3, 0), Point(3, 0), 3, Point(0, 0), Color(255, 255, 255));
	a.Calibr(0.2);
	b.Calibr(0.5);
	b.Grad(45);
	cout << a << endl;
	cout << b << endl;
	cout << c << endl;
	system("pause");
	return 0;
}
