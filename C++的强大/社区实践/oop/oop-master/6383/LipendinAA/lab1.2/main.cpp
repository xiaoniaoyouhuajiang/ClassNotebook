#include "pentagon.h"
#include "point.h"
#include "rectangle.h"
#include "shape.h"
#include "pentagram.h"
#include <vector>

using namespace std;

int main()
{
	Point center_rectangle(2, 2);
	Rectangle rectangle(center_rectangle, 0, 0, 2, 2);
	rectangle.print(cout);
	//cout << rectangle;
	vector <Point> pentagon_vec{ Point(5, 1), Point(1, 4), Point(0, 3), Point(4, 5), Point(3, 0) };
	Point center_pentagon(3, 3);
	Pentagon pentagon(center_pentagon, 0, 0, pentagon_vec);
	pentagon.print(cout);
	//cout << pentagon;
	Point center_pentagram(0, 0);
	Pentagram pentagram(center_pentagram, 0, 0, 1);
	pentagram.print(cout);
	//cout << pentagram;
	system("pause");
	return 0;
}