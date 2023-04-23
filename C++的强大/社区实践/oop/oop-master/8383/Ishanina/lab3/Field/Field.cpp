//
// Created by Mila on 23.02.2020.
//

#include <iostream>
#include "Field.h"
#include "../Units/Artillerist/Archer.h"
#include "../Units/Artillerist/Magician.h"
#include "../Units/Cavalryman/ElfOnUnicorn.h"
#include "../Units/Cavalryman/KnightOnHorse.h"
#include "../Units/Infantryman/Gnome.h"
#include "../Units/Infantryman/Knight.h"
#include "../LandscapeFactory/LandscapeFactory.h"
#include "../NeutralObject/Strategy.h"
#include "../Landscape/ProxyLandscape.h"
#include "../Base/Base.h"
#include "../NeutralObject/Stone.h"

unsigned Field::getHeight() const {
    return height;
}


unsigned Field::getWidth() const {
    return width;
}



//----------------------------------- Конструктор --------------------------------//
Field::Field(unsigned height, unsigned width, unsigned controlMax)
        : width(width), height(height), controlMax(controlMax) {
    countObjects = 0;
    flag = 0;
    setLandscapesOnField();
    setNeutralObjectOnField();
    if(height < 3 || width < 3)
    {
        std::cout << "Error! Invalid field size!" << std::endl;
        flag = 1;
    }
    if (flag == 0)
    {
        obj = new ObjectInterface **[width];
        for (int i = 0; i < width; i++)
        {
            obj[i] = new ObjectInterface *[height];
            for (int j = 0; j < height; j++)
            {
                obj[i][j] = nullptr;
            }

        }
    }
}

//----------------------------------- Добавление юнита --------------------------------//
void Field::appendElement(unsigned newX, unsigned newY, ObjectInterface *unit) {

    if(!flag)
    {
        if (countObjects < controlMax && newX <= width && newY <= height)
        {
            if(obj[newX][newY] == nullptr)
            {
                countObjects++;
                obj[newX][newY] = unit;

            }
        }
    }

}

//----------------------------------- Удаление юнита --------------------------------//
void Field::deleteUnit(unsigned newX, unsigned newY) {

    if (dynamic_cast<Unit *>(obj[newX][newY]) != nullptr) {

        if (newX <= width && newY <= height) {
            //std::cout << "deleteUnit    x=" << newX << "  y=" << newY << std::endl;
            if(dynamic_cast<Archer *>(obj[newX][newY]) != nullptr) {
                auto *archer = dynamic_cast<Archer *>(obj[newX][newY]);
                delete archer;
            }
            else if(dynamic_cast<Magician *>(obj[newX][newY]) != nullptr) {
                auto *magician = dynamic_cast<Magician *>(obj[newX][newY]);
                delete magician;
            }
            else if(dynamic_cast<ElfOnUnicorn *>(obj[newX][newY]) != nullptr) {
                auto *elfOnUnicorn = dynamic_cast<ElfOnUnicorn *>(obj[newX][newY]);
                delete elfOnUnicorn;
            }
            else if(dynamic_cast<KnightOnHorse *>(obj[newX][newY]) != nullptr) {
                auto *knightOnHorse = dynamic_cast<KnightOnHorse *>(obj[newX][newY]);
                delete knightOnHorse;
            }
            else if(dynamic_cast<Gnome *>(obj[newX][newY]) != nullptr) {
                auto *gnome = dynamic_cast<Gnome *>(obj[newX][newY]);
                delete gnome;
            }
            else if(dynamic_cast<Knight *>(obj[newX][newY]) != nullptr) {
                auto *knight = dynamic_cast<Knight *>(obj[newX][newY]);
                delete knight;
            }
            //delete obj[newX][newY];
            countObjects--;
            obj[newX][newY] = nullptr;
        }


    }

}
//----------------------------------- Передвижение юнита --------------------------------//
void Field::move( int x, int y, int newX, int newY)
{
    if (newX <= width && newY <= height)//проверка, что в пределах поля
    {
        if(obj[newX][newY] == nullptr && dynamic_cast<Base*>(obj[newX][newY]) == nullptr) //проверка, что там никто не стоит
        {
            auto *unit = dynamic_cast<Unit *>(obj[x][y]);

            if(neutralobject[newX][newY] != nullptr)///ИСПОЛЬЗУЕТСЯ ПАТТЕРН СТРАТЕГИЯ
            {

                Strategy client;
                client.setStrategy(neutralobject[newX][newY]);
                client.useStrategy(unit);

            }
            if( neutralobject[newX][newY] == nullptr ||(neutralobject[newX][newY] != nullptr && neutralobject[newX][newY]->canStepOnIt())) {
                //landscapes[newX][newY]->updateUnitHealth(unit->getHealthForUpdate());
                ProxyLandscape proxyLandscape(dynamic_cast<Landscape*>(landscapes[newX][newY]));
                proxyLandscape.updateUnitHealth(unit->getHealthForUpdate());
                if (unit->getHealth() <= 0) {
                    deleteUnit(x, y);
                }

                obj[newX][newY] = obj[x][y];
                obj[x][y] = nullptr;
            }
        }


    }
}

