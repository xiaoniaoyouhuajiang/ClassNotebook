//
// Created by therealyou on 11.02.2020.
//
/**
 * Юнит является объектов, размещаемым на поля боя. Один юнит представляет собой отряд.
 *
 * Основные требования к классам юнитов:
 * Все юниты должны иметь как минимум один общий интерфейс
 * Реализованы 3 типа юнитов (например, пехота, лучники, конница)
 * Реализованы 2 вида юнитов для каждого типа(например, для пехоты могут быть созданы мечники и копейщики)
 * Юниты имеют характеристики, отражающие их основные атрибуты, такие как здоровье, броня, атака.
 * Юнит имеет возможность перемещаться по карте
 * */
#ifndef LAB1_UNIT_H
#define LAB1_UNIT_H
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ctime>
#include "GameField.h"

#define SCATTER 0.0 // разброс [0, 1) | элемент случайности

class GameField;

class Unit {
protected:
    GameField* gameField = nullptr;

    // coords
    int x;
    int y;

    // attributes
    int speed;
    double health;
    double armor;
    double damage;

    bool canAdded = true;

    double deltaAttribute(double attribute);
    double minAttribute(double attribute);

public:
    Unit(int speed, int armor, int damage, int health);

    virtual char getId() = 0;

    void addUnit();
    void deleteUnit();

    bool isCanAdded() const;

    double getSpeed() const;
    double getHealth() const;
    double getArmor() const;
    double getDamage() const;

    void setSpeed(int speed);
    void setHealth(int health);
    void setArmor(int armor);
    void setDamage(int damage);

    GameField *getGameField() const;

    void setGameField(GameField *gameField);

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    void print();

    void move(int dx, int dy);
};


#endif //LAB1_UNIT_H
