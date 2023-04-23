//
// Created by max on 19.02.20.
//

#include <iostream>
#include "Field.h"
#include "Cavalry.h"
#include "Infantry.h"
#include "Archer.h"
#include "Base.h"
using std::cin;
using std::cout;

Unit* Cell::getUnit() {
    return this->unit;
}

bool Cell::getIfOccupiedByUnit() {
    return this->occupied_by_unit;
}

bool Cell::getIfOccupiedByBuilding() {
    return this->occupied_by_building;
}

bool Cell::getIfOccupiedByBase() {
    return this->occupied_by_base;
}

void Cell::setOccupiedByUnit(bool flag) {
    this->occupied_by_unit = flag;
}

void Cell::setOccupiedByBuilding(bool flag) {
    this->occupied_by_building = flag;
}

void Cell::setOccupiedByBase(bool flag) {
    this->occupied_by_base = flag;
}

void Cell::setLandscape(int id,int x,int y) {
    switch (id){
        case 0:
            this->land = new Plain(x,y,id);
            break;
        case 1:
            this->land = new Forest(x,y,id);
            break;
        case 2:
            this->land = new Water(x,y,id);
            break;
        case 3:
            this->land = new Mountain(x,y,id);
            break;
        default:
            cout << "Неправильное id для ландшафта!!!\n";
    }
}

void Cell::setNeutralObject(int id, int x, int y) {
    switch (id){
        case 0:
            this->neutral_object = new Hospital(x,y,id);
            break;
        case 1:
            this->neutral_object = new WorkShop(x,y,id);
            break;
        case 2:
            this->neutral_object = new PublicHouse(x,y,id);
            break;
        case 3:
            this->neutral_object = new Bar(x,y,id);
            break;
        default:
            cout << "Неправильное id для объекта!!!\n";
    }
}

Landscape* Cell::getLandscape()  {
    return this->land;
}

NeutralObject* Cell::getNeutralObject() {
    return this->neutral_object;
}

Base* Cell::getBase() {
    return this->base;
}

void Cell::setElement(Unit* unit) {
    if(unit->getUnitType() == "Bowman")
        this->unit = new Bowman;
    if(unit->getUnitType() == "Crossbowman")
        this->unit = new Crossbowman;
    if(unit->getUnitType() == "Spearman")
        this->unit = new Spearman;
    if(unit->getUnitType() == "Swordsman")
        this->unit = new Swordsman;
    if(unit->getUnitType() == "LightCavalry")
        this->unit = new LightCavalry;
    if(unit->getUnitType() == "HardCavalry")
        this->unit = new HardCavalry;

    this->unit->operator=(*unit);
}

void Cell::setBase(int x, int y,int id) {
    this->base = new Base(x,y,id);
}

void Cell::arrangeCavalryToIntantry() {
    if(!this->getIfOccupiedByUnit())
        return;
    int prev_xp,prev_armour,prev_attack,max_attack,prev_id;
    prev_xp = this->unit->getXp();
    prev_armour = this->unit->getArmour();
    prev_attack = this->unit->getAttack();
    max_attack = this->unit->getMaxAttack();
    prev_id = this->unit->getId();
    if(this->unit->getUnitType() == "LightCavalry"){
        this->unit->cleanUnitMemory();
        this->unit = new Spearman;
        this->unit->setId(prev_id);
        this->unit->setParameters(prev_xp,prev_armour,prev_attack > max_attack ? max_attack : prev_attack,"Spearsman");
    } else
        if(this->unit->getUnitType() == "HardCavalry"){
            this->unit->cleanUnitMemory();
            this->unit = new Swordsman;
            this->unit->setParameters(prev_xp,prev_armour,prev_attack > max_attack ? max_attack : prev_attack,"Swordsman");
        }
}

void Cell::setUnit(Unit *unit) {
    this->unit = unit;
}

int Field::getNumberOfBases() {
    return this->number_of_bases;
}

int Field::getXsize() {
    return this->x_size;
}

int Field::getYsize() {
    return this->y_size;
}

int Field::getNumberOfObjects() {
    return this->number_of_objects;
}

int Field::getMaxNumberOfObjects() {
    return this->max_number_of_objects;
}

int Field::getBaseXCoordinateById(int id) {
    return this->base_coordinates[id].first;
}

