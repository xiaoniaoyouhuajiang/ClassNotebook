#include <QCoreApplication>
#include <iostream>
#include <unitsinterface.h>
#include <field.h>
#include <base.h>
#include <unitsclasses.h>
#include <abstractFactory.h>
#include <string>

void example1();
void example2();
void example3();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    example1();
    //example2();
    //example3();
}

void example1()
{
    std::cout << "Example 1\n";
    Field* field = new Field(5, 5, 5);
    int cols = 5;

    Base* baseHumans = new Base(field, HUMAN);
    baseHumans->createUnit(CRT_DMG_ARC, 1, 1);

    Base* baseElfs = new Base(field, ELF);
    baseElfs->createUnit(DMG_ABS_INF, 0, 2);

    std::cout << field->getStringInfo(cols).toStdString();
}

void example2()
{
    std::cout << "Example 2\n";
    Field* field = new Field(4, 4, 4);
    int cols = 4;
    Base* baseHumans = new Base(field, HUMAN);
    baseHumans->createUnit(CRT_DMG_ARC, 1, 1);

    Base* baseElfs = new Base(field, ELF);
    baseElfs->createUnit(DMG_ABS_INF, 1, 0);

    std::cout << field->getStringInfo(cols).toStdString();
    std:: cout << "\n\nNow archer at position [1][1] has extra damage\nand attacks the unit at position [1][0] and opponent's base at [2][3]\n\n";
    dynamic_cast<UnitInterface*>(field->getCell(1,1)->getCreature())->setDamage(500);
    field->commitFight(1, 1, 2, 3);
    field->commitFight(1, 1, 1, 0);
    std::cout << field->getStringInfo(cols).toStdString();
}

void example3()
{
    std::cout << "Example 3\n";
    Field* field = new Field(3, 3, 3);
    int cols = 3;
    Base* baseDw = new Base(field, HUMAN);
    Base* baseElf = new Base(field, ELF);

    std::cout << field->getStringInfo(cols).toStdString();
    std :: cout << "Now add village to [0][0] and  change landscapes on [2][2] and [2][1] and [1][1]\nThen add a cavalry to [0][0] and then print bonus from village\n\n";

    field->getCell(0, 0)->setNeutralObject(new Village());
    field->getCell(2, 1)->setLandscape(new Water());
    field->getCell(2, 2)->setLandscape(new Water());
    field->getCell(1, 1)->setLandscape(new Mountains());

    baseDw->createUnit(DMG_ABS_CAV, 0, 0);
    baseElf->createUnit(CRT_DMG_ARC, 0, 2);
    std::cout << field->getStringInfo(cols).toStdString();
    std :: cout << "Bonus from current neutral object is " << dynamic_cast<UnitInterface*>(field->getCell(0,0)->getCreature())->getHealth().getValue()
                << " " << dynamic_cast<UnitInterface*>(field->getCell(0,0)->getCreature())->getDamage()->getExtra()
                << " " << dynamic_cast<UnitInterface*>(field->getCell(0,0)->getCreature())->getArmor()->getExtra() << "\n";
}
