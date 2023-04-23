#include <iostream>
#include "Pentagon.h"
#include "Line.h"

void main()
{
	Pentagon pentagon(Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 }, Point{ 7, 8 }, Point{ 9, 10 });
	Line line(Point{ 2, 5 }, Point{ 6, 8 });
	std::cout << pentagon;




	std::cout << std::endl;
	system("PAUSE");
}