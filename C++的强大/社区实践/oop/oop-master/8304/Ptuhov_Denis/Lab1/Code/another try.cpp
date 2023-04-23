#include "UnitFactory.h"  
#include "Field.h"
#include <ctime>

int main()
{
	srand(time(nullptr));

	bool isMoveCheck = false;
	// Демонстрация перемещения + абстрактная фабрика
	if (isMoveCheck)
	{
		UnitFactory* unf1 = new Tier1Factory();
		UnitFactory* unf2 = new Tier2Factory();
		UnitFactory* unf3 = new Tier3Factory();
		Field f(10, 10);

		f.addUnit(unf1->createType1(), { 0, 0 });
		f.addUnit(unf2->createType2(), { 1, 1 });
		f.addUnit(unf3->createType2(), { 2, 2 });
		std::cout << "Before:\n";
		std::cout << f;
		
		Field f2(std::move(f));
		std::cout << "\nAfter:\n";
		std::cout << f;
		std::cout << f2;

		delete unf1;
		delete unf2;
		delete unf3;
	}


	bool isMaxUnitCntCheck = false;
	// Демонстрация maxUnitCnt
	if (isMaxUnitCntCheck)
	{
		UnitFactory* unf1 = new Tier1Factory();
		Field f(10, 10);

		f.setMaxUnitsCnt(2);
		f.addUnit(unf1->createType1(), { 5, 9 });
		f.addUnit(unf1->createType1(), { 5, 8 });
		f.addUnit(unf1->createType1(), { 0, 0 });
		std::cout << f;
		f.removeUnit({ 5, 9 });
		f.addUnit(unf1->createType1(), { 0, 0 });

		std::cout << f;

		delete unf1;
	}


	bool IsIteratorCheck = false;
	// Демонстрация итератора дял поля
	if (IsIteratorCheck)
	{
		size_t ind = 0;
		UnitFactory* unf1 = new Tier1Factory();
		Field fld(10, 10);
		fld.addUnit(unf1->createType2(), { 9, 9 });
		fld.addUnit(unf1->createType2(), { 8, 8 });
		fld.addUnit(unf1->createType2(), { 0, 0 });

		std::cout << "| ";
		for (auto it = fld.begin(); it != fld.end(); ++it)
		{
			std::cout << (it->unit == nullptr ? ' ' : it->unit->name) << " | ";
			++ind;
			if (ind == fld.getHeight())
			{
				std::cout << "\n| ";
				ind = 0;
			}
		}

		for (auto it = fld.begin(); it != fld.end(); ++it)
		{
			if ((*it).unit != nullptr)
				(*it).unit = unf1->createType1();
		}

		std::cout << "\n\n| ";
		for (auto it = fld.begin(); it != fld.end(); ++it)
		{
			std::cout << (it->unit == nullptr ? ' ' : it->unit->name) << " | ";
			++ind;
			if (ind == fld.getHeight())
			{
				std::cout << "\n| ";
				ind = 0;
			}
		}

		auto it = fld.begin();
		++it;
		++it;
		it++;
		it++;
		(*it).unit = unf1->createType1();
		it--;
		--it; 
		(*it).unit = unf1->createType1();

		std::cout << "\n\n| ";
		for (auto it = fld.begin(); it != fld.end(); ++it)
		{
			std::cout << (it->unit == nullptr ? ' ' : it->unit->name) << " | ";
			++ind;
			if (ind == fld.getHeight())
			{
				std::cout << "\n| ";
				ind = 0;
			}
		}

		delete unf1;
	}

	return 0;
}