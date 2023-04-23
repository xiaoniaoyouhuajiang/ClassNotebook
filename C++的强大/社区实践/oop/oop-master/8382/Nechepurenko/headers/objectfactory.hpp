#pragma once
#include "object.hpp"
#include "unit.hpp"
#include <functional>
#include <map>

typedef int ParamList;

class AbstractObjectFactory {
    public:
        virtual Object* createObject(ObjectType ot) = 0;  
};

class UnitFactory : public AbstractObjectFactory {
    public:
        UnitFactory();
        Object* createObject(ObjectType ot) {}
        Unit* createHero(ObjectType ot = ObjectType::MULTIARCHER, UnitParamList* params = nullptr);

    private:
        std::map<ObjectType, std::function<Unit* (UnitParamList*)>> map;
};

class NeutralObjectFactory : public AbstractObjectFactory {
    public:
        Object* createObject(ObjectType ot = ObjectType::NEUTRAL_HEAL);
};