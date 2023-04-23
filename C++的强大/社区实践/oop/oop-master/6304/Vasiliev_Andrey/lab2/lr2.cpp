#include <iostream>
#include "shape.h"
using namespace std;

int main()
{

		cout << "Square test!" << endl;
		Square s(Point(1,1),1,Color(1,2,3));
		cout << s;
		s.move(Point(2,2)).scale(2).rotate(180);
		cout << s;

		cout << "\nRight tri test!" << endl;
		RightTriangle t(Point(0,0),4,10);
		t.setColor(Color(23,23,23));
		cout << t;
		t.move(Point(5,0)).rotate(90).scale(0.5);
		cout << t;

		cout << "\nIso tri test!" << endl;
		IsosTriangle it(Point(0,0),8,20);
		cout << it;
		it.scale(0.25).rotate(-270).move(Point(5,-1));
		cout << it;


	return 0;
}
