//
// Created by Artem Butko on 14/05/2020.
//

#include "Field.h"

Field::Field(int height, int width)
{
    this->height = height;
    this->width = width;
    this->objCount = 0;
    this->objLimit = width * height;
    field = new Tale*[height];
    for (int i = 0; i < height; ++i)
        field[i] = new Tale[width];
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
        {
            field[i][j].object = nullptr;
            field[i][j].x = i;
            field[i][j].y = j;
        }
}

Field::Field(const Field &other)
{
    height = other.height;
    width = other.width;
    objLimit = other.objLimit;
    objCount = other.objCount;

    field = new Tale*[height];
    for (int i = 0; i < height; ++i)
        field[i] = new Tale[width];

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            field[i][j] = other.field[i][j];
}

Field::Field(Field&& other)
{
    height = other.height;
    width = other.width;
    objLimit = other.objLimit;
    objCount = other.objCount;

    field = new Tale*[height];
    for (int i = 0; i < height; ++i)
        field[i] = new Tale[width];

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            field[i][j] = other.field[i][j];

    for (int i = 0; i < other.height; ++i)
        delete[] other.field[i];
    delete[] other.field;
}

int Field::addObject(Object *object, int x, int y)
{
    if (objCount > objLimit)
    {
        std::cout << "ERROR: limit of objects on the field is exceeded!" << std::endl;
        return 1;
    }
    if (field[x][y].object != nullptr)
    {
        std::cout << "ERROR: this tale is not empty!" << std::endl;
        return 1;
    }

    field[x][y].object = object;
    field[x][y].x = x;
    field[x][y].y = y;

    objCount++;
    return 0;
}

int Field::moveObject(int x, int y, int i, int j)
{
    /*TODO выход за границы поля*/
    if (field[x][y].object != nullptr && field[i][j].object == nullptr)
    {
        field[i][j].object = field[x][y].object;
        field[x][y].object = nullptr;
    }
    else
    {
        std::cout << "ERROR: impossible to move!" << std::endl;
        return 1;
    }
    return 0;
}

int Field::deleteObject(int x, int y)
{
    if (field[x][y].object != nullptr)
    {
        field[x][y].object = nullptr;
        objCount --;
    }
    else
    {
        std::cout << "ERROR: impossible to delete!" << std::endl;
        return 1;
    }
    return 0;
}

void Field::show()
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (field[i][j].object == nullptr) std::cout << "[ ]";
            else std::cout << "[" << field[i][j].object->id<< "]";
        }
        std::cout << std::endl;
    }
}

Field::~Field()
{
    for (int i = 0; i < height; ++i)
        delete[] field[i];
    delete[] field;
}

FieldIterator *Field::iterator()
{
    return (new FieldIterator(*this));
}

FieldIterator *Field::end() {
    auto* end = new FieldIterator(*this);
    end->end();
    return end;
}

FieldIterator* Field::begin() {
    auto* begin = new FieldIterator(*this);
    begin->begin();
    return begin;
}




