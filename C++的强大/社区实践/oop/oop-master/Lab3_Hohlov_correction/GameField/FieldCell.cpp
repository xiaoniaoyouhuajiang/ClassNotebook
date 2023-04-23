
#include "FieldCell.h"

FieldCell::FieldCell(Landscape *landscape): FieldCell() {

    landscape = landscape;

}

bool FieldCell::setObject(GameObject *object) {
    if (isEmpty()){

        this->object = object;
        return true;

    } else {
        return false;
    }
}

bool FieldCell::setLandscape(Landscape *landscape) {
    if (!this->landscape){

        this->landscape = landscape;
        return true;

    } else {
        return false;
    }
}

void FieldCell::eraseObject() {

    object = nullptr;

}

std::ostream &operator<<(std::ostream &stream, const FieldCell &cell) {

    stream << " ";
    if (cell.landscape){

        if (cell.object)
            cell.landscape->print(stream, *cell.object);
        else
            stream << *cell.landscape;

    } else{

        if (cell.object)
            stream << "|" << *cell.object << "|";
//            stream << *cell.object;
        else
            stream << "|.|";
//            stream << ".";

    }

    return stream;

}

FieldCell::FieldCell(FieldCell &&other):
object(other.object),
landscape(other.landscape)
{

    other.object = nullptr;

}

FieldCell &FieldCell::operator=(FieldCell &&other) {

    if (&other == this) return *this;

    object = other.object;
    other.object = nullptr;

    return *this;

}

FieldCell::FieldCell(const FieldCell &other):
object(other.object),
landscape(other.landscape){}

FieldCell &FieldCell::operator=(const FieldCell &other) {

    if (&other == this) return *this;

    object = other.object;
    landscape = other.landscape;

    return *this;

}
