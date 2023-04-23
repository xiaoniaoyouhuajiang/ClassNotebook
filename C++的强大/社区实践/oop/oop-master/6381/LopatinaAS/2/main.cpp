#include "shapes.h"
#include <iostream>

int main() {
	Trapezoid trp(1,3,0,0,2,5,new Color(5,10,15));
	std::cout << trp << std::endl;

	Rectangle rec1(1,1,5,3,new Color(60,155,90));
	std::cout << rec1 << std::endl;

	Circle circle(5,new Dot(10,10),new Color(0,255,0));
	std::cout << circle << std::endl;

	Rectangle rec2(1,1,5,3,new Color(99,50,30));
	std::cout << rec2 << std::endl;

	std:: cout << "Circle after color change to 10,155,255" << std::endl;
	circle.set_color(new Color(10, 155, 255));
	std::cout << circle << std::endl;

	std:: cout << "Rectangle after moving to 2 units right and 3 units up" << std::endl;
	rec1.move(2,3);
	std::cout << rec1 << std::endl;

	std:: cout << "Trapezoid after a 45 degree turn" << std::endl;
	trp.rotation(45);
	std::cout << trp << std::endl;

	std:: cout << "Rectangle after increase 3 times" << std::endl;
	rec2.scaling(3);
	std::cout << rec2 << std::endl;

	return 0;
}