int Field::getBaseYCoordinateById(int id) {
    return this->base_coordinates[id].second;
}

int Field::getNeutralObjectXCoordinateById(int id) {
    return this->neutral_objects_coordinates[id].first;
}

int Field::getNeutralObjectYCoordinateById(int id) {
    return this->neutral_objects_coordinates[id].second;
}

int Field::getUnitXCoordinateById(int id) {
    return this->unit_coordinates[id].first;
}

int Field::getUnitYCoordinateById(int id) {
    return this->unit_coordinates[id].second;
}

int Field::getNumberOfUnits() {
    return this->unit_coordinates.size();
}

string Field::getNeutralObjectName(int id) {
    return this->convert_neutral_object_id[id];
}

string Field::getLandscapeName(int id) {
    return this->convert_landscape_id[id];
}

void Field::increaseNumberOfBases() {
    this->number_of_bases++;
}

void Field::increaseNumberOfObjects() {
    this->number_of_objects++;
}

void Field::decreaseNumberOfObjects(int amount) {
    this->number_of_objects -= amount;
}

void Field::printFieldSize() {
    cout << " x " << this->x_size << " y " << this->y_size << "\n";
}

void Field::decreaseNumberOfBases() {
    this->number_of_bases--;
}

void Field::setLog(Log* game_report){
    this->game_report = game_report;
}

Log* Field::getLog() {
    return this->game_report;
}

void Field::convertLandcape() {
    this->convert_landscape_id[0] = "plain";
    this->convert_landscape_id[1] = "forest";
    this->convert_landscape_id[2] = "water";
    this->convert_landscape_id[3] = "mountain";
    for(auto it = convert_landscape_id.begin();it != convert_landscape_id.end();it++)
        convert_landscape_name[convert_landscape_id[it->first]] = it->first;
}

void Field::convertNeutralObject() {
    this->convert_neutral_object_id[0] = "hospital";
    this->convert_neutral_object_id[1] = "work_shop";
    this->convert_neutral_object_id[2] = "public_house";
    this->convert_neutral_object_id[3] = "bar";
    for(auto it = convert_neutral_object_id.begin();it != convert_neutral_object_id.end();it++)
        convert_neutral_object_name[convert_neutral_object_id[it->first]] = it->first;
}

void Field::deleteUnitFromArray(int index) {
    for(int i = index;i < base_coordinates.size();i++){
        this->field[unit_coordinates[i].first][unit_coordinates[i].second].getUnit()->setNumberInArray(this->field[unit_coordinates[i].first]
        [unit_coordinates[i].second].getUnit()->getNumberInArray() - 1);
    }
    this->unit_coordinates.erase(unit_coordinates.begin() + index);
}

void Field::move(int x_start,int y_start,int x_end, int y_end, bool& check) {
    if(x_start < this->x_size && y_start < this->y_size && x_end < this->x_size && y_end < this->y_size && x_start >= 0 && y_start >= 0 && x_end >= 0 && y_end >= 0){
        if(!this->field[x_start][y_start].getIfOccupiedByUnit()){
            this->getLog()->write("На этой клетке нету юнита,чтобы переместить\n");
            return;
        }
        if(!this->field[x_end][y_end].getIfOccupiedByUnit()){
            if(convert_landscape_id[this->field[x_end][y_end].getLandscape()->getObjectId()] == "water"){
                this->getLog()->write("На воду нельзя перемещаться!!!\n");
                return;
            }
            if((this->field[x_start][y_start].getUnit()->getUnitType() == "HardCavalry" || this->field[x_start][y_start].getUnit()->getUnitType() == "LightCavalry")
               && convert_landscape_id[this->field[x_end][y_end].getLandscape()->getObjectId()] == "mountain"){
                this->getLog()->write("Кавалерии в гору не подняться!!!\n");
                return;
            }
            if(this->field[x_end][y_end].getIfOccupiedByBase() && this->field[x_end][y_end].getBase()->getObjectId() !=
            this->field[x_start][y_start].getUnit()->getId()){
                this->getLog()->write("На чужую базу перемещаться нельзя!!!\n");
                return;
            }
            this->addUnit(x_end,y_end,this->field[x_start][y_start].getUnit());
            cout << this->field[x_end][y_end].getUnit()->getUnitType() << "\n";
            this->field[x_start][y_start].getUnit()->cleanUnitMemory();
            this->field[x_start][y_start].setOccupiedByUnit(false);
            this->field[x_end][y_end].setOccupiedByUnit(true);
            this->unit_coordinates[this->field[x_end][y_end].getUnit()->getNumberInArray()].first = x_end;
            this->unit_coordinates[this->field[x_end][y_end].getUnit()->getNumberInArray()].second = y_end;
            check = true;
            this->getLog()->write("Перемещение выполнено\n");
        } else
            this->getLog()->write("Эта клетка занята!!!\n");
    }
}

