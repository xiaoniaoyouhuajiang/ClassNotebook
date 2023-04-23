#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <ctime>
#include "Pentagon.h"
#include "Line.h"
#include "Ellipse.h"
#include "shared_ptr.h"
#include "vector.h"
float random()
{
	return (rand() / (float)RAND_MAX * 1000);
}

bool isNoOne(std::vector<std::shared_ptr<Shape>> shapes, float perimeter)
{
	for (size_t i = 0; i < shapes.size(); i++)
	{
		if (shapes[i]->Perimeter() < perimeter)
			return 1;
	}
	return 0;
}


 void Copy(stepik::vector<stepik::shared_ptr<Shape>> shapes, float perimeter) {
	 size_t i = 0; size_t k = 0;
	 while (i < shapes.size()) {
		 if (shapes[i]->Perimeter() < perimeter) {
			 shapes.erase(&shapes[i]);
			 std::cout << i + k << " deleted" << std::endl;
			 k++;
		 }
		 else
			 i++;
	 }
 }


void main()
{
	srand(time(0));
	std::vector<std::shared_ptr<Shape>> shapes;
	for (size_t i = 0; i < 1000; i++)	
	{
		std::shared_ptr<Shape> shape;
		switch (rand() % 3)
		{
		case 0:
			shape = std::shared_ptr<Shape>(
				new Line(Point{ random(), random() }, Point{ random(), random() })
			);
			shapes.push_back(std::shared_ptr<Shape>(shape));
			break;
		case 1:
			shape = std::shared_ptr<Shape>(
				new Ellipse(Point{ random(), random() }, Point{ random(), random() })
			);
			shapes.push_back(std::shared_ptr<Shape>(shape));
			break;
		case 2:
			shape = std::shared_ptr<Shape>(
				new Pentagon(
					Point{ random(), random() }, 
					Point{ random(), random() }, 
					Point{ random(), random() }, 
					Point{ random(), random() }, 
					Point{ random(), random() })
			);
			shapes.push_back(std::shared_ptr<Shape>(shape));
			break;
		}
	}

	system("PAUSE");
}