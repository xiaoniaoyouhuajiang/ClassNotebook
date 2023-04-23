
#include <iostream>
#include "Unit.h"
#include "Field.h"
#include "FieldIterator.h"

void testCopyConstructor(Field fi){

};

int main()
{

	Field field(10, 10);

	auto* archer = new NoviceArcher;
	auto* paladin = new Paladin;


	field.addObj((Unit*) archer, 1, 1);
	field.addObj((Unit*) paladin, 2, 2);

	archer->attack(&field, paladin);

	paladin->move(&field, -1, -1);

    Iterator it(field);

    it.first();

    ++it;
    --it;

    auto tmp = (*it);

    testCopyConstructor(field);

	return 0;
}


