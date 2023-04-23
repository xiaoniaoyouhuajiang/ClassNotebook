//
// Created by anton on 5/30/20.
//

#ifndef OOPROJECT_FLYWEIGHT_H
#define OOPROJECT_FLYWEIGHT_H

#include <map>

#include "../Stats.h"

struct FlyWeight {
    std::map<std::pair<CommonClass ,Devotion>,GameObjectFlyWeight*> dict;

    GameObjectFlyWeight* getFlyWeight(CommonClass objectClass, Devotion devotion){
        if(dict.count({objectClass,devotion})){
            return dict[{objectClass,devotion}];
        }else{
            //dict[{objectClass,devotion}]=new GameObjectFlyWeight{"",CommonClass ::NONE,' ',devotion};
            switch (objectClass) {

                case CommonClass::NONE: {
                    dict[{objectClass,devotion}]= new GameObjectFlyWeight{"",CommonClass ::NONE,' ',devotion};
                    break;
                }
                case CommonClass::TheRanger: {
                    dict[{objectClass,devotion}]= new GameObjectFlyWeight{"TheRanger",objectClass,'R',devotion};
                    break;
                }
                case CommonClass::ThePowerful: {
                    dict[{objectClass,devotion}]= new GameObjectFlyWeight{"ThePowerful",objectClass,'P',devotion};
                    break;
                }
                case CommonClass::TheAgile: {
                    dict[{objectClass,devotion}]= new GameObjectFlyWeight{"TheAgile",objectClass,'A',devotion};
                    break;
                }
                case CommonClass::TheMarathoner: {
                    dict[{objectClass,devotion}]= new GameObjectFlyWeight{"TheMarathoner",objectClass,'M',devotion};
                    break;
                }
                case CommonClass::TheTough: {
                    dict[{objectClass,devotion}]= new GameObjectFlyWeight{"TheTough",objectClass,'T',devotion};
                    break;
                }
                case CommonClass::TheVampire: {
                    dict[{objectClass,devotion}]= new GameObjectFlyWeight{"TheVampire",objectClass,'V',devotion};
                    break;
                }
                case CommonClass::SpikyTerrain: {
                    dict[{objectClass,devotion}]= new GameObjectFlyWeight{"SpikyTerrain",objectClass,'^',devotion};
                    break;
                }
                case CommonClass::SteepTerrain: {
                    dict[{objectClass,devotion}]= new GameObjectFlyWeight{"SteepTerrain",objectClass,'~',devotion};
                    break;
                }
                case CommonClass::HollyTerrain: {
                    dict[{objectClass,devotion}]= new GameObjectFlyWeight{"HollyTerrain",objectClass,'%',devotion};
                    break;
                }
                case CommonClass::HealEntity: {
                    dict[{objectClass,devotion}]= new GameObjectFlyWeight{"HealEntity",objectClass,'+',devotion};

                    break;
                }
                case CommonClass::TrapEntity: {
                    dict[{objectClass,devotion}]= new GameObjectFlyWeight{"TrapEntity",objectClass,'<',devotion};
                    break;
                }
                case CommonClass::BlockEntity: {
                    dict[{objectClass,devotion}]= new GameObjectFlyWeight{"BlockEntity",objectClass,'#',devotion};
                    break;
                }
                case CommonClass::PitEntity: {
                    dict[{objectClass,devotion}]= new GameObjectFlyWeight{"PitEntity",objectClass,'@',devotion};
                    break;
                }
                case CommonClass::Base: {
                    dict[{objectClass,devotion}]= new GameObjectFlyWeight{"Base",objectClass,'$',devotion};
                    break;
                }
            }

        }
        auto ptr = dict[{objectClass,devotion}];
        assert(ptr);
        return ptr;

    }
};


#endif //OOPROJECT_FLYWEIGHT_H
