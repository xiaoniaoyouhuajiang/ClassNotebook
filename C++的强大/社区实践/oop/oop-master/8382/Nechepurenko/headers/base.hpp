#pragma once
#include "objectfactory.hpp"

class Base : public Object{
    public:
        virtual Unit* createUnit(ObjectType t, UnitParamList* p) = 0;
        void deleteObject(Unit* o);
        void unitDied(Unit* au);
        int getCurrent();
        int getCreated();
        int getMax();
        int getDied();
        std::vector<Unit*> getUnits();
        void setCurrent(int newCurrent);
        void setCreated(int newCreated);
        void setMax(int newMax);
        void setDied(int newDied);
        void setUnits(const std::vector<Unit*> &units);
        Unit* getCurrentUnit();
        void setCurrentUnit(Unit* unit);
        Base() = default;
        Unit* next();
        virtual void describe() = 0;
    protected:
        Base(ObjectType ot, int max_units = 50) 
        : Object(ot), factory(new UnitFactory), maxUnits(max_units), currentUnit(nullptr) {}
        UnitFactory* factory;
        int curUnits = 0;
        int createdUnits = 0;
        int maxUnits;
        int unitsDied = 0;
        std::vector<Unit*> units;
        Unit* currentUnit;
        size_t currentUnitPos = 0;
};

class RadiantBase : public Base {
    public:
        RadiantBase(int max_units = 10) : Base(ObjectType::RADIANTBASE, max_units) {}
        virtual Unit* createUnit(ObjectType t, UnitParamList* p);
        virtual void describe();
        ~RadiantBase() { delete factory; }
        std::string repr(){
            return std::string("R");
        }
        
};

class DireBase : public Base {
    public:
        DireBase(int max_units = 10) : Base(ObjectType::DIREBASE, max_units) {}
        virtual Unit* createUnit(ObjectType t, UnitParamList* p);
        virtual void describe();
        ~DireBase() { delete factory; }
        std::string repr(){
            return std::string("D");
        }
};