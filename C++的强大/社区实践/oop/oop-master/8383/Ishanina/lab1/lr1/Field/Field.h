//
// Created by Mila
//

#ifndef UNTITLED_FIELD_H
#define UNTITLED_FIELD_H


#include "../Units/Unit.h"

class Field {
private:
    unsigned height;
    unsigned width;
    unsigned controlMax;
    unsigned countObjects;
    int flag;

    ObjectInterface** *obj;

public:

    Field(unsigned height, unsigned width, unsigned controlMax);

    Field(Field &field);

    Field(Field &&field);//перемещение

    void move(int x, int y, int newX, int newY);

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

    Field &operator=(Field &&field) {

        if (&field == this)
            return *this;
        for (int i = 0; i < this->width; i++) {
            delete [] this->obj[i];
            for (int j = 0; j < this->height; j++) {
                delete &this->obj[i][j];
            }
        }
        delete [] this->obj;

        this->height = field.height;
        this->width = field.width;

        this->obj = field.obj;
        return *this;
    }

    unsigned getHeight() const;

    unsigned getWidth() const;

    void drawField();

    void deleteUnit(unsigned newX, unsigned newY);

    void appendUnit(unsigned newX, unsigned newY, ObjectInterface *unit);
};


#endif //UNTITLED_FIELD_H
