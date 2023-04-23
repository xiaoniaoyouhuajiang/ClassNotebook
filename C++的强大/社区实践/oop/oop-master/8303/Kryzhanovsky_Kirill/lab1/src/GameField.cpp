//
// Created by therealyou on 11.02.2020.
//
/**
 * Игровое поле является контейнером для объектов представляющим прямоугольную сетку.
 * Основные требования к классу игрового поля:
 * Создание поля произвольного размера
 * Контроль максимального количества объектов на поле
 * Возможность добавления и удаления объектов на поле
 * Возможность копирования поля (включая объекты на нем)
 * Для хранения запрещается использовать контейнеры из stl
 * */

#include "GameField.h"

GameField::GameField() {
    std::cout << "Creating default field" << std::endl;
    setWidth(DEFAULT_X);
    setHeight(DEFAULT_Y);
    setCountUnits();
    setMatrix();
}

GameField::GameField(int x, int y) {
    setWidth(x);
    setHeight(y);
    setCountUnits();
    setMatrix();
}

GameField::GameField(const GameField* gameField) {
    setWidth(gameField->width);
    setHeight(gameField->height);
    setCountUnits();
    setMatrix(gameField->matrix);
}

void GameField::setMatrix() {
    matrix = new baseType*[height];
    for (int i = 0; i < height; i++){
        matrix[i] = new baseType[width];
    }
//    for (int i = 0; i < height; i++){
//        for (int j = 0; j < width; j++){
//            matrix[i][j].valueAsChar = DEFAULT_VALUE;
//        }
//    }
}

void GameField::setMatrix(baseType** matrix) {
    this->matrix = new baseType*[height];
    for (int i = 0; i < height; i++){
        this->matrix[i] = new baseType[width];
    }
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            this->matrix[i][j] = matrix[i][j];
        }
    }
}

void GameField::setWidth(int width) {
    this->width = width;
}

void GameField::setHeight(int height) {
    this->height = height;
}

void GameField::setCountUnits() {
    this->maxCountUnits = height * width;
}


int GameField::addUnit(Unit* unit, int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height){
        std::cerr << "\t\tWrong coords to add" << std::endl;
        return 1;
    }
    if (countUnits == maxCountUnits){
        std::cerr << "\t\tHas reached total count of units" << std::endl;
        return 2;
    }
    if (!unit->isCanAdded()){
        std::cerr << "\t\tThis unit has been added early" << std::endl;
        return 3;
    }
    if (matrix[y][x].valueAsChar != DEFAULT_VALUE){
        std::cerr << "\t\tThis place is not free" << std::endl;
        return 4;
    }
    unit->addUnit();
    unit->setX(x);
    unit->setY(y);
    unit->setGameField(this);
    matrix[y][x].valueAsChar = unit->getId();
    matrix[y][x].unit = unit;

    countUnits++;
//    std::cout << matrix[y][x] << std::endl;
//    std::cout << matrix[y][x] << std::endl;
//    this->printField();
    return 0;
}

void GameField::deleteUnit(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height){
        std::cerr << "\t\tWrong coords to delete" << std::endl;
        return;
    }
    if (matrix[y][x].valueAsChar != DEFAULT_VALUE){
        matrix[y][x].valueAsChar = DEFAULT_VALUE;
        countUnits--;
    } else {
        std::cerr << "\t\tThis place is free" << std::endl;
        return;
    }
}

void GameField::printField() {
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            std::cout << matrix[i][j].valueAsChar << " ";
        }
        std::cout << std::endl;
    }
}

void GameField::move(Unit* unit, int dx, int dy) {
    unit->deleteUnit();
    int res = this->addUnit(unit, unit->getX() + dx, unit->getY() + dy);
    if (res != 0){
        std::cerr << "\t\tCan not move unit to another place" << std::endl;
        unit->addUnit();
        return;
    }
    this->deleteUnit(unit->getX() - dx, unit->getY() - dy);
}

/**
 * Игровое поле является контейнером для объектов представляющим прямоугольную сетку.
 * Основные требования к классу игрового поля:
 *
 + Создание поля произвольного размера
 + Контроль максимального количества объектов на поле
 + Возможность добавления и удаления объектов на поле
 * Возможность копирования поля (включая объекты на нем)
 + Для хранения запрещается использовать контейнеры из stl
 * */