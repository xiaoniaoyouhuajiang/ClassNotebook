#include "../headers/objectfactory.hpp"

UnitFactory::UnitFactory(){
    this->map = { 
        {ObjectType::BOGATYR,[&](UnitParamList* p = nullptr) {
            return new Bogatyr(p);
        }}, 
        {ObjectType::TAMPLIER,[&](UnitParamList* p = nullptr) {return new Tamplier(p);}}, 
        {ObjectType::CHRISTIANWITCH,[&](UnitParamList* p = nullptr) {return new ChristianWitch(p);}}, 
        {ObjectType::BURNEDWITCH,[&](UnitParamList* p = nullptr) {return new BurnedWitch(p);}}, 
        {ObjectType::MULTIARCHER,[&](UnitParamList* p = nullptr) {return new MultiArcher(p);}}, 
        {ObjectType::WINDARCHER,[&](UnitParamList* p = nullptr) {return new WindArcher(p);}} 
    };
}

Unit* UnitFactory::createHero(ObjectType ot, UnitParamList* params) {
    if (this->map[ot]) {
        return this->map[ot](params); // todo 0 is a parameter list
    }
    return nullptr;
}