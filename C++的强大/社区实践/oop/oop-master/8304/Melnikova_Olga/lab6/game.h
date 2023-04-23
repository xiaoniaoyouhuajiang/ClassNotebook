#pragma once

#include "field/field.h"
#include "objects/base.h"
#include "objects/object.h"
#include "fabrics/objectFabric.h"

#include "fabrics/landscapefabric.h"
#include "landscapes/cliffProxy.h"
#include "landscapes/gladeProxy.h"
#include "landscapes/swampProxy.h"

#include "strategies/istrategy.h"

#include "rules.h"

template <typename T>
class Game
{
public:
    ~Game(){

    }

    T rules;
    bool win = false;
    int winH = 2;
    int winW = 2;

    int currNumBase = false;

    Field* field;
    Base *base1;
    Base *base2;

    Landscape* cliff;
    Landscape* glade;
    Landscape* swamp;

    bool isActionDone = false;
    int isAttackDone = false;

    Game(){}


    Game(int h, int w, T rules)
    {
        field = new Field(h, w);

        currNumBase = rules.currNumBase;
        win = rules.end;
        if(win){
            winH = std::rand() % h +1;;
            winW = std::rand() % w +1;;
        }
        LandscapeFabric landFabric;
        cliff = landFabric.cliff();
        glade = landFabric.glade();
        swamp = landFabric.swamp();

        for (int i = 1; i <= h; i++){
            for (int j = 1; j <= w; j++){
                int random = std::rand() % 7 +1;
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

        if(rules.first){
            int randomH = std::rand() % h +1;
            int randomW = std::rand() % w +1;
            field->addObject(base1->createUnit("Archer"),randomH,randomW-1);
            randomH = std::rand() % h +1;
            randomW = std::rand() % w +1;
            field->addObject(base2->createUnit("Archer"),randomH,randomW-1);
        }else{
            field->addObject(base1->createUnit("Archer"),1,2);
            field->addObject(base2->createUnit("Archer"),h,w-1);
        }





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



    void atack(Unit* unit, Object* base){
        if(!(((Unit*)base)->shieldEnabled)){
            base->health = base->health - unit->damage;
        }else{
            ((Unit*)base)->shieldEnabled = false;
            ((Unit*)base)->shieldUsed = true;
        }
        if(base->health == 0){
            del((Unit*)base);
        }
    }


    bool move(int x1, int y1, int x2, int y2){
        field->cells(x2,y2).landscape->action->interact((Unit*)field->cells(x1,y1).innerObject);
        if((Unit*)field->cells(x1,y1).innerObject->health == 0){
            del((Unit*)field->cells(x1,y1).innerObject);
        }else{
            field->moveObject(x1,y1,x2,y2);
        }
    }


    bool moveToNeutral(Unit* unit, NeutralObject* obj){
        /*...*/
        obj->action->interact(unit);
        field->moveObject(unit->x,unit->y,obj->x,obj->y);
    }


    bool add(std::string who, bool numBase, int x, int y){
        if(!numBase){
            field->addObject(base1->createUnit(who),x,y);
        }else{
            field->addObject(base2->createUnit(who),x,y);
        }
        return true;
    }

    void del(Unit* unit){
        field->deleteObject(unit->x, unit->y);
    }

};
