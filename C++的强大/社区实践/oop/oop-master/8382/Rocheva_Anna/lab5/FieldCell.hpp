#ifndef LABOOP_FIELDCELL_HPP
#define LABOOP_FIELDCELL_HPP

#include "landscapes/Forest.hpp"
#include "landscapes/Grass.hpp"
#include "landscapes/Mountains.hpp"
#include "landscapes/Swamp.hpp"
#include "landscapes/Proxy.hpp"

#include "objects/units/people/Infantry.hpp"
#include "objects/units/people/Guardsmen.hpp"
#include "objects/units/aircrafts/Fighter.hpp"
#include "objects/units/aircrafts/Scout.hpp"
#include "objects/units/groundForces/Tank.hpp"
#include "objects/units/groundForces/Cannon.hpp"

#include "objects/neutralObjects/Bar.hpp"
#include "objects/neutralObjects/Hospital.hpp"
#include "objects/neutralObjects/Shop.hpp"
#include "objects/neutralObjects/TrainingBase.hpp"

class FieldCell {
public:
    explicit FieldCell();
    explicit FieldCell(int land, int obj, bool base, Unit *unit1);
    bool isEmpty() { return unit == nullptr; };
    bool isObject() { return object != nullptr; };
    void setUnit(Unit *unit1) {this->unit = unit1;};
    Unit *getUnit() {return unit;};
    void setBase() {base = true;};
    bool isBase() {return base;};
    void setCoordinates(int x, int y);
    Coordinates *getCoordinates() {return coordinates;};
    NeutralObject *getObject() {return object;};
    void deleteUnit(int flag=0) {if (!flag) {delete unit;}; unit = nullptr;}; // если перемещение, то просто nullptr
    Landscape *getLandscape() { return landscape;};
    void deleteObject(){delete object; object = nullptr;};
    void setLandscape(int land);
    void setObject(int obj);
private:
    Unit *unit;
    Landscape *landscape;
    NeutralObject *object;
    bool base;
    Coordinates *coordinates;
};


#endif //LABOOP_FIELDCELL_HPP
