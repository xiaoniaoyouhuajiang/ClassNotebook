#ifndef CONVERTFROMENUM_H
#define CONVERTFROMENUM_H
#include "enums.h"
#include <iostream>
using namespace std;
string convertFromEnumToLand(LandscapeType type){
    if(type == FOREST)
        return "forest";
    else if(type == RIVER)
        return "river";
    else if(type == MOUNTAIN)
        return "mountain";
    else{
        return "no such type of landscape";
    }
}
string convertFromEnumToNeutral(NeutralType type){
    if(type == HELMET)
        return "helmet";
    else if(type == MITTENS)
        return "mittens";
    else if(type ==SABATON)
        return "sabaton";
    else if(type == BANDAGE)
        return "bandage";
    else if(type == POWERPOTION)
        return "powerpotion";
    else if(type == COVID19)
        return "covid 19";
    else if(type == CODID37)
        return "covid 37";
    else if(type == SWORD)
        return "sword";
    else if(type == HATCHET)
        return "hatchet";
    else{
        return "no such type of neutral";
    }
}
string convertFromEnumToUnit(UnitsType type){
    if(type == ARCHER)
        return "archer";
    else if(type == SHAMAN)
        return "shaman";
    else if(type == KNIGTH)
        return "knigth";
    else if(type == RIDER)
        return "rider";
    else if(type == SWARDMAN)
        return "swardman";
    else if(type == ORK)
        return "ork";
    else if(type == COMPOSITEUNITS)
        return "compositeunits";
    else{
        return "no such type of unit";
    }
}
int convertFromNeutralToEnum(string type){
    if(type == "helmet")
        return 60;
    else if(type == "mittens")
        return 61;
    else if(type == "sabaton")
        return 62;
    else if(type == "bandage")
        return 63;
    else if(type == "powerpotion")
        return 64;
    else if(type == "covid 19")
        return 65;
    else if(type == "covid 37")
        return 66;
    else if(type == "sword")
        return 67;
    else if(type == "hatchet")
        return 68;
    else{
        return 0;
    }
}
int convertFromUnitToEnum(string type){
    if(type == "archer")
        return 20;
    else if(type == "shaman")
        return 21;
    else if(type == "knigth")
        return 22;
    else if(type == "rider")
        return 23;
    else if(type == "swardman")
        return 24;
    else if(type == "ork")
        return 25;
    else if(type == "compositeunits")
        return 26;
    else{
        return 0;
    }
}
#endif // CONVERTFROMENUM_H
