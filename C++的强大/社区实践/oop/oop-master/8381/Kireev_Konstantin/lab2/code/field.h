#pragma once
#include <unitsinterface.h>
#include <cellInterface.h>
#include <stdexcept>
#include <iostream>

class Field
{
private:
    cellInterface*** fieldModel;
    friend class IteratorForField;
    //характеристики поля
    unsigned int NmRows;
    unsigned int NmColumns;
    unsigned int MaxObjects;
    unsigned int CurrObjects;

public:
    Field(unsigned int NmRows, unsigned int NmColumns, unsigned int MaxObjects); //конструктор класса
    Field(const Field& field); //конструктор копирования
    Field(Field&& field); //конструктор перемещения
    ~Field(); //деструктор

    unsigned int getNmRows() const; //получить количество рядов
    unsigned int getNmColumns() const; //получить количество столбцов
    unsigned int getMaxObjects() const; //получить максимальное количество объектов на поле

    void setMaxObjects(unsigned int maxObjectsNewValue); //установить максимальное количество объектов на поле
    void addObject(unsigned int Nrows, unsigned int Ncols, CreatureInterface *creature); //добавить объект на поле
    void removeObject(unsigned int Nrows, unsigned int Ncols); //удалить объект с поля
    void moveObject(unsigned int NrowFrom, unsigned int NcolFrom, unsigned int NrowTo, unsigned int NcolTo); //переместить объект
    void commitFight(unsigned int NrowFrom, unsigned int NcolFrom, unsigned int NrowTo, unsigned int NcolTo);

    cellInterface* getCell(unsigned int rowNumber, unsigned int columnNumber); //получить указатель на объект
    QString getStringInfo(int cols); //вывод информации о поле
};

class IteratorForField
{
private:
    Field* field;
    unsigned int x;
    unsigned int y;
    unsigned int maxX;
    unsigned int maxY;

public:
    IteratorForField(Field* fieldAttachedTo)
    {
        this->field = fieldAttachedTo;
        this->x = 0;
        this->y = 0;
        maxX = field->NmRows;
        maxY = field->NmColumns;
    }

    void reset()
    {
        x = 0;
        y = 0;
        std::cout << x << " " << y << std::endl;
    }

    void begin()
    {
        x = 0;
        y = 0;
        std::cout << x << " " << y << std::endl;
    }

    void end()
    {
        x = maxX;
        y = maxY;
        std::cout << x << " " << y << std::endl;
    }

    bool hasNext()
    {
        if(x < field->NmRows && y < field->NmColumns)
            return true;
        else
            return false;
    }

    cellInterface* getC()
    {
        if (hasNext() == false)
            return nullptr;
        cellInterface* cell = field->fieldModel[x][y];
        std::cout << x << " " << y << std::endl;
        return cell;
    }

    cellInterface* getNext()
    {
        cellInterface* cell = field->fieldModel[x][y];
        x++;
        if(x == field->NmRows)
        {
            x = 0;
            y++;
        }
        std::cout << x << " " << y << std::endl;
        return cell;
    }
};
