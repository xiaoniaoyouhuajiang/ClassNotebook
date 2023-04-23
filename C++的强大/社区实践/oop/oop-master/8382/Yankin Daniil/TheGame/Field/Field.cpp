#include "Field.h"
#include "Game/Game.h"
#include "Landscape/LandscapeHeader.h"
#include "Player/Player.h"
#include "Unit/UnitHeader.h"
#include "Base/Base.h"
#include "Rules/Rule.h"
#include <cstdlib>
#include <ctime>


Field::Field(uint16_t width, uint16_t height, uint16_t landscapeType) : maxUnitCoint(MAX_UNIT_COUNT_ON_FIELD), unitCount(0) {
    if (width >= MIN_FIELD_SIZE && height >= MIN_FIELD_SIZE) {
        this->width = width;
        this->height = height;
    }
    else {
        this->width = MIN_FIELD_SIZE;
        this->height = MIN_FIELD_SIZE;
    }

    if (landscapeType < LAND_WATER && landscapeType > LAND_FOREST_HILL) {
        landscapeType = LAND_PLAIN;
    }

    LandscapeFactory landscapeFactory;

    cellArray = new Cell*[this->height];
    for (uint16_t i = 0; i < this->height; i++) {
        cellArray[i] = new Cell[this->width];
        for (uint16_t j = 0; j < this->height; j++) {
            cellArray[i][j] = Cell(Point(j, i), landscapeFactory.produce(landscapeType, Point(j, i)));
        }
    }
}

Field::Field(uint16_t width, uint16_t height, std::vector<std::vector<uint16_t>> parameters) {
    // Сначала проверки на адекватность входных данных
    // Если входные данные не очень, переадресация на стандартный конструктор
    if (width < MIN_FIELD_SIZE || height < MIN_FIELD_SIZE) {
        Field(MIN_FIELD_SIZE, MIN_FIELD_SIZE, LAND_PLAIN);
        return;
    }
    if (parameters.size() != height) {
        Field(MIN_FIELD_SIZE, MIN_FIELD_SIZE, LAND_PLAIN);
        return;
    }
    for (auto vector : parameters) {
        if (vector.size() != width) {
            Field(MIN_FIELD_SIZE, MIN_FIELD_SIZE, LAND_PLAIN);
            return;
        }
    }
    this->width = width;
    this->height = height;

    cellArray = new Cell*[height];
    for (auto i = 0; i < height; i++) {
        cellArray[i] = new Cell[width];
    }
  
    // Остальные генератором псевдослучайных чисел
    // 0 - любое
    // 1 - проходимые
    // 2 - непроходимые
    // 3 - вода
    for (auto i = 0; i < height; i++) {
        for (auto j = 0; j < width; j++) {
            LandscapeFactory factory;
            int randVal;
            if (parameters[i][j] == INIT_LAND_ANY) {
                randVal = rand() % 130;
            }
            else if (parameters[i][j] == INIT_LAND_PASSABLE) {
                randVal = rand() % 90;
            }
            else if (parameters[i][j] == INIT_LAND_UNPASSABLE) {
                randVal = rand() % 40;
                randVal += 90;
            }
            else if (parameters[i][j] == INIT_LAND_WATER) {
                randVal = 90;
            }
            else {
                randVal = rand() % 90;
            }

            if (randVal >= 0 && randVal < 30) {
                cellArray[i][j] = Cell(Point(j, i), factory.produce(LAND_PLAIN, Point(j, i)));
            }
            else if (randVal >= 30 && randVal < 50) {
                cellArray[i][j] = Cell(Point(j, i), factory.produce(LAND_FOREST, Point(j, i)));
            }
            else if (randVal >= 50 && randVal < 70) {
                cellArray[i][j] = Cell(Point(j, i), factory.produce(LAND_HILL, Point(j, i)));
            }
            else if (randVal >= 70 && randVal < 90) {
                cellArray[i][j] = Cell(Point(j, i), factory.produce(LAND_FOREST_HILL, Point(j, i)));
            }
            else if (randVal >= 90 && randVal < 110) {
                cellArray[i][j] = Cell(Point(j, i), factory.produce(LAND_WATER, Point(j, i)));
            }
            else if (randVal >= 110 && randVal < 130) {
                cellArray[i][j] = Cell(Point(j, i), factory.produce(LAND_MOUNTAIN, Point(j, i)));
            }
            else {
                cellArray[i][j] = Cell(Point(j, i), factory.produce(LAND_PLAIN, Point(j, i)));
            }
        }
    }
}

Field::Field(FieldSnapshot& snapshot) : maxUnitCoint(200), unitCount(0) {
    width = snapshot.width;
    height = snapshot.height;

    bool correctInput = true;
    if (width < MIN_FIELD_SIZE || height < MIN_FIELD_SIZE) {
        correctInput = false;
    }

    LandscapeFactory landscapeFactory;

    if (correctInput) {
        cellArray = new Cell*[height];
        for (uint16_t i = 0; i < height; i++) {
            cellArray[i] = new Cell[width];
        }

        for (uint16_t i = 0; i < height; i++) {
            for (uint16_t j = 0; j < width; j++) {
                uint16_t landType = snapshot.landscapes[i][j];

                if (landType < LAND_WATER || landType > LAND_FOREST_HILL) {
                    landType = LAND_PLAIN;
                }

                cellArray[i][j] = Cell(Point(j, i), landscapeFactory.produce(landType, Point(j, i)));
            }
        }
    }

    else {
        width = MIN_FIELD_SIZE;
        height = MIN_FIELD_SIZE;

        cellArray = new Cell*[height];
        for (uint16_t i = 0; i < height; i++) {
            cellArray[i] = new Cell[width];
        }

        for (uint16_t i = 0; i < height; i++) {
            for (uint16_t j = 0; j < width; j++) {
                cellArray[i][j] = Cell(Point(j, i), landscapeFactory.produce(LAND_PLAIN, Point(j, i)));
            }
        }
    }
}

