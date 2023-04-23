//
// Created by anton on 2/18/20.
//

#include "UnitFactory.h"

/*
GameObject* UnitFactory::createUnit(UnitClass _class,UnitDevotion devotion,int x, int y) {

    switch (_class){

        case ALPHA:{
            Alpha* u = new Alpha(fld, x, y,0,devotion);
            return u;
            break;
        }
        case BETA:{
            Beta* u = new Beta(fld, x, y,0,devotion);
            return u;
            break;
        }
        case GAMMA:{
            Gamma* u = new Gamma(fld,x,y,0,devotion);
            return u;
            break;
        }
        case DELTA:{
            Delta* u = new Delta(fld, x, y,0,devotion);
            return u;
            break;
        }
        case EPSILON:{
            Epsilon* u = new Epsilon(fld, x, y,0,devotion);
            return u;
            break;
        }
        case ZETA:{
            Zeta* u = new Zeta(fld, x, y,0,devotion);
            return u;
            break;
        }
        case NO_CLASS:return nullptr;
        default:return nullptr;
    }


}
*/

UnitFactory::UnitFactory(Field *fld) : fld(fld) {}

UnitFactory::~UnitFactory() {

}
