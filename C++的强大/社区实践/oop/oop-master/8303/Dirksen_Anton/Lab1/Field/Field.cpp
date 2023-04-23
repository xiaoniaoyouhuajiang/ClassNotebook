#include "Field.h"
#include <cassert>
#include <unordered_map>
#include "FieldIterator.h"

Field::Field(int height, int width) : size(height, width)
{
    assert(height>0);
    assert(width>0);
    cell = new Cell* [height];
    for (int i = 0; i < height; i++){
        cell[i] = new Cell[width];
        for (int j = 0; j < width; j++){
            cell[i][j].object = nullptr;
        }
    }

}

Field::~Field() {
    if (cell!= nullptr){
        for (int i = 0; i < size.x; i++){
            delete[] cell[i];
        }
        delete[] cell;
    }
}


bool Field::addObject(Point &point, Object* object) {
    return addObject(point.x, point.y, object);
}

bool Field::addObject(int x, int y, Object* object) {
    assert(x >= 0);
    assert(y >= 0);
    assert(size.x > x);
    assert(size.y > y);
    if (maxCountOfObjects == countOfUnits)
        return false;

    if (cell[x][y].object == nullptr){
        cell[x][y].object = object;
        ++countOfUnits;
        cell[x][y].object->move({x, y});
        return true;
    }
    return false;
}

bool Field::deleteObject(Point &point) {
    return deleteObject(point.x, point.y);
}

bool Field::deleteObject(int x, int y) {
    assert(x >= 0);
    assert(y >= 0);
    assert(size.x > x);
    assert(size.y > y);
    if (cell[x][y].object != nullptr){
        delete cell[x][y].object;
        cell[x][y].object = nullptr;
        --countOfUnits;
        return true;
    }
    return false;
}

bool Field::deleteObject(Object* object) {
    return deleteObject(object->getCoords().x, object->getCoords().y);
}


Field::Field(Field const& field) : size(field.size), countOfUnits(field.countOfUnits), maxCountOfObjects(field.maxCountOfObjects), cell(new Cell* [field.size.x]) {
    for (int i = 0; i < size.x; i++){
        cell[i] = new Cell[size.y];
        for (int j = 0; j < size.y; j++){
            cell[i][j].object = field.cell[i][j].object;
        }
    }
}

Field::Field(Field&& field) : size(field.size), countOfUnits(field.countOfUnits), maxCountOfObjects(field.maxCountOfObjects), cell(field.cell) {
    field.cell = nullptr;
}



Field& Field::operator=(Field const& field) {
    if (this != &field){
        size = field.size;
        countOfUnits = field.countOfUnits;
        maxCountOfObjects = field.maxCountOfObjects;
        for (int i = 0; i < field.size.x; i++){
            for (int j = 0; j < field.size.y; j++){
                delete cell[i][j].object;
            }
            delete[] cell[i];
        }
        delete[] cell;

        cell = new Cell* [field.size.x];
        for (int i = 0; i < field.size.x; i++){
            cell[i] = new Cell[field.size.y];
            for (int j = 0; j < field.size.y; j++){
                cell[i][j].object = field.cell[i][j].object;
            }
        }
    }
    return *this;
}

Field& Field::operator=(Field&& field) {
    cell = field.cell;
    field.cell = nullptr;
}

bool Field::moveObject(Object * object, int x, int y) {
    if (object != nullptr && object->type()==UNIT){
        if ((isFreeCell(x, y) || object->texture() == ARCHMAGE ) && abs(object->getCoords().x - x) <= 1 && abs(
                object->getCoords().y - y) <= 1) {
            std::swap(cell[object->getCoords().x][object->getCoords().y].object, cell[x][y].object);
            if (!isFreeCell(object->getCoords().x, object->getCoords().y))
                cell[object->getCoords().x][object->getCoords().y].object->move(object->getCoords());
            object->move({x, y});
            return true;
        }
    }
    return false;
}


bool Field::isFreeCell(int x, int y) const{
    return cell[x][y].object == nullptr;
}

void Field::print() const{
    std::cout << "\n\n";
    for (int i = 0; i < size.x; i++){
        for (int j = 0; j < size.y; j++){
            std::cout.width(3);
            std::cout << (isFreeCell(i, j) ? '_' : (char)cell[i][j].object->texture());
        }
        std::cout << std::endl;
    }
}

Object* Field::getObject(int x, int y) const{
    return cell[x][y].object;
}

FieldIterator Field::begin() { return FieldIterator(Point(0, 0), this); }
FieldIterator Field::end() { return FieldIterator(Point(0, size.x), this); }