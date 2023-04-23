//
// Created by Mila on 23.02.2020.
//

#include <iostream>
#include "Field.h"

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
void Field::appendUnit(unsigned newX, unsigned newY, ObjectInterface *unit) {

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

    if (newX <= width && newY <= height) {
        countObjects--;
        obj[newX][newY] = nullptr;
    }


}

//----------------------------------- Передвижение юнита --------------------------------//
void Field::move( int x, int y, int newX, int newY)
{
    if (newX <= width && newY <= height)//проверка, что в пределах поля
    {
        if(obj[newX][newY] == nullptr) //проверка, что там никто не стоит
        {
            obj[newX][newY] = obj[x][y];
            obj[x][y] = nullptr;
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
                    obj[i][j]->whatYouName();
                    std::cout << '|';
                }
                else
                    {
                    std::cout << " ";
                    std::cout << '|';
                    }
            }
            std::cout << std::endl;
        }
        for (int k = 0; k < width * 2 + 1; k++)
            std::cout << '-';
        std::cout << std::endl;
    }

}


//----------------------------------- Конструктор перемещения --------------------------------//
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

    for (int i = 0; i < this->width; i++) {
        delete [] this->obj[i];
    }
    delete [] this->obj;
}






