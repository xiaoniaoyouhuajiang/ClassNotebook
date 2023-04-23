//
// Created by anton on 5/10/20.
//

#ifndef OOPROJECT_FIELD_H
#define OOPROJECT_FIELD_H

#include <memory>
#include <cassert>
#include "Cell.h"

class Field {
    friend class Mediator;
public:
    Field(int objLimit, int height, int width);

    Field(const Field &src);

    Field &operator=(Field &&other);

    std::shared_ptr<Unit> getUnitAt(int x, int y);
    void setUnitAt(std::shared_ptr<Unit> unit, int x, int y);


    std::shared_ptr<TerrainProxy> getTerrainAt(int x, int y);
    void setTerrainAt(std::shared_ptr<TerrainProxy> terrain, int x, int y);

    std::shared_ptr<Entity> getEntityAt(int x, int y);
    void setEntityAt(std::shared_ptr<Entity> entity, int x, int y);

    void onLimitExceeded();

    bool objSwap(int x1, int y1, int x2, int y2);



    std::wstring toWString();

private:
    Cell** content;
    int objLimit;
    int objCnt;
    int height;
    int width;

public:
    class iterator{
    public:
        iterator(int x, int y, Field *collection);

        bool operator==(const iterator &rhs) const;

        bool operator!=(const iterator &rhs) const;

        iterator operator++();
        iterator& operator++(int);

        Cell& operator*() const;

        iterator& next();
        bool hasNext();

    private:
        Field* collection;
        int x;
        int y;
    };

    iterator begin();
    iterator end();


};


#endif //OOPROJECT_FIELD_H
