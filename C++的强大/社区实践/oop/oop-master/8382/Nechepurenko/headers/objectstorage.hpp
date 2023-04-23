#pragma once
#include "map.hpp"
#include "objectfactory.hpp"
#include "base.hpp"
#include <map>
#include <memory>

class ObjectStorage {
    public:
        ObjectStorage()  {}
        void setObject(Object* ao, std::shared_ptr<MapCell> cell);
        Unit* createUnit(std::shared_ptr<MapCell> cell, ObjectType ot = ObjectType::KNIGHT);
        void registerObject(Object* ao, std::shared_ptr<MapCell> cell, Base* base);
        void registerNeutral(Object* ao, std::shared_ptr<MapCell> cell);
        bool deleteNeutral(Object* ao);
        bool deleteObject(Object* ao);
        std::pair<uint32_t, uint32_t> getCoords(Object* ao);
        std::shared_ptr<MapCell> getCellPtr(Object* ao);
        void setBase(Unit* unit, Base* base);
        Base* getBase(Unit* unit);
        void eraseBase(Unit* unit);
        std::map<Object*, std::shared_ptr<MapCell>> getStorage();
        void setStorage(std::map<Object*, std::shared_ptr<MapCell>> newStorage);
        std::map<Object*, std::shared_ptr<MapCell>> getNeutral();
        void setNeutral(std::map<Object*, std::shared_ptr<MapCell>> newNeutral);

    private:
        std::map<Object*, std::shared_ptr<MapCell>> storage;
        std::map<Object*, std::shared_ptr<MapCell>> neutral;
        std::map<Unit*, Base*> base;
        //UnitFactory* unitFactory;

};