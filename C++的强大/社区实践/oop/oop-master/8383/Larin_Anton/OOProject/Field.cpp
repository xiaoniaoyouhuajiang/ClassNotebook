//
// Created by anton on 5/10/20.
//

#include "Field.h"
#include "Exeptions/ObjectLimitExceededException.h"

Field::Field(int objLimit, int height, int width) : objLimit(objLimit),
                                                    height(height), width(width), objCnt(0) {
    content = new Cell*[height];
    for(int i = 0;i<height;i++){
        content[i] = new Cell[width]();
    }
}

std::shared_ptr<Unit> Field::getUnitAt(int x, int y) {
    return content[y][x].getUnit();
}

void Field::setUnitAt(std::shared_ptr<Unit> unit, int x, int y) {
    if(!unit && getUnitAt(x,y))objCnt--;
    if(unit && !getUnitAt(x,y)){
        objCnt++;
        if(objCnt>objLimit)onLimitExceeded();
    }
    content[y][x].setUnit(unit);
}

std::shared_ptr<TerrainProxy> Field::getTerrainAt(int x, int y) {
    return content[y][x].getTerrain();
}

void Field::setTerrainAt(std::shared_ptr<TerrainProxy> terrain, int x, int y) {
    content[y][x].setTerrain(terrain);
}

std::shared_ptr<Entity> Field::getEntityAt(int x, int y) {
    return content[y][x].getEntity();
}

void Field::setEntityAt(std::shared_ptr<Entity> entity, int x, int y) {
    content[y][x].setEntity(entity);
}

void Field::onLimitExceeded() {
    throw ObjectLimitExceededException();

}

bool Field::objSwap(int x1, int y1, int x2, int y2) {
    //True if any one is occupied
    //False if neither of both are occupied

    auto unit1 = getUnitAt(x1,y1);
    auto unit2 = getUnitAt(x2,y2);
    auto foo = unit1.use_count();
    foo = unit2.use_count();
    bool occ1 = unit1!=0;
    bool occ2 = unit2!=0;
    if(occ1){
        if(occ2){
            setUnitAt(std::shared_ptr<Unit>(unit2),x1,y1);
            setUnitAt(std::shared_ptr<Unit>(unit1),x2,y2);
            return false;
        }else{
            //Unit* tmp = &(*unit1);
            setUnitAt(std::shared_ptr<Unit>(unit2),x1,y1);
            setUnitAt(std::shared_ptr<Unit>(unit1),x2,y2);;
            return true;
        }
    } else{
        if(occ2){
            setUnitAt(std::shared_ptr<Unit>(unit2),x1,y1);
            setUnitAt(std::shared_ptr<Unit>(unit1),x2,y2);
            return true;
        }else{
            return false;
        }
    }
}

std::wstring Field::toWString() {
    std::wstring str = L"";
    for (int j = height; j >= -1; j--) {
        for (int i = -1; i <= width; i++) {
            if (i == -1 || i == width) {
                if (j == -1 || j == height) str += L"#";//Corner element
                else {//Left/right Border
                    str += L'0' + j;
                }
            } else if (j == -1 || j == height) {
                str += L'0' + i;
            } else {
                auto ptr = content[i][j].getUnit();
                if(ptr){
                        str += ptr->getFlyWeight()->symbol;
                }else{
                    auto ePtr = content[i][j].getEntity();
                    if(ePtr){
                        str += ePtr->getFlyWeight()->symbol;
                    } else{
                        str += content[i][j].getTerrain()->getFlyWeight()->symbol;
                    }
                }
            }
        }
        str += L"\n";
    }
    return str;
}

Field::Field(const Field &src) {
    if(this != &src) {
        this->objLimit = src.objLimit;
        this->objCnt = src.objCnt;
        this->width = src.width;
        this->height = src.height;
        content = new Cell *[height];
        for (int i = 0; i < src.height; i++) {
            content[i] = new Cell[width]();
            for (int j = 0; j < width; j++) {
                content[i][j] = Cell(src.content[i][j]);
            }
        }
    }
}

Field &Field::operator=(Field &&other) {
    std::swap(*this, other);
    return *this;
}

Field::iterator Field::begin() {
    return Field::iterator(0, 0, this);
}

Field::iterator Field::end() {
    return Field::iterator(0, height, this);
}

bool Field::iterator::operator==(const Field::iterator &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool Field::iterator::operator!=(const Field::iterator &rhs) const {
    return !(rhs == *this);
}

Field::iterator& Field::iterator::next() {
    if(x+1==collection->width){
        if(y==collection->height){
            assert(0&&"Iterating out of collection");
        }else{
            y++;
            return *this;
            //return Field::iterator(0,y+1,collection);
        }
    }
    else{
        x++;
        return *this;
        //return Field::iterator(x+1,y,collection);
    }
}

bool Field::iterator::hasNext() {
    return *this==iterator(0,collection->height,0);
}

Field::iterator::iterator(int x, int y, Field *collection) : collection(collection), x(x), y(y) {}

Cell &Field::iterator::operator*() const {
    return collection->content[y][x];
}

Field::iterator Field::iterator::operator++() {
    auto it = *this;
    next();
    return it;
}

Field::iterator &Field::iterator::operator++(int) {
    return next();
}
