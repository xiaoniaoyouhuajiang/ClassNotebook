#include "LandscapeHeader.h"


Landscape* LandscapeFactory::produce(uint16_t landscapeType, Point point) {
    Landscape* landscape = nullptr;
    switch(landscapeType) {
    case LAND_WATER:
        landscape = new Water(point);
        break;
    case LAND_MOUNTAIN:
        landscape = new Mountain(point);
        break;
    case LAND_PLAIN:
        landscape = new Plain(point);
        break;
    case LAND_FOREST:
        landscape = new Forest(point);
        break;
    case LAND_HILL:
        landscape = new Hill(point);
        break;
    case LAND_FOREST_HILL:
        landscape = new ForestHill(point);
        break;
    }
    return landscape;
}
