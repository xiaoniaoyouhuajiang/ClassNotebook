#include <iostream>
#include <vector>
#include "Field.h"
#include "unit.h"
#include "Factory.h"
#include "Iterator.h"



std::vector<Unit*> createArmy(AbstractFactory& factory) {
	
	std::vector<Unit*> legion;
	Unit* swordman = factory.createDivisionA();
	legion.push_back(swordman);
	Unit* spearman = factory.createDivisionB();
	legion.push_back(spearman);
	return legion;

}

int main() {

	Field field(10, 10, 10);

	WarriorsFactory *factory = new WarriorsFactory();
	std::vector<Unit*> warriors_legion = createArmy(*factory);

	field.AddObj(warriors_legion[0], 1, 1);
	field.AddObj(warriors_legion[1], 2, 3);
	//f.Moving(warriors_legion[0], 2, 3, 1, -1);
	//f.RemObj(warriors_legion[1], 1, 1);
	
	field.PrintField();

	std::cout << std::endl;


	Field newfield(0, 0, 0);

	newfield = field;
	newfield.PrintField();

	//Iterator it(field);
	//it.first();
	//++it;
	//--it;
	//auto tmp = (*it);
	//Field newfield(10,5,10);
	//Field *n = f.CopyField(&newfield);
	//n->PrintField();


	return 0;

}