void Field::addUnit(int x, int y, Unit* warrior) {
    if(x >= this->x_size || y >= this->y_size){
        this->getLog()->write("Выход за пределы поля\n");
        return;
    }
    if(this->field[x][y].getIfOccupiedByUnit()){
        this->getLog()->write("Поле занято, добавлять нельзя\n");
    }
    if(this->number_of_objects + 1 > this->max_number_of_objects) {
        this->getLog()->write("Нельзя добавить, выход за максимальное значение\n");
        return;
    }
    this->field[x][y].setElement(warrior);
    this->field[x][y].setOccupiedByUnit(true);
    this->increaseNumberOfObjects();
}

void Field::addUnitToArray(int x,int y) {
    this->unit_coordinates.emplace_back(make_pair(x,y));
}

void Field::deleteUnit(int x, int y) {
    if(x < this->x_size && x >= 0 && y < this->y_size && y >= 0 && this->field[x][y].getIfOccupiedByUnit()) {
        this->field[x][y].getUnit()->cleanUnitMemory();
        this->field[x][y].setOccupiedByUnit(false);
        this->decreaseNumberOfObjects(1);
    } else
        this->getLog()->write("Координаты за пределв поля\n");
}

void Field::createBase(int x,int y) {
    if(!this->field[x][y].getIfOccupiedByBuilding()){
        this->base_coordinates.emplace_back(make_pair(x,y));
        this->field[x][y].setOccupiedByBase(true);
        this->field[x][y].setBase(x,y,this->getNumberOfBases());
        this->increaseNumberOfBases();
        this->increaseNumberOfObjects();
    } else
        this->getLog()->write("Место занято другим зданием\n");
}

void Field::destroyBase(int id) {
    this->field[this->base_coordinates[id].first][this->base_coordinates[id].second].setOccupiedByBase(false);
    delete this->field[this->base_coordinates[id].first][this->base_coordinates[id].second].getBase();
    this->deleteBaseFromArray(id);
    this->decreaseNumberOfBases();
    this->decreaseNumberOfObjects(1);
}

void Field::deleteBaseFromArray(int index) {
    this->base_coordinates.erase(this->base_coordinates.begin() + index);
}

void Field::printField() {
    bool check;
    for(int i = 0;i < this->x_size;i++){
        cout << "|";
        for(int j = 0;j < this->y_size;j++){
            check = false;
            cout << this->convert_landscape_id[this->field[i][j].getLandscape()->getObjectId()].substr(0,3)  << " ";
            for(int k = 0;k < neutral_objects_coordinates.size();k++) {
                if (neutral_objects_coordinates[k].first == i && neutral_objects_coordinates[k].second == j) {
                    cout << this->convert_neutral_object_id[this->field[i][j].getNeutralObject()->getObjectId()].substr(0,3);
                    check = 1;
                    break;
                }
            }
            for(int k = 0;k < this->base_coordinates.size();k++){
                if (base_coordinates[k].first == i && base_coordinates[k].second == j) {
                    cout << "Bas" << k + 1;
                    check = 1;
                    break;
                }
            }
            if(!check)
                cout << "   ";
            if(this->field[i][j].getIfOccupiedByUnit())
                cout << this->field[i][j].getUnit()->getNumberInArray() + 1 << "_" << this->field[i][j].getUnit()->getId() + 1 << " ";
            else
                cout << " ";
            cout << "|";
        }
        cout << "\n";
        for(int j = 0;j < this->y_size;j++)
            cout << "---------";
        cout << "\n";
    }
}

