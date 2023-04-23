//
// Created by anton on 5/10/20.
//

#ifndef OOPROJECT_TERRAINPROXY_H
#define OOPROJECT_TERRAINPROXY_H

#include <memory>
#include <cassert>
#include "Terrain.h"


class CommonFactory;
class TerrainProxy:public Terrain{
public:

    static CommonClass terrainToCommon(TerrainType tt){
        switch (tt){

            case TerrainType::SpikyTerrain:
                return CommonClass ::SpikyTerrain;
            case TerrainType::SteepTerrain:
                return CommonClass ::SteepTerrain;
            case TerrainType::HollyTerrain:
                return CommonClass ::HollyTerrain;
        }
    }

    TerrainProxy(int x, int y, TerrainType terrainType,
                 const std::shared_ptr<CommonFactory> &commonFactory);

    virtual void restep(std::shared_ptr<GameObject> sbj) override;

    virtual void act(std::shared_ptr<GameObject> obj) override;

    virtual void react(std::shared_ptr<GameObject> sbj) override;

    virtual void step(std::shared_ptr<GameObject> obj) override;

    virtual bool canStep(int x, int y) override;

    virtual bool canAct(int x, int y) override;

    virtual int getSteepness();

    GameObjectFlyWeight * getFlyWeight() override;

    void setFlyWeight(GameObjectFlyWeight *flyWeight) override;

private:

    void init();

    CommonClass getObjectClass() override;

    std::shared_ptr<Terrain> object;//Kinda unique, but factoru makes shared
    std::shared_ptr<CommonFactory> commonFactory;
    CommonClass objClass;

};


#endif //OOPROJECT_TERRAINPROXY_H
