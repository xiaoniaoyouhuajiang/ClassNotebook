#pragma once

#include <vector>
#include <fstream>
#include "Cell.h"
#include "Trivia/Snapshot.h"

#define MIN_FIELD_SIZE 20
#define MAX_UNIT_COUNT_ON_FIELD 200

class Field
{
    friend class GameFacade;
    friend class RoutePlotter;

public:
    class FieldSnapshot;
    FieldSnapshot getSnapshot();

    Field() = delete;
    Field(uint16_t width, uint16_t height, uint16_t landscapeType);
    Field(uint16_t width, uint16_t height, std::vector<std::vector<uint16_t>> parameters);
    Field(FieldSnapshot& snapshot);
    ~Field();

    Field(const Field& field);
    Field& operator=(Field& field);
    Field(Field&& field);
    Field& operator=(Field&& field);

    uint16_t getWidth();
    uint16_t getHeight();

    ILandscape* getLandscape(Point point);

    int setUnit(Point point, IUnit* unit);
    IUnit* getUnit(Point point);
    void removeUnit(Point point);

    int setBase(Point point, Base* base);
    Base* getBase(Point point);
    void removeBase(Point point);

    int setContext(Point point, NeutralContext* context);
    NeutralContext* getContext(Point point);

    bool isUnitFree(Point point);
    bool isBuildingFree(Point point);
    uint16_t getBuildingGroupType(Point point);

    bool isBelowMaxUnitCount();

    class Iterator;
    Iterator begin();
    Iterator end();

private:
    Cell* getCell(Point point);

private:
    uint16_t width;
    uint16_t height;
    Cell** cellArray;

    uint16_t maxUnitCoint;
    uint16_t unitCount;
};


class Field::Iterator
{
public:
    Iterator(Field* field, Cell* cell);

    Cell& operator*();
    Cell* operator->();

    friend bool operator== (const Field::Iterator& iter1, const Field::Iterator& iter2);
    friend bool operator!= (const Field::Iterator& iter1, const Field::Iterator& iter2);

    Cell& operator++();
    Cell& operator++(int);
    Cell& operator--();
    Cell& operator--(int);

    Cell& operator+=(int n);
    Cell& operator-=(int n);

    Cell& operator+(int n);
    Cell& operator-(int n);

private:
    Field* field;
    Cell* cell;
};


class Field::FieldSnapshot : public Snapshot {
    friend class Field;

public:
    FieldSnapshot(Field& field);
    FieldSnapshot(std::ifstream& stream);
    friend std::ofstream& operator<<(std::ofstream& stream, const Field::FieldSnapshot& snapshot);

private:
    uint16_t width;
    uint16_t height;
    std::vector<std::vector<uint16_t>> landscapes;
};