void Field::initializeLandscape() {
    int x,y;
    for(int k = 0;k < (this->x_size * this->y_size * 10 / 100);k++){
        while (1){
            x = rand() % this->x_size;
            y = rand() % this->y_size;
            if(this->field[x][y].getLandscape() == nullptr || this->field[x][y].getLandscape()->getXCoord() == -1){
                this->field[x][y].setLandscape(convert_landscape_name["mountain"],x,y);
                break;
            }
        }
    }
    for(int k = 0;k < (this->x_size * this->y_size * 10 / 100);k++){
        while (1){
            x = rand() % this->x_size;
            y = rand() % this->y_size;
            if(this->field[x][y].getLandscape() == nullptr || this->field[x][y].getLandscape()->getXCoord() == -1){
                this->field[x][y].setLandscape(convert_landscape_name["water"],x,y);
                break;
            }
        }
    }
    for(int k = 0;k < (this->x_size * this->y_size * 20 / 100);k++){
        while (1){
            x = rand() % this->x_size;
            y = rand() % this->y_size;
            if(this->field[x][y].getLandscape() == nullptr || this->field[x][y].getLandscape()->getXCoord() == -1){
                this->field[x][y].setLandscape(convert_landscape_name["forest"],x,y);
                break;
            }
        }
    }
    for(int k = 0;k < (this->x_size * this->y_size * 60 / 100);k++){
        while (1){
            x = rand() % this->x_size;
            y = rand() % this->y_size;
            if(this->field[x][y].getLandscape() == nullptr || this->field[x][y].getLandscape()->getXCoord() == -1){
                this->field[x][y].setLandscape(convert_landscape_name["plain"],x,y);
                break;
            }
        }
    }
    for(int i = 0;i < this->x_size;i++)
        for(int j = 0;j < this->y_size;j++)
            if(this->field[i][j].getLandscape() == nullptr || this->field[i][j].getLandscape()->getXCoord() == -1)
                this->field[i][j].setLandscape(convert_landscape_name["plain"],i,j);
}

void Field::initializeNeutralObjects() {
    int x,y;
    while (1){
        x = rand() % this->x_size;
        y = rand() % this->y_size;
        if(!this->field[x][y].getIfOccupiedByBuilding() && convert_landscape_id[this->field[x][y].getLandscape()->getObjectId()] != "mountain"
        && convert_landscape_id[this->field[x][y].getLandscape()->getObjectId()] != "water"){
            this->field[x][y].setNeutralObject(convert_neutral_object_name["hospital"],x,y);
            this->neutral_objects_coordinates.emplace_back(make_pair(x,y));
            this->field[x][y].setOccupiedByBuilding(true);
            break;
        }
    }
    while (1){
        x = rand() % this->x_size;
        y = rand() % this->y_size;
        if(!this->field[x][y].getIfOccupiedByBuilding() && convert_landscape_id[this->field[x][y].getLandscape()->getObjectId()] != "mountain"
        && convert_landscape_id[this->field[x][y].getLandscape()->getObjectId()] != "water"){
            this->field[x][y].setNeutralObject(convert_neutral_object_name["work_shop"],x,y);
            this->neutral_objects_coordinates.emplace_back(make_pair(x,y));
            this->field[x][y].setOccupiedByBuilding(true);
            break;
        }
    }
    while (1){
        x = rand() % this->x_size;
        y = rand() % this->y_size;
        if(!this->field[x][y].getIfOccupiedByBuilding() && convert_landscape_id[this->field[x][y].getLandscape()->getObjectId()] != "mountain"
        && convert_landscape_id[this->field[x][y].getLandscape()->getObjectId()] != "water"){
            this->field[x][y].setNeutralObject(convert_neutral_object_name["public_house"],x,y);
            this->neutral_objects_coordinates.emplace_back(make_pair(x,y));
            this->field[x][y].setOccupiedByBuilding(true);
            break;
        }
    }
    while (1){
        x = rand() % this->x_size;
        y = rand() % this->y_size;
        if(!this->field[x][y].getIfOccupiedByBuilding() && convert_landscape_id[this->field[x][y].getLandscape()->getObjectId()] != "mountain"
        && convert_landscape_id[this->field[x][y].getLandscape()->getObjectId()] != "water"){
            this->field[x][y].setNeutralObject(convert_neutral_object_name["bar"],x,y);
            this->neutral_objects_coordinates.emplace_back(make_pair(x,y));
            this->field[x][y].setOccupiedByBuilding(true);
            break;
        }
    }
}