//
// Created by max on 19.02.20.
//

#ifndef OOP_FIELD_H
#define OOP_FIELD_H

#include "Unit.h"
#include "Landscape.h"
#include "Object.h"
#include "NeutralObject.h"
#include <vector>
#include "Water.h"
#include "Mountain.h"
#include "Forest.h"
#include "Plain.h"
#include "Hospital.h"
#include "WorkShop.h"
#include "PublicHouse.h"
#include "Bar.h"
#include "Log.h"
#include <map>

using std::vector;
using std::pair;
using std::map;

class Base;

class Cell{
    bool occupied_by_unit = false;
    bool occupied_by_building = false;
    bool occupied_by_base = false;
    Landscape* land;
    Unit* unit;
    NeutralObject* neutral_object;
    Base* base;
    string object_name;
public:
    bool getIfOccupiedByUnit();
    bool getIfOccupiedByBuilding();
    bool getIfOccupiedByBase();
    Unit* getUnit();
    Landscape* getLandscape();
    NeutralObject* getNeutralObject();
    Base* getBase();
    void setOccupiedByUnit(bool flag);
    void setOccupiedByBuilding(bool flag);
    void setOccupiedByBase(bool flag);
    void setElement(Unit* unit);
    void setLandscape(int id,int x,int y);
    void arrangeCavalryToIntantry();
    void setNeutralObject(int id,int x,int y);
    void setBase(int x,int y,int id);
    void setUnit(Unit* unit);
};

class Field {
    int x_size;
    int y_size;
    int number_of_objects = 0;
    int max_number_of_objects;
    int number_of_bases = 0;
    Log* game_report;
    vector<pair<int,int>> unit_coordinates;
    vector<pair<int,int>> base_coordinates;
    vector<pair<int,int>> neutral_objects_coordinates;
    map<int,string> convert_landscape_id;
    map<string,int> convert_landscape_name;
    map<int,string> convert_neutral_object_id;
    map<string,int> convert_neutral_object_name;
public:
    Cell** field;
    Field(int max_number_of_objects=10,int x_size=0, int y_size=0)
    {
        if(x_size <= 0 || y_size <= 0){
            cout << "Некорректные размеры поля\n";
            return;
        }
        this->x_size = x_size;
        this->y_size = y_size;
        this->max_number_of_objects = max_number_of_objects;
        this->field = new Cell*[this->x_size];
        for(int i = 0;i < this->x_size;i++) {
            this->field[i] = new Cell[y_size];
        }
        this->convertLandcape();
        this->initializeLandscape();
        this->convertNeutralObject();
        this->initializeNeutralObjects();
    }
    Field(const Field &other)
    {
        this->y_size = other.y_size;
        this->x_size = other.x_size;
        this->number_of_objects = other.number_of_objects;
        this->max_number_of_objects = other.max_number_of_objects;
        this->field = new Cell*[this->x_size];
        for(int i = 0;i < this->x_size;i++) {
            this->field[i] = new Cell[y_size];
            for(int j = 0;j < y_size;j++)
                this->field[i][j] = other.field[i][j];
        }
    }
    void operator = (const Field &other){
        for(int i = 0;i < this->x_size;i++)
            delete[] this->field[i];
        this->x_size = other.x_size;
        this->y_size = other.y_size;
        this->field = new Cell*[this->x_size];
        for(int i = 0;i < this->x_size;i++) {
            this->field[i] = new Cell[y_size];
            for (int j = 0; j < this->y_size; j++) {
                this->field[i][j] = other.field[i][j];
            }
        }
    }
    int getNumberOfUnits();
    int getXsize();
    int getYsize();
    int getNumberOfObjects();
    int getMaxNumberOfObjects();
    int getNumberOfBases();
    int getBaseXCoordinateById(int id);
    int getBaseYCoordinateById(int id);
    int getNeutralObjectXCoordinateById(int id);
    int getNeutralObjectYCoordinateById(int id);
    int getUnitXCoordinateById(int id);
    int getUnitYCoordinateById(int id);
    string getNeutralObjectName(int id);
    string getLandscapeName(int id);
    void addUnit(int x,int y,Unit* element);
    void deleteUnit(int x,int y);
    void printFieldSize();
    void move(int x_start,int y_start,int x_end,int y_end,bool& check);
    void printField();
    void increaseNumberOfObjects();
    void createBase(int x,int y);
    void increaseNumberOfBases();
    void destroyBase(int id);
    void initializeLandscape();
    void convertLandcape();
    void initializeNeutralObjects();
    void convertNeutralObject();
    void deleteUnitFromArray(int index);
    void deleteBaseFromArray(int index);
    void addUnitToArray(int x,int y);
    void decreaseNumberOfBases();
    void setLog(Log* game_report);
    void decreaseNumberOfObjects(int amount);
    Log* getLog();
    ~Field()
    {
        if(this->x_size <= 0 || this->y_size <= 0)
            return;
        for(int i = 0;i < this->x_size;i++)
            delete[] this->field[i];
    }
};

#endif //OOP_FIELD_H
