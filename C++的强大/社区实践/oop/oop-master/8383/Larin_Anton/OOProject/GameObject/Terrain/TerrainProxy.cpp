//
// Created by anton on 5/10/20.
//

#include "TerrainProxy.h"

#include "../../Factory/CommonFactory.h"

TerrainProxy::TerrainProxy(int x, int y, TerrainType terrainType,
                           const std::shared_ptr<CommonFactory> &commonFactory) : Terrain(x, y, TerrainProxy::terrainToCommon(terrainType),
                                                                                          terrainType, 0),
                                                                                  commonFactory(commonFactory),objClass(TerrainProxy::terrainToCommon(terrainType)) {}

void TerrainProxy::restep(std::shared_ptr<GameObject> sbj) {
    init();
    object->restep(std::move(sbj));
}

void TerrainProxy::act(std::shared_ptr<GameObject> obj) {
    init();
    object->act(std::move(obj));

}

void TerrainProxy::react(std::shared_ptr<GameObject> sbj) {
    init();
    object->react(std::move(sbj));
}

void TerrainProxy::step(std::shared_ptr<GameObject> obj) {
    init();
    object->step(std::move(obj));
}

bool TerrainProxy::canStep(int x, int y) {
    init();
    return object->canStep(x, y);
}

bool TerrainProxy::canAct(int x, int y) {
    init();
    return object->canAct(x, y);
}

int TerrainProxy::getSteepness() {
    init();
    return object->getSteepness();
}

void TerrainProxy::init(){
    try {
        std::pair<int, int> c = getCoords();
        if (object)return;
        std::shared_ptr<GameObject> ptr(
                std::move(commonFactory->createObject(c.first, c.second, getDevotion(), objClass)));
        auto tPtr = std::dynamic_pointer_cast<Terrain>(ptr);
        assert(tPtr);//TODO exeption base made incastable terrain
        steepness = tPtr->steepness;
        object=std::move(tPtr);
    }catch(MediatorNotSetException& e){
        std::cerr<<e;
    }
}

CommonClass TerrainProxy::getObjectClass() {
    return objClass;
}

GameObjectFlyWeight * TerrainProxy::getFlyWeight() {
    init();
    auto ptr = object->getFlyWeight();
    assert(ptr);
    return ptr;
}

void TerrainProxy::setFlyWeight(GameObjectFlyWeight *flyWeight) {
    init();
    GameObject::setFlyWeight(flyWeight);
}
