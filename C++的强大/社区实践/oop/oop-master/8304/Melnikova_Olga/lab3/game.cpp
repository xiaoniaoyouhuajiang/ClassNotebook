#include "game.h"

Game::Game(){}

Game::Game(int h, int w)
{
    field = new Field(h, w);

    LandscapeFabric landFabric;
    cliff = landFabric.cliff();
    glade = landFabric.glade();
    swamp = landFabric.swamp();

    for (int i = 1; i <= h; i++){
        for (int j = 1; j <= w; j++){
            int random = std::rand() % 20 +1;
            if(field->cells(i,j).innerObject){
                field->cells(i, j).landscape = glade;
            }else{
                if(random==1){
                    field->cells(i, j).landscape = cliff;
                }else if(random==2){
                    field->cells(i, j).landscape = swamp;
                }else{
                    field->cells(i, j).landscape = glade;
                }
            }
        }
    }

    objectFabric fabric;
    base1 = fabric.createBase(1,1,0);
    base2 = fabric.createBase(h,w,1); //numbase 0 ??????
    field->addObject(base1, base1->baseCell->x, base1->baseCell->y);
    field->addObject(base2, base2->baseCell->x, base2->baseCell->y);

    field->addObject(base1->createUnit("Archer"),1,2);
    field->addObject(base2->createUnit("Archer"),h,w-1);


    for (int i = 1; i <= h; i++){
        for (int j = 1; j <= w; j++){
            int random = std::rand() % 20 +1;
            if(field->cells(i,j).innerObject == nullptr){
                if(random==1){
                    field->addObject(fabric.createMedicineChest(), i, j);
                    //field->cells(i, j).innerObject = fabric.createMedicineChest();
                }else if(random==2){
                    field->addObject(fabric.createPowerUp(), i, j);
                    //field->cells(i, j).innerObject = fabric.createPowerUp();
                }else if(random==3){
                    field->addObject(fabric.createShield(), i, j);
                    //field->cells(i, j).innerObject = fabric.createShield();
                }else if(random==4){
                    field->addObject(fabric.createHorse(), i, j);
                    //field->cells(i, j).innerObject = fabric.createHorse();
                }
            }
        }
    }
}

Game::~Game(){}

void Game::atack(Unit* unit, Object* base){
    if(!(((Unit*)base)->shieldEnabled)){
        base->health = base->health - unit->damage;
    }else{
        ((Unit*)base)->shieldEnabled = false;
    }
    if(base->health == 0){
        del((Unit*)base);
    }
}

bool Game::move(int x1, int y1, int x2, int y2){
    field->cells(x2,y2).landscape->action->interact((Unit*)field->cells(x1,y1).innerObject);
    if((Unit*)field->cells(x1,y1).innerObject->health == 0){
        del((Unit*)field->cells(x1,y1).innerObject);
    }else{
        field->moveObject(x1,y1,x2,y2);
    }
}

bool Game::moveToNeutral(Unit* unit, NeutralObject* obj){
    /*...*/
    obj->action->interact(unit);
    field->moveObject(unit->x,unit->y,obj->x,obj->y);
}

bool Game::add(std::string who, bool numBase, int x, int y){
    if(!numBase){
        field->addObject(base1->createUnit(who),x,y);
    }else{
        field->addObject(base2->createUnit(who),x,y);
    }
    return true;
}
void Game::del(Unit* unit){
    field->deleteObject(unit->x, unit->y);
}
