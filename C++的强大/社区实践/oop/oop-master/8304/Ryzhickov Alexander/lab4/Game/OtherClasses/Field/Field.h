//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_FIELD_H
#define GAME_FIELD_H


#include "../GameCell/GameCell.h"
#include "../Factories/LandscapeFactory.h"

class Field {
private:
    const int height;
    const int width;
    const int maxCountUnits;
    int countUnits;
    GameCell **cells;
    LandscapeFactory *landscapeFactory;
public:
    class Iterator;

    Iterator begin() {
        return &cells[0];
    }

    Iterator end() {
        return &cells[height-1][width-1] ;
    }

    int getWidth() const;

    int getHeight() const;

    int getMaxCountUnits() const;

    int getCountUnits() const;

    void appendUnits(int x, int y, Unit *unit);

    void deleteUnits(int x, int y);

    void setBase(int x,int y,Base *base);

    GameCell *getCell(int x, int y);

public:
    Field(int width2, int height2, int maxCountUnits);

    ~Field();

    Field(const Field &field);

    Field &operator=(const Field &field) {
        if (this == &field)
            return *this;

        for (int i = 0; i < height; i++) {
            delete (Field::cells[i]);
        }
        delete (cells);

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


        return *this;
    }

    class Iterator {
    private:
        GameCell **iteratorGameCell;
        int count;
        int my_Width;
    public:


        Iterator(GameCell **gameCell) {
            iteratorGameCell = gameCell;
            count = 0;
            my_Width = 10;
        };

        GameCell &operator+(int number) {
            count = count + number;
            return *(iteratorGameCell[count % my_Width] + count / my_Width);
        };

        GameCell &operator-(int number) {
            count = count - number;
            return *(iteratorGameCell[count % my_Width] + count / my_Width);

        };

        GameCell &operator++() {
            count++;
            return *(iteratorGameCell[count % my_Width] + count / my_Width);

        };

        GameCell &operator--() {
            count--;
            return *(iteratorGameCell[count % my_Width] + count / my_Width);

        };

        GameCell &operator*() {
            return *(iteratorGameCell[count % my_Width] + count / my_Width);

        };

        bool operator!=(const Iterator &it) {
            // return count != it.count;
            return (iteratorGameCell[count % my_Width] + count / my_Width) != (it.iteratorGameCell[it.count % my_Width] + it.count / my_Width);
        }

        bool operator==(const Iterator &it) {
            return (iteratorGameCell[count % my_Width] + count / my_Width) == (it.iteratorGameCell[it.count % my_Width] + it.count / my_Width);
        };

        /*GameCell begin() {
            return *(iteratorGameCell[count / my_Width] + count / my_Width);
        }

        GameCell end() {
            return *(iteratorGameCell[count / my_Width] + count / my_Width);
        }*/
        Iterator(GameCell *cell) {
            iteratorGameCell = &cell;
            count = 0;
            my_Width = 10;
        }
    };


    void setUnit(int x,int y,Unit *unit);
    void updateUnitPosition(int lastX,int lastY, int newX,int newY);
};


#endif //GAME_FIELD_H