//----------------------------------- Вывод поля --------------------------------//
void Field::drawField() {
    if(!flag)
    {
        for (int k = 0; k < width * 2 + 1; k++)
            std::cout << '-';
        std::cout << std::endl;
        for (int i = 0; i < width; ++i)
        {
            std::cout << '|';
            for (int j = 0; j < height; ++j)
            {
                if (obj[i][j] != nullptr)
                {
                    std::cout << obj[i][j]->whatYouName();
                    std::cout << ',';
                    std::cout<< landscapes[i][j]->whatYouName();
                    std::cout << ',';
                    if(neutralobject[i][j] == nullptr)
                    {
                        std::cout<< ' ';
                    }
                    else
                        std::cout << neutralobject[i][j]->whatYouName();
                    std::cout << '|';
                }
                else
                {


                    std::cout << " ";
                    std::cout << ',';
                    std::cout<< landscapes[i][j]->whatYouName();
                    std::cout << ',';
                    if(neutralobject[i][j] == nullptr)
                    {
                        std::cout<< ' ';
                    }
                    else
                        std::cout << neutralobject[i][j]->whatYouName();
                    std::cout << '|';

                    //std::cout << " ";
                    //std::cout << ',';
                    //std::cout<< neutralobject[i][j]->whatYouName();
                    //std::cout << '|';
                }
            }
            std::cout << std::endl;
        }
        for (int k = 0; k < width * 2 + 1; k++)
            std::cout << '-';
        std::cout << std::endl;
    }

}

Field::Field(Field &&field)//конструктор перемещения
    :width(field.width), height(field.height), obj(field.obj), controlMax(field.controlMax), countObjects(field.countObjects)
{
field.obj = nullptr;
field.width = 0;
field.height = 0;
}

//----------------------------------- Конструктор копирования --------------------------------//
Field::Field(Field &field)
    : height(field.height), width(field.width), controlMax(field.controlMax), countObjects(field.countObjects), flag(field.flag){

    obj = new ObjectInterface **[width];
    for (int i = 0; i < width; i++)
    {
        obj[i] = new ObjectInterface *[height];
        for (int j = 0; j < height; j++)
        {
            obj[i][j] = nullptr;
        }

    }

    for (int k = 0; k < width; ++k)
    {
        for (int i = 0; i < height; ++i)
        {
            obj[k][i] = field.obj[k][i];
        }
    }
}



//----------------------------------- Деструктор --------------------------------//
Field::~Field() {

    for (int i = 0; i < height; ++i) {
        delete (obj[i]);
    }

    delete (obj);

    delete landscapes;
}

unsigned int Field::getControlMax() const {
    return controlMax;
}

void Field::setLandscapesOnField() {


    landscapes = new LandscapeInterface **[width];
    for (int i = 0; i < width; i++)
    {
        landscapes[i] = new LandscapeInterface *[height];
        for (int j = 0; j < height; j++)
        {
            landscapes[i][j] = landscapeFactory.getLandscapeGlade();
        }

    }
    /*for (int i = 0; i <width ; i++) {
        for (int j = 0; j < height ; j++) {
            landscapes[i][j] = landscapeFactory.getLandscapeGlade();
        }
    }*/

    landscapes[5][6] = landscapeFactory.getLandscapeAbyss();
    landscapes[width-1][height-1] = landscapeFactory.getLandscapeSwamp();
}

void Field::setNeutralObjectOnField(){
    neutralobject = new NeutralObjectInterface **[width];
    for (int i = 0; i < width; i++)
    {
        neutralobject[i] = new NeutralObjectInterface *[height];
        for (int j = 0; j < height; j++)
        {
            neutralobject[i][j] = nullptr;
        }

    }
}
void Field::addNeutralObject(unsigned newX, unsigned newY, NeutralObjectInterface* neutral)
{
    if (newX <= width && newY <= height)
    {
        if(neutralobject[newX][newY] == nullptr)
        {
            //countObjects++;
            neutralobject[newX][newY] = neutral;

        }
    }
}

Unit *Field::getUnit(int x, int y) {
    return dynamic_cast<Unit *>(obj[x][y]);
}

void Field::attack(int x1, int y1, int x2, int y2) {
    auto *unit1 = dynamic_cast<Unit *>(obj[x1][y1]);
    auto *unit2 = dynamic_cast<Unit *>(obj[x2][y2]);
    unit1->attack(unit2);
}








