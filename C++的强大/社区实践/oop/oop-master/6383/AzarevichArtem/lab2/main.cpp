#include <iomanip>
#include "Circum.h"
#include "Pentagon.h"
#include "Reg_Pentagon.h"


void main()
{
	system("color 0A");

	Circum a(10, Point(0,0), Color(1,2,3));
	Pentagon b( Point(5,0), Point(10,0), Point(11,4), Point(7,7), Point(2,4), Color(1,2,3) );
	Reg_Pentagon c(Point(5,7), Point(5,4), Color(1,2,3));

	std::cout <<"Begin:\n\n"<< a << std::endl << b << std::endl << c << std::endl;

	// Повернуть на 180 град.
	a.Rotate(acos((double)-1)); b.Rotate(acos((double)-1)); c.Rotate(acos((double)-1));	// Вращение на 180 град.
		std::cout <<"__________\nRotate at 180 grad.:\n\n"<< a << std::endl << b << std::endl << c << "\n\n";
	
	// Перекрасить
	a.Set_Color(3,2,1); b.Set_Color(3,2,1); c.Set_Color(3,2,1);
		std::cout <<"__________\nRecolor to (3,2,1):\n\n"<< a << std::endl << b << std::endl << c << "\n\n";

	// Сместить на координаты ()
	a.Move(50, 50); b.Move(50, 50); c.Move(50, 50);
		std::cout <<"__________\nMove to (50;50):\n\n"<< a << std::endl << b << std::endl << c << "\n\n";
		
	// Уменьшить в 2 раза
	a.Scale(0.5); b.Scale(0.5); c.Scale(0.5);			
		std::cout <<"__________\nScale 0,5:\n\n"<< a << std::endl << b << std::endl << c << "\n\n";

	system("pause");
}