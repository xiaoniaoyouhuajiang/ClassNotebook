#include "game.h"


Game::Game(int h, int w)
{

    field = new Field(h, w);

    LandscapeFabric landFabric;
    cliff = landFabric.cliff();
    glade = landFabric.glade();
    swamp = landFabric.swamp();

    for (int i = 1; i <= h; i++)
        for (int j = 1; j <= w; j++)
            field->cells(i, j).landscape = glade;

    objectFabric fabric;
    base1 = fabric.createBase(1,1,0);
    base2 = fabric.createBase(h,w,1);
    field->addObject(base1, base1->baseCell->x, base1->baseCell->y);
    field->addObject(base2, base2->baseCell->x, base2->baseCell->y);

    field->addObject(base1->createUnit("Archer"),1,2);

    field->addObject(fabric.createMedicineChest(),4,4);
}
Game::~Game(){}
