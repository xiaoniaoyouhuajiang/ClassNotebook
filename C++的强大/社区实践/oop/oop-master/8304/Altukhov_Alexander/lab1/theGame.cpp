#include <locale>
#include <iostream>
#include "Field.h"
int main()
{
	setlocale(LC_ALL, "Russian");
	Field* f = new Field(3, 7);
	f->visualizeField();
	Unit* unit1 = f->createAndSetUnit(UnitTypes::HORSEMAN, 1, 1, 2, f);
	f->visualizeField();

	Field* f1 = new Field(4, 5);
	f1->visualizeField();

	f1->totalCopy(f, f1);

	std::cout << f->getAmountOfObjects() << " " << f1->getAmountOfObjects() << " \n";

	f->visualizeField();
	f1->visualizeField();
	f->deleteUnit(unit1);
	f->visualizeField();
	delete f;
	delete f1;
	return 0;
}


