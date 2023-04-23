#include "Iterator.h"
#include "Unit.h"

    Iterator::Iterator(Field& field) : field(field), x(0), y(0){

    }

    bool Iterator::hasNext(){
        for (int i=0; i<field.lengthY; i++){
            for (int j=0; j<field.lenghtX; j++){
                if (field.mapCell[i][j]->unit != nullptr){
                    if (i > y) {
                        x = j;
                        y = i;
                        isFind = true;
                        return true;
                    }
                    else if ((i==y && j>x) || !isFind){
                        x = j;
                        y = i;
                        isFind = true;
                        return true;
                    }
                }
            }
        }
        return false;
    }

    Unit*& Iterator::operator* () {
        return field.mapCell[y][x]->unit;
    }
