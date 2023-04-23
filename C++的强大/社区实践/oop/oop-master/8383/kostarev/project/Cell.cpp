#include <iostream>
#include "Cell.h"
#include "Naming.h"
#include "Buildings.h"

Cell::Cell(){
    buildingOnCell = nullptr;
}

Cell::Cell(const Cell& oldCell) {
    this->buildingOnCell = oldCell.buildingOnCell;
}

void Cell::addBuild(char type) {
    if (buildingOnCell == nullptr){
        switch (type){
            case 'D':
                buildingOnCell = new Dacha();
                break;
            case 'H':
                buildingOnCell = new Hrushchovka();
                break;
            case 'F':
                buildingOnCell = new Ferma();
                break;
            case 'O':
                buildingOnCell = new Office();
                break;
            case 'S':
                buildingOnCell = new School();
                break;
            case 'V':
                buildingOnCell = new Vodokanal();
                break;
            case 'P':
                buildingOnCell = new Powerhouse();
                break;
            default:
                return;
        }
    }
}

void Cell::removeBuild() {
    buildingOnCell = nullptr;
}

void Cell::aboutCell() {
    if (buildingOnCell != nullptr){
        TypeOfBuild typeOfBOnCell = (buildingOnCell)->typeOfBuild();
        std::cout << "Saldo: " << dynamic_cast<Building*>(buildingOnCell)->getSaldo() << std::endl;
        std::cout << "Energy: " << dynamic_cast<Building*>(buildingOnCell)->getEnergy() << std::endl;
        std::cout << "Water: " << dynamic_cast<Building*>(buildingOnCell)->getWater() << std::endl;
        std::cout << "Eat: " << dynamic_cast<Building*>(buildingOnCell)->getEat() << std::endl;
        if (typeOfBOnCell == DACHA || typeOfBOnCell == HRUSHCHOVKA){
            std::cout << "Workmans: " << dynamic_cast<Apartment*>(buildingOnCell)->getWorkmans() << std::endl;
            std::cout << "Students: " << dynamic_cast<Apartment*>(buildingOnCell)->getStudents() << std::endl;
            std::cout << "Kids: " << dynamic_cast<Apartment*>(buildingOnCell)->getKids() << std::endl;
        } else if (typeOfBOnCell == FERMA || typeOfBOnCell == OFFICE){
            std::cout << "Workmans: " << dynamic_cast<Production*>(buildingOnCell)->getVacancy() << std::endl;
        }
    } else{
        std::cout << "No build" << std::endl;
    }
}

char Cell::typeBuild() {
    if (buildingOnCell != nullptr){
        switch (buildingOnCell->typeOfBuild()){
            case DACHA:
                return 'D';
            case HRUSHCHOVKA:
                return 'H';
            case FERMA:
                return 'F';
            case OFFICE:
                return 'O';
            case SCHOOL:
                return 'S';
            case VODOKANAL:
                return 'V';
            case POWERHOUSE:
                return 'P';
        }
    }
    return '0';
}

int Cell::aboutCell_Saldo() {
    return dynamic_cast<Building*>(buildingOnCell)->getSaldo();
}

Building *FactoryOfBuildings::creator(TypeOfBuild typeOfB) {
    switch (typeOfB){
        case DACHA:
            return new Dacha();
        case HRUSHCHOVKA:
            return new Hrushchovka();
        case FERMA:
            return new Ferma();
        case OFFICE:
            return new Office();
        case SCHOOL:
            return new School();
        case VODOKANAL:
            return new Vodokanal();
        case POWERHOUSE:
            return new Powerhouse();
        default:
            return nullptr;
    }
}
