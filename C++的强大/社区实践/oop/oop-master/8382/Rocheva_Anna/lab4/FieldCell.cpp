#include "FieldCell.hpp"

FieldCell::FieldCell(){
    unit = nullptr;
    base = false;
    object = nullptr;

    int randomLand = rand() % 4;
    switch (randomLand){
        case 0: {
            landscape = new Grass;
            break;
        }
        case 1:{
            landscape = new Mountains;
            break;
        }
        case 2:{
            landscape = new Forest;
            break;
        }
        case 3:{
            landscape = new Swamp;
            break;
        }
        default:
            break;
    }

    int randomObj = rand() % 8;
    switch (randomObj) {
        case 0: {
            object = new Bar;
            break;
        }
        case 1: {
            object = new Hospital;
            break;
        }
        case 2: {
            object = new Shop;
            break;
        }
        case 3:{
            object = new TrainingBase;
            break;
        }
        default:
            break;
    }
}

void FieldCell::setCoordinates(int x, int y) {
    coordinates = new Coordinates;
    coordinates->x = x;
    coordinates->y = y;
}


