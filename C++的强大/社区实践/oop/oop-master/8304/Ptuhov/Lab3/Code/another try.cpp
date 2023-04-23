#include "UnitFactory.h"  
#include "Field.h"
#include "Dialog.h"
#include <ctime>

int main()
{
	srand(time(nullptr));
/*
	bool isMoveCheck = false;
	// Демонстрация перемещения + абстрактная фабрика
	if (isMoveCheck)
	{
		UnitFactory* unf1 = new Tier1Factory();
		UnitFactory* unf2 = new Tier2Factory();
		UnitFactory* unf3 = new Tier3Factory();
		Field f(10, 10);

		f.addUnit(unf1->createType1(), { 4, 4 });
		f.addUnit(unf2->createType2(), { 5, 5 });
		f.addUnit(unf3->createType2(), { 6, 6 });
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
		f.addUnit(unf1->createType1(), { 4, 4 });
		std::cout << f;
		f.removeUnit({ 5, 9 });
		f.addUnit(unf1->createType1(), { 4, 4 });

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


	bool landscapeCheck = true;
	if (landscapeCheck)
	{
		std::cout << "Base value for Scout: hp = 50, damage = 20\n";

		Field f(10, 10);

		UnitFactory* unf1 = new Tier3Factory;
		auto un1 = unf1->createType1();
		auto un2 = unf1->createType2();

		f.addUnit(un1, { 4, 4 });
		std::cout << "After being on mount(-15 damage)\n";
		std::cout << "Scout damage = " << f[4][4].unit->damage.get() << "\n";

		std::cout << "\nBase value for Warrior: hp = 150, damage = 10\n";
		f.addUnit(un2, {5, 5 });
		std::cout << "After being on swamp(-15 hp)\n";
		std::cout << "Warrior hp = " << f[5][5].unit->hp.get() << "\n";
		f.removeUnit({ 5, 5 });

		std::cout << "\nAfter move Scout from mount to swamp\n";
		f.moveUnit({ 4, 4 }, { 5, 5 });
		std::cout << "Scout damage = " << f[5][5].unit->damage.get();
		std::cout << ", hp = " << f[5][5].unit->hp.get() << "\n";

		delete unf1;
	}

	bool BaseCheck = false;
	if (BaseCheck)
	{
		Field f(10, 10);
		UnitFactory* unf1 = new Tier3Factory;
		f.setMaxUnitCntToBase(2);
		f.createInBase(unf1->createType1(), { 4, 4 });
		f.createInBase(unf1->createType1(), { 5, 5 });

		std::cout << "Before using base: damage{4, 4} = " << f[4][4].unit->damage.get();
		std::cout << ", damage{5, 5} = " << f[5][5].unit->damage.get() << "\n";

		f.useBase();

		std::cout << "\nAfter using base: damage{4, 4} = " << f[4][4].unit->damage.get();
		std::cout << ", damage{5, 5} = " << f[5][5].unit->damage.get() << "\n";

		std::cout << "\nAfter deleting unit\n";
		f.removeUnit({ 5, 5 });
	}

	bool NtrlObjCheck = false;
	if (NtrlObjCheck)
	{
		std::cout << "Base value for Scout: hp = 50, damage = 20\n";

		Field f(10, 10);
		UnitFactory* unf1 = new Tier3Factory;
		f.addUnit(unf1->createType1(), { 6, 6 });
		std::cout << "After being on Trap(-20 hp) + swamp landscape(-15 hp)\n";
		std::cout << "Scout hp = " << f[6][6].unit->hp.get() << "\n";

		f.moveUnit({ 6, 6 }, { 7, 7 });
		std::cout << "\nAfter moving Scout to HillingRain(+20 hp) + mountain landscape(-15 damage)\n";
		std::cout << "Scout hp = " << f[7][7].unit->hp.get() << ", damage = " << f[7][7].unit->damage.get() << "\n";
	}
*/

	Dialog d;
	d.speak();

	return 0;
}