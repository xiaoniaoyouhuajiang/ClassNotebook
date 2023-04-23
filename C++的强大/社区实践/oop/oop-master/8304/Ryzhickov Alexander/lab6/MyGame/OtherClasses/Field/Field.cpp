//
// Created by Alex on 21.03.2020.
//

#include <iostream>
#include "Field.h"
#include "../Landscapes/ProxyLandscape.h"

Field::Field(int width, int height, int maxCountUnits) : width(width), height(height), maxCountUnits(maxCountUnits) {
    Field::countUnits = 0;
    Field::landscapeFactory = new LandscapeFactory;
    Field::cells = new GameCell *[width];
    for (int i = 0; i < width; i++) {
        Field::cells[i] = new GameCell[height];
    }
    int count = 0;
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            cells[i][j].numer = count++;
            cells[i][j].setLanscape(landscapeFactory->getFieldLandscape());
        }
    }

    cells[2][4].setLanscape(landscapeFactory->getMountainLandscape());
    cells[7][0].setLanscape(landscapeFactory->getMountainLandscape());
    //cells[0][0].setLanscape(landscapeFactory->getMountainLandscape());


    /*std::cout << "hello\n";

    for (int k = height-1; k > -1; --k) {
        for (int i = 0; i < width; ++i) {
            if (dynamic_cast<FieldLandscape *>(cells[i][k].getLanscape()) != nullptr) {
                std::cout << "* ";
            }
            if (dynamic_cast<MountainsLandscape *>(cells[i][k].getLanscape()) != nullptr) {
                std::cout << "| ";
            }
        }
        std::cout <<'\n';
    }*/


//    cells[0][0].setLanscape(landscapeFactory->getMountainLandscape());
//    cells[9][4].setLanscape(landscapeFactory->getMountainLandscape());
//    cells[10][4].setLanscape(landscapeFactory->getMountainLandscape());


    /*// Демонстрационный пример работы итератора
    // Выводи номера клеток в двойном цикле
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            std::cout << cells[i][j].numer << " ";
        }
        std::cout << '\n';
    }

    // Выводим номера клеток с использованием итератора
    auto it = Field::Iterator(begin());

    while (it!=end()){
        std::cout << (*it).numer<<"\n";
        ++it;
    }*/

}

Field::~Field() {
    for (int i = 0; i < height; i++) {
        delete (Field::cells[i]);
    }
    delete (cells);
}


Field::Field(const Field &field) : height(field.height), width(field.width),
                                   maxCountUnits(field.maxCountUnits) {

    Field::countUnits = field.countUnits;
    Field::cells = new GameCell *[height];
    for (int i = 0; i < height; i++) {
        Field::cells[i] = new GameCell[width];
    }

    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            Field::cells[j][i] = field.cells[j][i];
        }
    }

}


int Field::getWidth() const {
    return width;
}


int Field::getHeight() const {
    return height;
}


int Field::getMaxCountUnits() const {
    return maxCountUnits;
}


int Field::getCountUnits() const {
    return countUnits;
}

void Field::appendUnits(int x, int y, Unit *unit) {
    if (countUnits < maxCountUnits) {
        cells[x][y].setUnit(unit);
        countUnits++;
    }
}

void Field::deleteUnits(int x, int y) {
    cells[x][y].deleteUnit();
    countUnits--;
}

void Field::setBase(int x,int y,Base *base) {
    Field::cells[x][y].setBase(base);
}

GameCell *Field::getCell(int x, int y) {
    return &cells[x][y];
}

void Field::setUnit(int x,int y,Unit *unit) {
    cells[x][y].setUnit(unit);
}

void Field::updateUnitPosition(int lastX, int lastY, int newX, int newY) {
    setUnit(newX,newY,cells[lastX][lastY].getUnit());
    cells[lastX][lastY].deleteUnit();

    ProxyLandscape proxyLandscape (cells[newX][newY].getLanscape());
    //proxyLandscape.getBonus(cells[newX][newY].getUnit());
}

void Field::resetUnits() {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            cells[i][j].setUnit(nullptr);
        }
    }
}
