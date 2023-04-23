#include "figures.h"

int main() {
    
    Shape* ptr;

	ptr = new Pentagon(1.0, 3.0, 4.5);
	ptr->operator<<(std::cout);
	ptr->SetColour(25, 40, 100);
	ptr->Scale(2.0);
	ptr->Rotate(90);
	ptr->operator<<(std::cout);
	delete ptr;
	
	ptr = new Pentagram(5.0, 3.0, 2.5);
	ptr->operator<<(std::cout);
	ptr->SetColour(80, 140, 10);
	ptr->ChangeCoordinates(15.0, 48.3);
	ptr->Rotate(270);
	ptr->operator<<(std::cout);
	delete ptr;
	
	ptr = new Rectangle(5.0, 3.0, 2.5, 5.0);
	ptr->operator<<(std::cout);
	ptr->SetColour(250, 10, 135);
	ptr->ChangeCoordinates(80.2, 10.15);
	ptr->Rotate(180);
	ptr->operator<<(std::cout);
	delete ptr;

    return 0;
}