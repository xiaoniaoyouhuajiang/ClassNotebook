//
// Created by Alex on 16.02.2020.
//

#include "Field.h"
#include "../Units/Infantry/Spearmen.h"
#include "../Units/Cavalry/LightCavalry.h"
#include "../Units/Infantry/Swordmen.h"
#include "../Units/LongRangeIUnits/Arbalester.h"
#include "../Units/LongRangeIUnits/Archer.h"
#include "../Units/Cavalry/HeavyCavalry.h"
#include <iostream>

Field::Field(int width, int height, int maxCountUnits) : width(width), height(height), maxCountUnits(maxCountUnits) {
    Field::countUnits = 0;
    Field::landscapeFactory = new LandscapeFactory;
    Field::cells = new GameCell *[height];
    for (int i = 0; i < height; i++) {
        Field::cells[i] = new GameCell[width];
    }
    int count = 0;
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            cells[i][j].numer = count++;
            cells[i][j].setLanscape(landscapeFactory->getFieldLandscape());
        }
    }
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            std::cout << cells[i][j].numer << " ";
        }
        std::cout << '\n';
    }
    //iterator = new Iterator(cells,width);
    /*for (Iterator it  = begin(); it != end(); it=+1) {

    }*/

//    Iterator it  = begin();
//    std::cout << *it.;
//    GameCell *game = begin();
//    std::cout << (it).operator*().numer;

    auto it = Field::Iterator(begin());

    //std::cout << it.operator*().numer;
   /* for (int k = 0; k < 100; ++k) {
        std::cout << (*it).numer<<"\n";
        ++it;
    }*/

    while (it!=end()){
        std::cout << (it).operator*().numer<<"\n";
        it.operator++();
    }

    //auto it2 = Field::Iterator(begin());
    //std::cout << (it2).operator*().numer;

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



