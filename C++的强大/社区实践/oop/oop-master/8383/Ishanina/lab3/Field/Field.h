//
// Created by Mila on 23.02.2020.
//

#ifndef UNTITLED_FIELD_H
#define UNTITLED_FIELD_H


#include "../Units/Unit.h"
#include "../Landscape/LandscapeInterface.h"
#include "../LandscapeFactory/LandscapeFactory.h"
#include "../NeutralObject/NeutralObjectInterface.h"


class Field {
private:
    unsigned height;
    unsigned width;
    unsigned controlMax;
public:
    unsigned int getControlMax() const;

    void setNeutralObjectOnField();

private:
    unsigned countObjects;
    int flag;
    void setLandscapesOnField();

    LandscapeFactory landscapeFactory;
    NeutralObjectInterface** *neutralobject;
    LandscapeInterface** *landscapes;
    ObjectInterface** *obj;

public:

    //int countBase;
    Field(unsigned height, unsigned width, unsigned controlMax);

    Unit* getUnit(int x, int y);//метод, который возвращает с поля юнита
    Field(Field &field);


    Field(Field &&field);//перемещение объекта

    void addNeutralObject(unsigned int newX, unsigned int newY, NeutralObjectInterface *neutral);
    void move(int x, int y, int newX, int newY);
    void attack(int x1, int y1, int x2, int y2);
    //void createBase();

    ~Field();

    Field &operator=(const Field &field) {          //оператор копирования
        // Проверка на самоприсваивание
        if (&field == this)
            return *this;
        // Удаляем всё, что может хранить указатель до этого момента
        for (int i = 0; i < height; ++i) {
            delete (obj[i]);
        }
        delete (obj);
        // Копируем передаваемый объект
        obj = new ObjectInterface **[width];
        for (int i = 0; i < width; i++) {
            obj[i] = new ObjectInterface *[height];
            for (int j = 0; j < height; j++) {
                obj[i][j] = nullptr;
            }
        }
        for (int k = 0; k < width; ++k) {
            for (int i = 0; i < height; ++i) {
                obj[k][i] ->copy();
            }
        }
        return *this;
    }

//--------------------------------- Опреатор перемещения ------------------------------------//

    Field &operator=(Field &&field) {////////////////////////////////////////////////

        if (&field == this)
            return *this;
        for (int i = 0; i < this->width; i++) {
            delete (obj[i]);
            for (int j = 0; j < this->height; j++) {
                delete &this->obj[i][j];
            }
        }
        delete this->obj;

        this->height = field.height;
        this->width = field.width;

        this->obj = field.obj;
        return *this;
    }

    unsigned getHeight() const;

    unsigned getWidth() const;

    void drawField();


    void deleteUnit(unsigned newX, unsigned newY);

    void appendElement(unsigned newX, unsigned newY, ObjectInterface *unit);

    //void kill


};


#endif //UNTITLED_FIELD_H
