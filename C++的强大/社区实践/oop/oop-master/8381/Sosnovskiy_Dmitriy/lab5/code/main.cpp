#include <QApplication>
#include <iostream>
#include "gamewindow.h"
#include "field.h"
#include "base.h"

void example_1();

void example_2();

void example_3();

void example_4();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    w.show();

    return a.exec();
}

/* examples for 1 lab_work
void example_1()
{
    Field* field = new Field(10, 10, 6);

    std::cout << "Example 1." << "\n";
    std::cout << "Field size: " << field->getRowsAmount() << " rows, " << field->getColumnsAmount() << " columns.\n";

    std::cout << "Adding a CritArcher to position [1][1] and an AbsorbCavalry to [2][4] \n\n";

    CritDealersFactory* critDealersFactory = new CritDealersFactory;
    AbsorbersFactory* absorbersFactory = new AbsorbersFactory;

    field->addObject(1, 1, critDealersFactory->createArcher());
    field->addObject(2, 4, absorbersFactory->createCavalry());

    std::cout << field->getAsString().toStdString() << "\n";

    std::cout << "Done. \n\n";
}

void example_2()
{
    Field* field = new Field(3, 4, 4);

    std::cout << "Example 2." << "\n";
    std::cout << "Field size: " << field->getRowsAmount() << " rows, " << field->getColumnsAmount() << " columns.\n";

    std::cout << "Adding a CritInfantry to position [2][0] \n\n";

    CritDealersFactory* critDealersFactory = new CritDealersFactory;
    field->addObject(2, 0, critDealersFactory->createInfantry());

    std::cout << field->getAsString().toStdString() << "\n";
    std::cout << "Now move it to the [0][1] \n\n";

    field->moveUnit(2, 0, 0, 1);
    std::cout << field->getAsString().toStdString() << "\n";
    std::cout << "Done. \n\n";
}

void example_3()
{
    Field* field = new Field(5, 3, 6);

    std::cout << "Example 3." << "\n";
    std::cout << "Field size: " << field->getRowsAmount() << " rows, " << field->getColumnsAmount() << " columns.\n";

    std::cout << "Adding a AbsorbInfantry to position [2][0] \n\n";
    AbsorbersFactory* absorbersFactory = new AbsorbersFactory;
    field->addObject(2, 0, absorbersFactory->createInfantry());
    std::cout << field->getAsString().toStdString() << "\n";
    std::cout << "Now remove it \n\n";

    field->onCreatureRemoved(2, 0);
    std::cout << field->getAsString().toStdString() << "\n";
    std::cout << "Done. \n\n";
} */


/* examples for 2 lab work
void example_1()
{
    std::cout << "Example 1 - just showing that adding units with help of base is working successfully.\nGenerating field:\n";
    Field* field = new Field(3, 3, 3);
    Base* baseDw = new Base(field, DWARF);
    baseDw->createUnit(CRIT_ARCHER, 1, 1);
    Base* baseElf = new Base(field, ELF);
    baseElf->createUnit(ABSORB_INFANTRY, 2, 0);
    std::cout << field->getAsString().toStdString();
    std::cout << "-------------------------------------------------------------\n";
}

void example_2()
{
    std::cout << "Example 2\nGenerating field:\n";
    Field* field = new Field(3, 3, 3);
    Base* baseDw = new Base(field, DWARF);
    baseDw->createUnit(CRIT_ARCHER, 1, 1);
    Base* baseElf = new Base(field, ELF);
    baseElf->createUnit(ABSORB_INFANTRY, 2, 0);
    std::cout << field->getAsString().toStdString();

    std:: cout << "\n";
    std:: cout << "Now archer at position [1][1] has 1000 damage set by administrator of the game and attacks the infantry at position [2][0] and base at [2][2]\n";
    std:: cout << "\n";
    dynamic_cast<IUnit*>(field->getCell(1,1)->getCreature())->setDamage(1000);
    field->commitFight(1, 1, 2, 0);
    field->commitFight(1, 1, 2, 2);


    std::cout << field->getAsString().toStdString();
    std::cout << "-------------------------------------------------------------\n";

}

void example_3()
{
    std::cout << "Example 3\nGenerating field:\n";

    Field* field = new Field(3, 3, 3);
    Base* baseDw = new Base(field, DWARF);
    Base* baseElf = new Base(field, ELF);
    std::cout << field->getAsString().toStdString();


    std :: cout << "Now add tower to [1][1] and  change landscapes and [1][0] and [1][1]. Then add a cavalry to [1][1] and then the bonus armor from tower to cavalry will be printed.\n\n";
    field->getCell(1, 1)->setNeutralObject(new Tower());
    field->getCell(1, 0)->setLandscape(new Water());
    field->getCell(1, 1)->setLandscape(new Mountains());

    baseDw->createUnit(ABSORB_CAVALRY, 1, 1);

    std::cout << field->getAsString().toStdString();

    std :: cout << "Bonus armor from tower:" << dynamic_cast<IUnit*>(field->getCell(1,1)->getCreature())->getArmor()->getBonus() << "\n";
    std::cout << "-------------------------------------------------------------\n";

}

void example_4()
{
    Field* field = new Field(3, 3, 3);
    Base* baseDw = new Base(field, DWARF);
    Base* baseElf = new Base(field, ELF);

    baseDw->createUnit(ABSORB_ARCHER, 1, 1);

    field->getCell(0, 1)->setNeutralObject(new Banner());

    std::cout << field->getAsString().toStdString();

    std :: cout << "\n";

    std :: cout << "Damage value before:" << dynamic_cast<IUnit*>(field->getCell(1,1)->getCreature())->getDamage()->getValue() << "\n";
    std :: cout << "Damage bonus before:" << dynamic_cast<IUnit*>(field->getCell(1,1)->getCreature())->getDamage()->getBonus() << "\n\n";

    try{
        field->moveUnit(1, 1, 0, 1);
    } catch(...)  { }

    std::cout << field->getAsString().toStdString();

    std :: cout << "Damage value after: " << dynamic_cast<IUnit*>(field->getCell(0,1)->getCreature())->getDamage()->getValue() << "\n";
    std :: cout << "Damage bonus after: " << dynamic_cast<IUnit*>(field->getCell(0,1)->getCreature())->getDamage()->getBonus() << "\n";
}
*/
