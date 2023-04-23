//
// Created by shenk on 14.02.2020.
//

#include <iostream>
#include "GameField.h"

GameField::GameField(int fieldSize):
fieldHeight(fieldSize),
fieldWidth(fieldSize),
objectsCount(0)
{

    field = new Unit** [fieldSize];
    for (int i=0; i<fieldSize; i++){
        field[i] = new Unit* [fieldSize];
        for (int j=0; j<fieldSize; j++){
            field[i][j] = nullptr;
        }
    }
}

GameField::GameField(int fieldHeight, int fieldWidth):
fieldHeight(fieldHeight),
fieldWidth(fieldWidth),
objectsCount(0)
{
    field = new Unit** [fieldHeight];
    for (int i=0; i<fieldHeight; i++){
        field[i] = new Unit* [fieldWidth];
        for (int j=0; j<fieldWidth; j++){
            field[i][j] = nullptr;
        }
    }

}

GameField::GameField(const GameField &other) :
fieldWidth(other.fieldWidth),
fieldHeight(other.fieldHeight),
maxObjectsCount(other.maxObjectsCount)
{

    field = new Unit** [fieldHeight];
    for (int i=0; i<fieldHeight; i++){
        field[i] = new Unit* [fieldWidth];
        for (int j=0; j<fieldWidth; j++){
            if (other.field[i][j])
                field[i][j] = new Unit(*other.field[i][j]);
            else
                field[i][j] = nullptr;
        }
    }
}

GameField::GameField(GameField &&other) :
fieldWidth(other.fieldWidth),
fieldHeight(other.fieldHeight),
maxObjectsCount(other.maxObjectsCount),
objectsCount(other.objectsCount)
{

    field = other.field;
    other.field = nullptr;

}

void GameField::deleteObject(int x, int y) {

    if (field[y][x]) {
        objectsCount--;
        delete field[y][x];
        field[y][x] = nullptr;
    }
}

void GameField::addObject(Unit *object, int x, int y) {

    bool isInBorder = x < fieldWidth && y < fieldHeight && x >= 0 && y >= 0;

    if (isInBorder && !field[y][x] && objectsCount < maxObjectsCount && !object->isOnField){

        field[y][x] = object;
        objectsCount++;
        object->position = Point(x, y);

    } else{

        std::cout << "Impossible to add Object " << object << " to field." << std::endl;

    }
}

void GameField::deleteObject(Unit *object) {

    deleteObject(object->position.x, object->position.y);

}

void GameField::moveObject(const Point &p1, const Point &p2) {

    if (field[p1.y][p1.x] && !field[p2.y][p2.x]){

        field[p2.y][p2.x] = field[p1.y][p1.x];
        field[p2.y][p2.x]->position = p2;

        field[p1.y][p1.x] = nullptr;

    } else{

        std::cout << "Impossible to move object. Coord " << p1.x << ' ' << p2.y << " is empty";

    }

}

void GameField::moveObject(Unit *object, const Point &p2) {

    Point p1 = object->getPosition();
    moveObject(p1, p2);

}

void GameField::deleteObject(const Point &point) {

    deleteObject(point.x, point.y);

}

int GameField::getHeight() const{
    return fieldHeight;
}

int GameField::getWidth() const{
    return fieldWidth;
}

Unit *GameField::getObject(const Point &p) const{

    if (p.x < fieldWidth && p.y < fieldHeight)
        return field[p.y][p.x];
    return nullptr;

}

GameField::~GameField() {

    for (int i=0; i<fieldHeight; i++){
        delete []field[i];
    }

    delete []field;

}
