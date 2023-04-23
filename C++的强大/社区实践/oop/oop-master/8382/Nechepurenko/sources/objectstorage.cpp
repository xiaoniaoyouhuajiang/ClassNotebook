#include "../headers/objectstorage.hpp"

void ObjectStorage::setObject(Object* ao, std::shared_ptr<MapCell> cell) {
    this->storage[ao] = cell;
    cell->setObject(ao);
}

std::pair<uint32_t, uint32_t> ObjectStorage::getCoords(Object* ao) {
    if (this->storage[ao])
        return this->storage[ao]->getCoords();
    if (this->neutral[ao])
        return this->storage[ao]->getCoords();
    return std::make_pair(-1, -1);
}

std::shared_ptr<MapCell> ObjectStorage::getCellPtr(Object* ao) {
    if (this->storage[ao])
        return this->storage[ao];
    if (this->neutral[ao])
        return this->neutral[ao];
    return std::shared_ptr<MapCell>(nullptr);
}

// Hero* ObjectStorage::createUnit(std::shared_ptr<MapCell>& cell, ObjectType ot) {
//     if (this->curUnits == this->maxUnits) throw "111";
//     if (cell == nullptr) throw "222";
//     //Hero* newUnit = this->unitFactory->createObject(ot);
//     this->setObject(newUnit, cell);
//     cell->setObject(newUnit);
//     return newUnit;
// }

bool ObjectStorage::deleteObject(Object* ao) {
    if (!ao) return false;
    this->getCellPtr(ao)->deleteObject();
    this->storage.erase(this->storage.find(ao));
    return true;
}

void ObjectStorage::registerObject(Object* ao, std::shared_ptr<MapCell> cell, Base* base) {
    if (!ao) return;
    if (cell->getObject()){
        delete ao;
        return;
    }
    this->setObject(ao, cell);
}

void ObjectStorage::setBase(Unit* unit, Base* base) {
    this->base[unit] = base;
}
Base* ObjectStorage::getBase(Unit* unit) {
    return this->base[unit];
}
void ObjectStorage::eraseBase(Unit* unit) {
    this->base.erase(unit);
}

void ObjectStorage::registerNeutral(Object* ao, std::shared_ptr<MapCell> cell) {
    if (!ao) return;
    if (cell->getObject()){
        delete ao;
        return;
    }
    cell->setObject(ao);
    neutral[ao] = cell;
}

bool ObjectStorage::deleteNeutral(Object* ao) {
    if (!ao) return false;
    this->getCellPtr(ao)->deleteObject();
    this->neutral.erase(this->neutral.find(ao));
    return true;
}

std::map<Object*, std::shared_ptr<MapCell>> ObjectStorage::getStorage() {
    return storage;
}
void ObjectStorage::setStorage(std::map<Object*, std::shared_ptr<MapCell>> newStorage) {
    storage = newStorage;
}
std::map<Object*, std::shared_ptr<MapCell>> ObjectStorage::getNeutral() {
    return neutral;
}

void ObjectStorage::setNeutral(std::map<Object*, std::shared_ptr<MapCell>> newNeutral) {
    neutral = newNeutral;
}