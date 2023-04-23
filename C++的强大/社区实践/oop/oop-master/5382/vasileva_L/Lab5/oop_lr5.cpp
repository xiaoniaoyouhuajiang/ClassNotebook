#include "oop_lr5.h"

int main()
{
	srand(time(0));
	unsigned size = 1000;
	
	stepik::vector<stepik::shared_ptr<Shape>> shapes = GenerationVector(size);	

	for (int i = 0; i < shapes.size(); i++)
	{
		std::cout << " P = " << shapes[i]->Perimeter() << std::endl;				
		std::cout << *shapes[i] << "\n";			
	}

	std::cout << "\n----------Find Equals-----------------\n";
	stepik::shared_ptr<Shape> foundEqual;	
	if (SearchforEqualinColor(shapes, foundEqual)) 
		std::cout << *(foundEqual);
	std::cout << "\n--------------------------------------\n";

	stepik::vector<stepik::shared_ptr<Shape>> shapes2 = UniontwoDiapazons(shapes, 2, 100, 50, 900);	

	std::cout << "\n---------Make from two diapason:result-----------\n";
	for (int i = 0; i < shapes2.size(); i++)
	{
		std::cout << "P = " << shapes2[i]->Perimeter() << "\n";	
		std::cout << *shapes2[i] << "\n";		
	}
	std::cout << "\n-------------------------------------------------\n";

	return 0;
}
