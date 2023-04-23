//
// Created by anton on 2/11/20.
//

#include "Field.h"

#include "GameObject.h"

Field::Field(int width, int height, int objLimit) {// : width(width), height(height), objLimit(objLimit)
    assert(width > 0);
    assert(height > 0);
    this->width = width;
    this->height = height;
    this->objLimit = objLimit;
    this->objCount = 0;
    content = new GameObject **[width];
    for (int i = 0; i < width; i++) {
        content[i] = new GameObject *[height];
        for (int j = 0; j < height; j++) {
            content[i][j] = nullptr;
        }
    }

}

Field::~Field() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (content[i][j]) delete content[i][j];
        }
        delete[] content[i];
    }
    delete[] content;
}

void Field::getSize(int &width, int &height) {
    width = this->width;
    height = this->height;
}

void Field::resetField() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (content[i][j]) delete content[i][j];
        }
        delete[] content[i];
    }
    delete[] content;
    //TODO
    content = new GameObject **[this->width];
    for (int i = 0; i < this->width; i++) {
        content[i] = new GameObject *[this->height];
        for (int j = 0; j < this->height; j++) {
            content[i][j] = nullptr;
        }
    }
    objCount = 0;
}

GameObject *Field::getAt(int x, int y) {
    assert(0 <= x && x < width);
    assert(0 <= y && y < height);
    return content[x][y];
}

bool Field::setAt(GameObject &obj, int x, int y) {
    assert(0 <= x && x < width);
    assert(0 <= y && y < height);
    if (getAt(x, y))objCount--;
    if (objCount < objLimit) {
        objCount++;
        obj.setCoords(x, y);
        //obj.setActive(true);
        content[x][y] = &obj;
        return true;
    }
    return false;
}

GameObject *Field::removeAt(int x, int y) {
    assert(0 <= x && x < width);
    assert(0 <= y && y < height);
    GameObject *obj = content[x][y];
    content[x][y] = nullptr;
    objCount--;
    return obj;
}

void Field::swap(int x1, int y1, int x2, int y2) {
    assert(0 <= x1 && x1 < width);
    assert(0 <= y1 && y1 < height);
    assert(0 <= x2 && x2 < width);
    assert(0 <= y2 && y2 < height);
    GameObject *src = removeAt(x1, y1);
    GameObject *dest = replaceAt(*src, x2, y2);
    setAt(*dest, x1, y1);
}


bool Field::move(int x1, int y1, int x2, int y2) {
    GameObject *obj = removeAt(x1, y1);
    GameObject *destObj;
    //bool erfolg = obj->step(x2, y2);
    destObj = replaceAt(*obj, x2, y2);
    assert(destObj == nullptr);
    //if (destObj)destObj->setActive(false);
    return true;
}

GameObject *Field::replaceAt(GameObject &obj, int x, int y) {
    assert(0 <= x && x < width);
    assert(0 <= y && y < height);
    auto destObj = getAt(x, y);
    setAt(obj, x, y);
    return destObj;
}

std::string Field::toString() {//top-left to bottom-right
    std::string str;
    for (int j = height; j >= -1; j--) {
        for (int i = -1; i <= width; i++) {
            if (i == -1 || i == width) {
                if (j == -1 || j == height) str += "#";//Corner element
                else {//Left/right Border
                    str += 'a' + j;
                }
            } else if (j == -1 || j == height) {
                str += '1' + i;
            } else {
                if (content[i][j] == nullptr)str += " ";
                else {
                    str += content[i][j]->toChar();

                }
            }
        }
        str += "\n";
    }
    return str;
}

std::wstring Field::toWString() {
    std::wstring str = L"";
    for (int j = height; j >= -1; j--) {
        for (int i = -1; i <= width; i++) {
            if (i == -1 || i == width) {
                if (j == -1 || j == height) str += L"#";//Corner element
                else {//Left/right Border
                    str += L'a' + j;
                }
            } else if (j == -1 || j == height) {
                str += L'1' + i;
            } else {
                if (content[i][j] == nullptr)str += L" ";
                else {
                    str += content[i][j]->toChar();

                }
            }
        }
        str += L"\n";
    }
    return str;
}

Field &Field::operator=(const Field &src) {
    if (&src == this) {
        return *this;
    }
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (content[i][j]) delete content[i][j];
        }
        delete[] content[i];
    }
    delete[] content;

    this->width = src.width;
    this->height = src.height;
    this->objCount = src.objCount;
    this->objLimit = src.objLimit;

    content = new GameObject **[src.width];
    for (int i = 0; i < src.width; i++) {
        content[i] = new GameObject *[src.height];
        for (int j = 0; j < src.height; j++) {
            content[i][j] = src.content[i][j];
        }
    }
    return *this;
}

Field::Field(const Field &src) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (content[i][j]) delete content[i][j];
        }
        delete[] content[i];
    }
    delete[] content;

    this->width = src.width;
    this->height = src.height;
    this->objCount = src.objCount;
    this->objLimit = src.objLimit;

    content = new GameObject **[src.width];
    for (int i = 0; i < src.width; i++) {
        content[i] = new GameObject *[src.height];
        for (int j = 0; j < src.height; j++) {
            content[i][j] = src.content[i][j];
        }
    }
}

Field &Field::operator=(Field &&other) {
    std::swap(*this, other);
    return *this;
}

FieldIterator Field::begin() {
    return FieldIterator(0, 0, this);
}

FieldIterator Field::end() {
    return FieldIterator(width, height, this);
}

std::pair<int, int> Field::getSize() {
    return std::pair<int, int>(width, height);
}
