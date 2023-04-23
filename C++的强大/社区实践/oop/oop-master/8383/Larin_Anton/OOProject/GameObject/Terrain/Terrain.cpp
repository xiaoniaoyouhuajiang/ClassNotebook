//
// Created by anton on 5/16/20.
//

#include "Terrain.h"

Terrain::Terrain(int x, int y, CommonClass objectClass, TerrainType terrainType, int steepness) : GameObject(x, y,
                                                                                                             false,
                                                                                                             Devotion::Neuter,
                                                                                                             ObjectType::Terrain,
                                                                                                             objectClass,
                                                                                                             1,
                                                                                                             1,
                                                                                                             1),
                                                                                                  terrainType(
                                                                                                         terrainType),
                                                                                                  steepness(steepness) {}

void Terrain::act(std::shared_ptr<GameObject> obj) {

}

void Terrain::react(std::shared_ptr<GameObject> sbj) {

}

void Terrain::step(std::shared_ptr<GameObject> obj) {

}

bool Terrain::canStep(int x, int y) {
    return false;
}

bool Terrain::canAct(int x, int y) {
    return false;
}

void Terrain::restep(std::shared_ptr<GameObject> sbj) {

}

int Terrain::getSteepness() {
    return steepness;
}