Field::~Field() {
    for (uint16_t i = 0; i < height; i++) {
        delete [] cellArray[i];
    }
    delete [] cellArray;
}


Field::Field(const Field &field) {
    width = field.width;
    height = field.height;
    cellArray = new Cell*[height];
    for (uint16_t i = 0; i < height; i++) {
        cellArray[i] = new Cell[width];
    }

    LandscapeFactory factory;
    Point point(0, 0);

    for (uint16_t i = 0; i < height; i++) {
        for (uint16_t j = 0; j < width; j++) {
            point = Point(j, i);
            uint16_t landType = field.cellArray[i][j].getLandscape()->getObjectType();

            cellArray[i][j] = Cell(Point(j, i), factory.produce(landType, point));

            cellArray[i][j].setUnit(field.cellArray[i][j].getUnit());

            uint16_t buildingType = field.cellArray[i][j].getBuildingGroupType();
            if (buildingType == BASE)
                cellArray[i][j].setBase(field.cellArray[i][j].getBase());
            else if (buildingType == NEUT_OBJECT)
                cellArray[i][j].setContext(field.cellArray[i][j].getContext());
        }
    }
}

Field& Field::operator=(Field &field) {
    if (&field == this) return *this;

    for (uint16_t i = 0; i < height; i++) {
        delete [] cellArray[i];
    }
    delete [] cellArray;

    width = field.width;
    height = field.height;
    cellArray = new Cell*[height];
    for (uint16_t i = 0; i < height; i++) {
        cellArray[i] = new Cell[width];
    }

    LandscapeFactory factory;
    Point point(0, 0);

    for (uint16_t i = 0; i < height; i++) {
        for (uint16_t j = 0; j < width; j++) {
            point = Point(j, i);
            uint16_t landType = field.cellArray[i][j].getLandscape()->getObjectType();

            cellArray[i][j] = Cell(Point(j, i), factory.produce(landType, point));

            cellArray[i][j].setUnit(field.cellArray[i][j].getUnit());

            uint16_t buildingType = field.cellArray[i][j].getBuildingGroupType();
            if (buildingType == BASE)
                cellArray[i][j].setBase(field.cellArray[i][j].getBase());
            else if (buildingType == NEUT_OBJECT)
                cellArray[i][j].setContext(field.cellArray[i][j].getContext());
        }
    }

    return *this;
}

Field::Field(Field &&field) {
    width = field.width;
    height = field.height;
    cellArray = field.cellArray;

    field.cellArray = nullptr;
}

Field& Field::operator=(Field &&field) {
    if (&field == this) return *this;

    for (uint16_t i = 0; i < height; i++) {
        delete [] cellArray[i];
    }
    delete [] cellArray;

    width = field.width;
    height = field.height;
    cellArray = field.cellArray;

    return *this;
}




uint16_t Field::getWidth() {
    return width;
}

uint16_t Field::getHeight() {
    return height;
}

Cell* Field::getCell(Point point) {
    if (point.getX() >= width || point.getY() >= height)
        return nullptr;
    return &(cellArray[point.getY()][point.getX()]);
}



ILandscape* Field::getLandscape(Point point) {
    return cellArray[point.getY()][point.getX()].getLandscape();
}


int Field::setUnit(Point point, IUnit* unit){
    auto cell = getCell(point);

    if (!cell->isUnitFree())
        return 1;

    if (!cell->isBuildingFree())
        if (cell->getBuildingGroupType() == BASE && cell->getBase()->getPlayer()->getColor() != unit->getPlayer()->getColor())
            return 1;

    cell->setUnit(unit);
    unitCount++;
    return 0;
}

IUnit* Field::getUnit(Point point) {
    return getCell(point)->getUnit();
}

void Field::removeUnit(Point point) {
    if (getCell(point)->isUnitFree())
        return;

    getCell(point)->removeUnit();
    unitCount--;
}


int Field::setBase(Point point, Base* base) {
    auto cell = getCell(point);

    if (!cell->isBuildingFree())
        return 1;

    if (!cell->isUnitFree())
        if (cell->getUnit()->getPlayer()->getColor() != base->getPlayer()->getColor())
            return 1;

    cell->setBase(base);
    return 0;
}

Base* Field::getBase(Point point) {
    return getCell(point)->getBase();
}

void Field::removeBase(Point point) {
    if (getCell(point)->getBuildingGroupType() != BASE)
        return;

    getCell(point)->removeBase();
}


int Field::setContext(Point point, NeutralContext* context) {
    if (!getCell(point)->isBuildingFree())
        return 1;

    getCell(point)->setContext(context);
    return 0;
}

NeutralContext* Field::getContext(Point point) {
    return getCell(point)->getContext();
}


bool Field::isUnitFree(Point point) {
    return getCell(point)->isUnitFree();
}

bool Field::isBuildingFree(Point point) {
    return getCell(point)->isBuildingFree();
}


uint16_t Field::getBuildingGroupType(Point point) {
    return getCell(point)->getBuildingGroupType();
}



bool Field::isBelowMaxUnitCount() {
    if (unitCount < maxUnitCoint)
        return true;
    return false;
}



Field::Iterator Field::begin() {
    return Iterator(this, cellArray[0]);
}

Field::Iterator Field::end() {
    return Iterator(this, cellArray[height - 1] + width);
}
