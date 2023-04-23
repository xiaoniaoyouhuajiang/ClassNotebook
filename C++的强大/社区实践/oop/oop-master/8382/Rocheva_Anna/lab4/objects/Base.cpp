#include "Base.hpp"

Base::Base() {
    coordinates = new Coordinates;
    numUnits = 0;
    health = new Health(1000);
    units = new CompositeUnit();
}

void Base::setCoordinates(int x, int y) {
    coordinates->x = x;
    coordinates->y = y;
}

void Base::createUnit(FieldCell *cell, UnitName name) {

    if (numUnits >= MAX_BASE_UNITS){
        std::cout << "You can't create new unit. Too much units." << std::endl;
        return;
    }

    logString = "The base has created a new unit: ";
    switch (name) {
        case INFANTRY: {
            auto factoryMethod = new InfantryFactoryMethod();
            cell->setUnit(factoryMethod->createUnit());
            logString += "infantry. ";
            break;
        }
        case GUARDSMEN: {
            auto factoryMethod = new GuardsmenFactoryMethod();
            cell->setUnit(factoryMethod->createUnit());
            logString += "guardsmen. ";
            break;
        }
        case FIGHTER: {
            auto factoryMethod = new FighterFactoryMethod();
            cell->setUnit(factoryMethod->createUnit());
            logString += "fighter. ";
            break;
        }
        case SCOUT: {
            auto factoryMethod = new ScoutFactoryMethod();
            cell->setUnit(factoryMethod->createUnit());
            logString += "scout. ";
            break;
        }
        case TANK: {
            auto factoryMethod = new TankFactoryMethod();
            cell->setUnit(factoryMethod->createUnit());
            logString += "tank. ";
            break;
        }
        case CANNON: {
            auto factoryMethod = new CannonFactoryMethod();
            cell->setUnit(factoryMethod->createUnit());
            logString += "cannon. ";
            break;
        }
        default:
            return;
    }

    units->addUnit(cell->getUnit());
    cell->getUnit()->setCoordinates(cell->getCoordinates()->x, cell->getCoordinates()->y);
    logString += ("Coordinates: (" + std::to_string(cell->getCoordinates()->x) + "," + std::to_string(cell->getCoordinates()->y) + ")");
    cell->getUnit()->addObservers(this);
}

void Base::deleteUnit(FieldCell *cell, int flag) {
    units->deleteUnit(cell->getUnit());
    cell->deleteUnit(flag);
    if (flag == 0) {
        logString = "The base has deleted unit from cell (";
        logString += (std::to_string(cell->getCoordinates()->x) + "," + std::to_string(cell->getCoordinates()->y)) + ")";
    }
}

void Base::moveUnit(FieldCell *cellIn, FieldCell *cellOut) {

    cellIn->setUnit(cellOut->getUnit());
    cellIn->getUnit()->setCoordinates(cellIn->getCoordinates()->x, cellIn->getCoordinates()->y);
    deleteUnit(cellOut, 1);
    units->addUnit(cellIn->getUnit());

    logString = "Unit moved from cell (";
    logString += (std::to_string(cellOut->getCoordinates()->x) + "," + std::to_string(cellOut->getCoordinates()->y) + ") ");
    logString += ("to cell (" +  std::to_string(cellIn->getCoordinates()->x) + "," + std::to_string(cellIn->getCoordinates()->y) + ")");
    auto proxy = new Proxy(cellIn->getLandscape()->getLandName());
    proxy->changeAttribute(cellIn->getUnit());
}

void Base::update(std::string newAction) {
    //std::cout << newAction << std::endl;
}

void Base::attackUnit(FieldCell *cell1, FieldCell *cell2) {

    if (cell1->getUnit()->getAttackValue() <= 0)
        return;;

    int health2 = cell2->getUnit()->getHealthValue();
    int defense2 = cell2->getUnit()->getDefenseValue();

    if (cell1->getUnit()->getAttackValue() - defense2 <= 0){
        cell2->getUnit()->changeAttributes(0, -1 * cell1->getUnit()->getAttackValue(), 0);
        cell1->getUnit()->changeAttributes(-1 * defense2/2, 0, 0);
        logString = "Unit from cell (";
        logString += (std::to_string(cell1->getCoordinates()->x) + "," + std::to_string(cell1->getCoordinates()->y));
        logString += ") tried to attack unit from cell (";
        logString += (std::to_string(cell2->getCoordinates()->x) + "," + std::to_string(cell2->getCoordinates()->y) + ").");
    }
    else if ((cell1->getUnit()->getAttackValue() - defense2 < health2)){
        cell2->getUnit()->changeAttributes(0, -1*defense2, -1 * cell1->getUnit()->getAttackValue() - defense2);
        logString = "Unit from cell (";
        logString += (std::to_string(cell1->getCoordinates()->x) + "," + std::to_string(cell1->getCoordinates()->y));
        logString += ") tried to attack unit from cell (";
        logString += (std::to_string(cell2->getCoordinates()->x) + "," + std::to_string(cell2->getCoordinates()->y) + ").");
    }
    else {
        deleteUnit(cell2);
        moveUnit(cell2, cell1);
        logString = "Unit from cell (";
        logString += (std::to_string(cell1->getCoordinates()->x) + "," + std::to_string(cell1->getCoordinates()->y));
        logString += ") attacked unit from cell (";
        logString += (std::to_string(cell2->getCoordinates()->x) + "," + std::to_string(cell2->getCoordinates()->y) + ").");
    }

}
