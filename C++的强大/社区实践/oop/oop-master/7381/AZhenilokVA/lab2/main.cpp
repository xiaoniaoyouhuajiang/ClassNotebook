
#include <math.h>
#include <stdlib.h>
#include <iostream>

#include "ravntrap.h"
#include "trap.h"
#include "square.h"
using namespace std;

int main()
{

	square test1({ 1, 2 }, 2, { 255, 255, 255 });
	test1.write();
	test1.turn(80);
	test1.write();
	//точки вводятся начиная с верхней левой
	point p0 = { 1,2 }, p1 = { 3,2 }, p2{ 0,1 }, p3 = { 5,1 };
	double k1 = (p0.y - p1.y) / (p0.x - p1.x);
	double k2 = (p2.y - p3.y) / (p2.x - p3.x);

	if (k1 != k2) {
		std::cout << "Not a trapeze"<<std::endl;
		
	}
	else {
		trap test2(p0, p2, 2,6, { 205, 255, 255 });
		test2.write();
		test2.scale(2);
		test2.write();
	}
	//o - middle of midline of trapeze
	ravntrap test3(p0, 4, 6, 2,{ 123, 23, 77 });
	test3.write();
	test3.move({ 3, 6 });
	test3.turn(80);
	test3.write();
	return 0;
	system("pause");
}
