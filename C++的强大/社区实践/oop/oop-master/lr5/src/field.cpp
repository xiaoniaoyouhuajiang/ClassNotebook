#include "field.h"


Field::Field(int M, int N, int maxNumOfObjects){
    rows = M;
    columns = N;
    this->maxNumOfObjects = maxNumOfObjects;
    field = new Cell**[this->rows];
    for (int i = 0; i < rows; i++){
        field[i] = new Cell*[columns];
        for(int j = 0; j < columns; j++){
            field[i][j] = new Cell;
            field[i][j]->base = nullptr;
            field[i][j]->unit = nullptr;
            field[i][j]->nObject = nullptr;
            if (i == 3 && j == 7){
                field[i][j]->nObject = new Stone();
            }
            if (i == 6 && j == 4){
                field[i][j]->nObject = new Gold();
            }
            if (i == 11 && j == 15){
                field[i][j]->nObject = new LifeWell();
            }
            if (i == 15 && j == 5){
                field[i][j]->nObject = new ForceWell();
            }
         //   if ((i != 6 && j != 4) || (i != 3 && j != 7) || (i != 9 && j != 5) || (i != 15 && j != 10)){

         //   }
            if (i > 3 && i < 9){            // потом сделаю рандомизированно
                if (j > columns/2-3 && j < columns/2 + 3){
                    field[i][j]->landScape = new Forest;
                    continue;
                }
            }
            if (i > rows/2+2 && i < rows/2 + 8){
                if (j > columns/2-1 && j < columns/2 + 5){
                    field[i][j]->landScape = new Swamp;
                    continue;
                }
            }
            field[i][j]->landScape = new Plain;
        }
    }
    units = new Unit**[countOfDiffUnits*2];
    for(int i = 0; i< countOfDiffUnits*2; i++){
        units[i] = new Unit*[maxNumOfObjects];
        for(int j = 0; j < maxNumOfObjects; j++){
            units[i][j] = new Unit;
            units[i][j] = nullptr;
        }
    }
}

Field::Field(const Field& field) : rows(field.rows), columns(field.columns), countOfObjects(field.countOfObjects), maxNumOfObjects(field.maxNumOfObjects){     // конструктор копирования
    cout << "Call the construktor of copy\n";
    this->field = new Cell**[rows];
    for (int i = 0; i < field.rows; i++){
        this->field[i] = new Cell*[columns];
        for(int j = 0; j < columns; j++){
            this->field[i][j] = new Cell;
            if (field.field[i][j]->landScape){
                if (field.field[i][j]->landScape->sym == '|'){
                    this->field[i][j]->landScape = new Forest;
                }
                if (field.field[i][j]->landScape->sym == '_'){
                    this->field[i][j]->landScape = new Swamp;
                }
                if (field.field[i][j]->landScape->sym == ' '){
                    this->field[i][j]->landScape = new Plain;
                }
            }
            if (field.field[i][j]->base){
                this->field[i][j]->base = new Base;
                this->field[i][j]->base->hp = field.field[i][j]->base->hp;
                this->field[i][j]->base->sym = field.field[i][j]->base->sym;
            }
            if (field.field[i][j]->nObject){
                if (field.field[i][j]->nObject->sym == 's'){
                    this->field[i][j]->nObject = new Stone;
                    this->field[i][j]->nObject = field.field[i][j]->nObject;
                }
                if (field.field[i][j]->nObject->sym == 'g'){
                    this->field[i][j]->nObject = new Gold;
                    this->field[i][j]->nObject = field.field[i][j]->nObject;
                }
                if (field.field[i][j]->nObject->sym == 'l'){
                    this->field[i][j]->nObject = new LifeWell;
                    this->field[i][j]->nObject = field.field[i][j]->nObject;
                }
                if (field.field[i][j]->nObject->sym == 'f'){
                    this->field[i][j]->nObject = new ForceWell;
                    this->field[i][j]->nObject = field.field[i][j]->nObject;
                }
            }
            if (field.field[i][j]->unit){
                this->field[i][j]->unit = new Unit;
                this->field[i][j]->unit->x = field.field[i][j]->unit->x;
                this->field[i][j]->unit->y = field.field[i][j]->unit->y;
                this->field[i][j]->unit->id.code = field.field[i][j]->unit->id.code;
                this->field[i][j]->unit->id.index = field.field[i][j]->unit->id.index;
                this->field[i][j]->unit->sym = field.field[i][j]->unit->sym;
            }
            this->field[i][j]->landScape->sym = field.field[i][j]->landScape->sym;
        }
    }

    this->units = new Unit**[COUNT_OF_UNITS_TYPE*2];
    for (int i = 0; i < COUNT_OF_UNITS_TYPE*2; i++){
        this->units[i] = new Unit*[maxNumOfObjects];
        for (int j = 0; j < maxNumOfObjects; j++){
            if (field.units[i][j]){
                this->units[i][j] = new Unit;
                this->units[i][j]->x = field.units[i][j]->x;
                this->units[i][j]->y = field.units[i][j]->y;
                this->units[i][j]->id.code = field.units[i][j]->id.code;
                this->units[i][j]->id.index = field.units[i][j]->id.index;
                this->units[i][j]->sym = field.units[i][j]->sym;
            }
        }
    }

}

Field& Field::operator= (const Field& field){          // оператор присваивания для копирования
    if (&field == this)
        return *this;
    cout << "new operator =\n";
    for (int i = 0; i < this->rows; i++){
        for (int j = 0; j < this->columns; j++){
            if (this->field[i][j]->base)
                delete this->field[i][j]->base;
            if (this->field[i][j]->unit)
                delete this->field[i][j]->unit;
            if(this->field[i][j]->nObject)
                delete this->field[i][j]->nObject;
        //    if (this->field[i][j]->landScape)
          //      delete this->field[i][j]->landScape;
        }
        delete [] this->field[i];
    }
    for (int i = 0; i < COUNT_OF_UNITS_TYPE; i++){
        delete [] this->units[i];
    }
    delete[] this->field;
    delete[] this->units;
    this->field = new Cell**[rows];
    for (int i = 0; i < field.rows; i++){
        this->field[i] = new Cell*[columns];
        for(int j = 0; j < columns; j++){
            this->field[i][j] = new Cell;
            if (field.field[i][j]->landScape){
                if (field.field[i][j]->landScape->sym == '|'){
                    this->field[i][j]->landScape = new Forest;
                }
                if (field.field[i][j]->landScape->sym == '_'){
                    this->field[i][j]->landScape = new Swamp;
                }
                if (field.field[i][j]->landScape->sym == ' '){
                    this->field[i][j]->landScape = new Plain;
                }
            }
            if (field.field[i][j]->base){
                this->field[i][j]->base = new Base;
                this->field[i][j]->base->hp = field.field[i][j]->base->hp;
                this->field[i][j]->base->sym = field.field[i][j]->base->sym;
            }
            if (field.field[i][j]->nObject){
                if (field.field[i][j]->nObject->sym == 's'){
                    this->field[i][j]->nObject = new Stone;
                    this->field[i][j]->nObject = field.field[i][j]->nObject;
                }
                if (field.field[i][j]->nObject->sym == 'g'){
                    this->field[i][j]->nObject = new Gold;
                    this->field[i][j]->nObject = field.field[i][j]->nObject;
                }
                if (field.field[i][j]->nObject->sym == 'l'){
                    this->field[i][j]->nObject = new LifeWell;
                    this->field[i][j]->nObject = field.field[i][j]->nObject;
                }
                if (field.field[i][j]->nObject->sym == 'f'){
                    this->field[i][j]->nObject = new ForceWell;
                    this->field[i][j]->nObject = field.field[i][j]->nObject;
                }
            }
            if (field.field[i][j]->unit){
                this->field[i][j]->unit = new Unit;
                this->field[i][j]->unit->x = field.field[i][j]->unit->x;
                this->field[i][j]->unit->y = field.field[i][j]->unit->y;
                this->field[i][j]->unit->id.code = field.field[i][j]->unit->id.code;
                this->field[i][j]->unit->id.index = field.field[i][j]->unit->id.index;
                this->field[i][j]->unit->sym = field.field[i][j]->unit->sym;
            }
            this->field[i][j]->landScape->sym = field.field[i][j]->landScape->sym;
        }
    }
    this->units = new Unit**[COUNT_OF_UNITS_TYPE*2];
    for (int i = 0; i < COUNT_OF_UNITS_TYPE*2; i++){
        this->units[i] = new Unit*[maxNumOfObjects];
        for (int j = 0; j < maxNumOfObjects; j++){
            if (field.units[i][j]){
                this->units[i][j] = new Unit;
                this->units[i][j]->x = field.units[i][j]->x;
                this->units[i][j]->y = field.units[i][j]->y;
                this->units[i][j]->id.code = field.units[i][j]->id.code;
                this->units[i][j]->id.index = field.units[i][j]->id.index;
                this->units[i][j]->sym = field.units[i][j]->sym;
            }
        }
    }
    return *this;
}

Field::Field(Field&& field) : rows(field.rows), columns(field.columns), countOfObjects(field.countOfObjects), maxNumOfObjects(field.maxNumOfObjects){  // конструктор перемещения
    cout << "Call the construktor of relocation\n";
    field.rows = 0;
    field.columns = 0;
    field.countOfObjects = 0;
    field.maxNumOfObjects = 0;
    this->field = field.field;
    for (int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            field.field[i][j]->landScape = nullptr;
            if (field.field[i][j]->base){
                field.field[i][j]->base = nullptr;
            }
            if (field.field[i][j]->nObject){
                field.field[i][j]->nObject = nullptr;
            }
            if (field.field[i][j]->unit){
                field.field[i][j]->unit = nullptr;
            }
        }
        field.field = nullptr;
    }

    this->units = field.units;
    for (int i = 0; i < COUNT_OF_UNITS_TYPE*2; i++){
        for (int j = 0; j < maxNumOfObjects; j++){
            if (field.units[i][j]){
                field.units[i][j] = nullptr;
            }
        }
    }
    field.units = nullptr;
}

Field& Field::operator=(Field&& field){            // оператор присваивания для перемещения
    if (&field == this)
        return *this;
    cout << "new relocation operator =\n";
    for (int i = 0; i < this->rows; i++){
        for (int j = 0; j < this->columns; j++){
            if (this->field[i][j]->base)
                delete this->field[i][j]->base;
            if (this->field[i][j]->unit)
                delete this->field[i][j]->unit;
            if(this->field[i][j]->nObject)
                delete this->field[i][j]->nObject;
         //   if (this->field[i][j]->landScape)
           //     delete this->field[i][j]->landScape;
        }
        delete [] this->field[i];
    }
    for (int i = 0; i < COUNT_OF_UNITS_TYPE*2; i++){
        delete [] this->units[i];
    }
    delete[] this->field;
    delete[] this->units;
    field.rows = 0;
    field.columns = 0;
    field.countOfObjects = 0;
    field.maxNumOfObjects = 0;
    this->field = field.field;
    for (int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            field.field[i][j]->landScape = nullptr;
            if (field.field[i][j]->base){
                field.field[i][j]->base = nullptr;
            }
            if (field.field[i][j]->nObject){
                field.field[i][j]->nObject = nullptr;
            }
            if (field.field[i][j]->unit){
                field.field[i][j]->unit = nullptr;
            }
        }
        field.field = nullptr;
    }
    this->units = field.units;
    for (int i = 0; i < 12; i++){
        for (int j = 0; j < maxNumOfObjects; j++){
            if (field.units[i][j]){
                field.units[i][j] = nullptr;
            }
        }
    }
    field.units = nullptr;
    return *this;
}

int Field::checkEmptySpace(int code){
    int in = 0;
    while(units[code][in]){
        in++;
    }
    return in;
}

void Field::setUnit1(Unit* unit){
    if (unit->x < this->rows && unit->y < this->columns && this->countOfObjects < this->maxNumOfObjects){
        int in = checkEmptySpace(unit->id.code);
        units[unit->id.code][in] = unit;
        unit->id.index = in;
        field[unit->y][unit->x]->unit = unit;
    }
}

void Field::deleteUnit1(Unit* unit){
    field[rows/2][0]->base->gold += unit->cost/2;
    field[rows/2][0]->base->countOfUnits--;
    units[unit->id.code][unit->id.index] = nullptr;
    field[unit->y][unit->x]->unit = nullptr;
    delete unit;
}

Unit* Field::changeUnit1 (Unit* unit){                      // need to be fixed
    int code = unit->id.code;
    int index = unit->id.index;
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 30; j++){
            if (units[i][j] && units[i][j] != unit){
                return units[i][j];
            }
        }
    }
}

void Field::setUnit2(Unit* unit){
    if (unit->x < this->rows && unit->y < this->columns && this->countOfObjects < this->maxNumOfObjects){
        int in = checkEmptySpace(unit->id.code);
        units[unit->id.code][in] = unit;
        unit->id.index = in;
        field[unit->y][unit->x]->unit = unit;
    }
}

void Field::deleteUnit2(Unit* unit){
    field[rows/2][columns-1]->base->gold += unit->cost/2;
    field[rows/2][columns-1]->base->countOfUnits--;
    units[unit->id.code][unit->id.index] = nullptr;
    field[unit->y][unit->x]->unit = nullptr;
    delete unit;
}

Unit* Field::changeUnit2(Unit* unit){
    for (int i = 6; i < 12; i++){
        for (int j = 0; j < 30; j++){
            if (units[i][j] && units[i][j] != unit){
                return units[i][j];
            }
        }
    }
}

void Field::move(Unit* unit, int x, int y, TerminalLog* termLog, FileLog* fileLog, int logFlag){                        // передвижение юнитов
        if (y < 0 || y > rows-1 || x < 0 || x > columns-1){
            try {
                throw -1;
            } catch (int a) {
                std::cerr << "\nError " << a << "\nYou tried to leave the battle!!!\n";
                return;
            }
        }
        if (unit->id.code < 6 && field[y][x]->unit && field[y][x]->unit->id.code > 5){
            field[y][x]->unit->hp -= unit->force;
            if (logFlag == 1){
                termLog->log("Unit"+to_string(unit->id.code)+to_string(unit->id.index)+" has attacked unit"+to_string(field[y][x]->unit->id.code)+to_string(field[y][x]->unit->id.index)+" with "+to_string(unit->force)+" damage.");
            }
            if (logFlag == 2){
                fileLog->log("Unit"+to_string(unit->id.code)+to_string(unit->id.index)+" has attacked unit"+to_string(field[y][x]->unit->id.code)+to_string(field[y][x]->unit->id.index)+" with "+to_string(unit->force)+" damage.");
            }
            if (field[y][x]->unit->hp <= 0){
                deleteUnit2(field[y][x]->unit);
            }
            return;
        }
        if (unit->id.code > 5 && field[y][x]->unit && field[y][x]->unit->id.code < 6){
            field[y][x]->unit->hp -= unit->force;
            if (logFlag == 1){
                termLog->log("Unit"+to_string(unit->id.code)+to_string(unit->id.index)+" has attacked unit"+to_string(field[y][x]->unit->id.code)+to_string(field[y][x]->unit->id.index)+" with "+to_string(unit->force)+" damage.");
            }
            if (logFlag == 2){
                fileLog->log("Unit"+to_string(unit->id.code)+to_string(unit->id.index)+" has attacked unit"+to_string(field[y][x]->unit->id.code)+to_string(field[y][x]->unit->id.index)+" with "+to_string(unit->force)+" damage.");
            }
            if (field[y][x]->unit->hp <= 0){
                deleteUnit1(field[y][x]->unit);
            }
            return;
        }
        if (field[y][x]->unit || field[y][x]->base){
            return;
        }
        else {
            if (field[y][x]->landScape->sym != field[unit->y][unit->x]->landScape->sym){
                if (!field[y][x]->landScape->interaction(unit)){
                    return;
                }
            }
            if (field[y][x]->nObject){
                if (field[y][x]->nObject->sym == 'f'){
                    if (unit->compFlag){
                        field[y][x]->nObject->strategy(unit);
                    }
                    return;
                }
                if (field[y][x]->nObject->sym == 'l'){
                    if (unit->compFlag){
                        field[y][x]->nObject->strategy(unit);
                    }
                    return;
                }
                if (field[y][x]->nObject->sym == 's'){
                    return;
                }
                if (field[y][x]->nObject->sym == 'g'){
                    NitralObject* g = field[y][x]->nObject;
                    field[y][x]->nObject = nullptr;
                    delete g;
                    field[rows/2][0]->base->gold += 1000;
                }
            }
            field[unit->y][unit->x]->unit = nullptr;
            units[unit->id.code][unit->id.index]->x = x;
            units[unit->id.code][unit->id.index]->y = y;
            unit->x = x;
            unit->y = y;
            field[y][x]->unit = unit;
        }
    }

void Field::createBase(int x, int y){
    field[y][x]->base = new Base;
    field[y][x]->base->x = x;
    field[y][x]->base->y = y;
}

void Field::setUnitFromBase(ArmyFactory& factory, int x, int y, int code){
    Unit* unit;
    if (code > 5){
        unit = field[y][x]->base->createUnit(code-6, factory);
    }
    else{
        unit = field[y][x]->base->createUnit(code, factory);
    }
    if (unit == nullptr){
        return;
    }
    field[unit->y][unit->x]->unit = unit;
    int in = checkEmptySpace(code);
    units[code][in] = unit;
    unit->id.index = in;
}

Unit* Field::getLastUnit(int code){
    Unit* unit = new Unit;
    int i = 0;
    while (units[code][i+1]){
        i++;
    }
    if (units[code][i]){
        unit = units[code][i];
        return unit;
    }
    else {
        return nullptr;
    }
}

int Field::getBaseGold(int x, int y){
    return field[y][x]->base->gold;
}

int Field::getBaseCountOfUnits(int x, int y){
    return field[y][x]->base->countOfUnits;
}

void Field::printField(Unit* unit){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            if (field[i][j]->unit){
                cout << field[i][j]->unit->sym;
                continue;
            }
            if (field[i][j]->base){
                cout << field[i][j]->base->sym;
                continue;
            }
            if (field[i][j]->nObject){
                cout << field[i][j]->nObject->sym;
                continue;
            }
            if(field[i][j]->landScape){
                cout << field[i][j]->landScape->sym;
                continue;
            }
        }
        cout << '\n';
    }
    if (unit)
        cout << "\nForce of current unit: " << unit->force << "\t\tHp of current unit: " << unit->hp << endl;

}

Memento* Field::quickSave(Memento* snapShot){
    snapShot->rows = this->rows;
    snapShot->columns = this->columns;
    snapShot->field = new Cell**[rows];
    for (int i = 0; i < rows; i++){
        snapShot->field[i] = new Cell*[columns];
        for(int j = 0; j < columns; j++){
            snapShot->field[i][j] = new Cell;
            snapShot->field[i][j]->base = nullptr;
            snapShot->field[i][j]->unit = nullptr;
            snapShot->field[i][j]->nObject = nullptr;
            if (this->field[i][j]->landScape){
                if (this->field[i][j]->landScape->sym == '|'){
                    snapShot->field[i][j]->landScape = new Forest;
                }
                if (this->field[i][j]->landScape->sym == '_'){
                    snapShot->field[i][j]->landScape = new Swamp;
                }
                if (this->field[i][j]->landScape->sym == ' '){
                    snapShot->field[i][j]->landScape = new Plain;
                }
            }
            if (this->field[i][j]->base){
                snapShot->field[i][j]->base = new Base;
                snapShot->field[i][j]->base->hp = this->field[i][j]->base->hp;
                snapShot->field[i][j]->base->gold = this->field[i][j]->base->gold;
                snapShot->field[i][j]->base->x = this->field[i][j]->base->x;
                snapShot->field[i][j]->base->y = this->field[i][j]->base->y;
                snapShot->field[i][j]->base->countOfUnits = this->field[i][j]->base->countOfUnits;
            }
            if (this->field[i][j]->nObject){
                if (this->field[i][j]->nObject->sym == 's'){
                    snapShot->field[i][j]->nObject = new Stone;
                }
                if (this->field[i][j]->nObject->sym == 'g'){
                    snapShot->field[i][j]->nObject = new Gold;
                }
                if (this->field[i][j]->nObject->sym == 'l'){
                    snapShot->field[i][j]->nObject = new LifeWell;
                }
                if (this->field[i][j]->nObject->sym == 'f'){
                    snapShot->field[i][j]->nObject = new ForceWell;
                }
            }
            if (this->field[i][j]->unit){
                snapShot->field[i][j]->unit = new Unit;
                snapShot->field[i][j]->unit->x = this->field[i][j]->unit->x;
                snapShot->field[i][j]->unit->y = this->field[i][j]->unit->y;
                snapShot->field[i][j]->unit->id.code = this->field[i][j]->unit->id.code;
                snapShot->field[i][j]->unit->id.index = this->field[i][j]->unit->id.index;
                snapShot->field[i][j]->unit->sym = this->field[i][j]->unit->sym;
                snapShot->field[i][j]->unit->hp = this->field[i][j]->unit->hp;
                snapShot->field[i][j]->unit->force = this->field[i][j]->unit->force;
                snapShot->field[i][j]->unit->cost = this->field[i][j]->unit->cost;
                snapShot->field[i][j]->unit->attackRange = this->field[i][j]->unit->attackRange;
            }
        }
    }

    snapShot->units = new Unit**[12];
    for (int i = 0; i < 12; i++){
        snapShot->units[i] = new Unit*[30];
        for (int j = 0; j < 30; j++){
            if (this->units[i][j]){
                snapShot->units[i][j] = new Unit;
                snapShot->units[i][j]->x = this->units[i][j]->x;
                snapShot->units[i][j]->y = this->units[i][j]->y;
                snapShot->units[i][j]->id.code = this->units[i][j]->id.code;
                snapShot->units[i][j]->id.index = this->units[i][j]->id.index;
                snapShot->units[i][j]->sym = this->units[i][j]->sym;
                snapShot->units[i][j]->hp = this->units[i][j]->hp;
                snapShot->units[i][j]->force = this->units[i][j]->force;
            }
            else {
                snapShot->units[i][j] = nullptr;
            }
        }
    }
    snapShot->snapFlag = 1;
    return snapShot;
}

void Field::quickLoad(Memento* snap){
    for (int i = 0; i < this->rows; i++){
        for (int j = 0; j < this->columns; j++){
            if (this->field[i][j]->base)
                delete this->field[i][j]->base;
            if (this->field[i][j]->unit)
                delete this->field[i][j]->unit;
            if(this->field[i][j]->nObject)
                delete this->field[i][j]->nObject;
        }
        delete [] this->field[i];
    }
    for (int i = 0; i < 12; i++){
        delete [] this->units[i];
    }
    delete[] this->field;
    delete[] this->units;
    this->rows = snap->rows;
    this->columns = snap->columns;
    this->maxNumOfObjects = rows*columns;
    field = new Cell**[rows];
    for (int i = 0; i < rows; i++){
        field[i] = new Cell*[columns];
        for(int j = 0; j < columns; j++){
            field[i][j] = new Cell;
            field[i][j]->base = nullptr;
            field[i][j]->unit = nullptr;
            field[i][j]->nObject = nullptr;
            if (snap->field[i][j]->landScape){
                if (snap->field[i][j]->landScape->sym == '|'){
                    field[i][j]->landScape = new Forest;
                }
                if (snap->field[i][j]->landScape->sym == '_'){
                    field[i][j]->landScape = new Swamp;
                }
                if (snap->field[i][j]->landScape->sym == ' '){
                    field[i][j]->landScape = new Plain;
                }
            }
            if (snap->field[i][j]->base){
                field[i][j]->base = new Base;
                field[i][j]->base->hp = snap->field[i][j]->base->hp;
                field[i][j]->base->sym = snap->field[i][j]->base->sym;
                field[i][j]->base->gold = snap->field[i][j]->base->gold;
                field[i][j]->base->countOfUnits = snap->field[i][j]->base->countOfUnits;
                field[i][j]->base->x = snap->field[i][j]->base->x;
                field[i][j]->base->y = snap->field[i][j]->base->y;
            }
            if (snap->field[i][j]->nObject){
                if (snap->field[i][j]->nObject->sym == 's'){
                    field[i][j]->nObject = new Stone;
                }
                if (snap->field[i][j]->nObject->sym == 'g'){
                    field[i][j]->nObject = new Gold;
                }
                if (snap->field[i][j]->nObject->sym == 'l'){
                    field[i][j]->nObject = new LifeWell;
                }
                if (snap->field[i][j]->nObject->sym == 'f'){
                    field[i][j]->nObject = new ForceWell;
                }
            }
            if (snap->field[i][j]->unit){
                field[i][j]->unit = new Unit;
                field[i][j]->unit->x = snap->field[i][j]->unit->x;
                field[i][j]->unit->y = snap->field[i][j]->unit->y;
                field[i][j]->unit->id.code = snap->field[i][j]->unit->id.code;
                field[i][j]->unit->id.index = snap->field[i][j]->unit->id.index;
                field[i][j]->unit->sym = snap->field[i][j]->unit->sym;
                field[i][j]->unit->hp = snap->field[i][j]->unit->hp;
                field[i][j]->unit->force = snap->field[i][j]->unit->force;
                field[i][j]->unit->attackRange = snap->field[i][j]->unit->attackRange;
            }
           // field[i][j]->landScape->sym = snap->field[i][j]->landScape->sym;
        }
    }

    units = new Unit**[12];
    for (int i = 0; i < 12; i++){
        units[i] = new Unit*[30];               // больше не видно юнитов после загрузки
        for (int j = 0; j < 30; j++){
            if (snap->units[i][j]){
                units[i][j] = new Unit;
                units[i][j]->x = snap->units[i][j]->x;
                units[i][j]->y = snap->units[i][j]->y;
                units[i][j]->id.code = snap->units[i][j]->id.code;
                units[i][j]->id.index = snap->units[i][j]->id.index;
                units[i][j]->sym = snap->units[i][j]->sym;
                units[i][j]->force = snap->units[i][j]->force;
                units[i][j]->hp = snap->units[i][j]->hp;
                units[i][j]->attackRange = snap->units[i][j]->attackRange;
            }
            else {
                units[i][j] = nullptr;
            }
        }
    }
}



Field::~Field(){
    for (int i = 0; i < this->rows; i++){
        for (int j = 0; j < this->columns; j++){
            if (this->field[i][j]->base)
                delete this->field[i][j]->base;
            if (this->field[i][j]->unit)
                delete this->field[i][j]->unit;
            if(this->field[i][j]->nObject)
                delete this->field[i][j]->nObject;
          //  if (this->field[i][j]->landScape)
            //    delete this->field[i][j]->landScape;
        }
        delete [] this->field[i];
    }
    for (int i = 0; i < COUNT_OF_UNITS_TYPE; i++){
        delete [] this->units[i];
    }
    delete[] this->field;
    delete[] this->units;
}

/* Паттерн команда */

void MoveUpCommand::execute(Unit* unit, TerminalLog* termLog, FileLog* fileLog, int logFlag){
    gField->move(unit, unit->x, unit->y-1, termLog, fileLog, logFlag);
}

void MoveDownCommand::execute(Unit* unit, TerminalLog* termLog, FileLog* fileLog, int logFlag){
    gField->move(unit, unit->x, unit->y+1, termLog, fileLog, logFlag);
}

void MoveLeftCommand::execute(Unit* unit, TerminalLog* termLog, FileLog* fileLog, int logFlag){
    gField->move(unit, unit->x-1, unit->y, termLog, fileLog, logFlag);
}

void MoveRightCommand::execute(Unit* unit, TerminalLog* termLog, FileLog* fileLog, int logFlag){
    gField->move(unit, unit->x+1, unit->y, termLog, fileLog, logFlag);
}


void Memento::fileSave(){
    *saveFile << rows << "\n";
    *saveFile << columns << "\n";
    for (int i = 0; i < rows; i ++){
        for (int j = 0; j < columns; j++){
           if (field[i][j]->unit){
               *saveFile << this->field[i][j]->unit->id.code << " " << this->field[i][j]->unit->id.index << " ";
               *saveFile << this->field[i][j]->unit->hp << " " << this->field[i][j]->unit->force << "\n";
           }
           else {
               *saveFile << "skip\n";
           }
           if (field[i][j]->base){
               *saveFile << field[i][j]->base->hp << " " << field[i][j]->base->x << " " << field[i][j]->base->y << " " << field[i][j]->base->countOfUnits << " " << field[i][j]->base->gold << "\n";
           }
           else {
               *saveFile << "skip\n";
           }
           if (field[i][j]->nObject){
               *saveFile << field[i][j]->nObject->sym << "\n";
           }
           else {
               *saveFile << "skip\n";
           }
           if (field[i][j]->landScape->sym != ' '){
               *saveFile << field[i][j]->landScape->sym << "\n";
           }
           *saveFile << "skip\n";
        }
        *saveFile << "skip\n";
    }
    return;
}

void Memento::fileLoad(){
    int buf;
    string str;
    *loadFile >> str;
    this->rows = atoi(str.c_str());
    *loadFile >> str;
    this->columns = atoi(str.c_str());
    this->field = new Cell**[rows];
    units = new Unit**[12];
    for(int i = 0; i< 12; i++){
        units[i] = new Unit*[30];
        for(int j = 0; j < 30; j++){
            units[i][j] = nullptr;
        }
    }
    for (int i = 0; i < rows; i++){
        this->field[i] = new Cell*[columns];
        for (int j = 0; j < columns; j++){
            this->field[i][j] = new Cell;
            *loadFile >> str;
            if (str == "skip"){

            }
            else {
                this->field[i][j]->unit = new Unit;
                this->field[i][j]->unit->id.code = atoi(str.c_str());
                *loadFile >> str;
                this->field[i][j]->unit->id.index = atoi(str.c_str());
                *loadFile >> str;
                this->field[i][j]->unit->hp = atoi(str.c_str());
                *loadFile >> str;
                this->field[i][j]->unit->force = atoi(str.c_str());
                if (this->field[i][j]->unit->id.code == 0 || this->field[i][j]->unit->id.code == 6){
                    this->field[i][j]->unit->sym = 'G';
                    this->field[i][j]->unit->attackRange = 1;
                    this->field[i][j]->unit->cost = 100;
                }
                if (this->field[i][j]->unit->id.code == 1 || this->field[i][j]->unit->id.code == 7){
                    this->field[i][j]->unit->sym = 'S';
                    this->field[i][j]->unit->attackRange = 3;
                    this->field[i][j]->unit->cost = 125;
                }
                if (this->field[i][j]->unit->id.code == 2 || this->field[i][j]->unit->id.code == 8){
                    this->field[i][j]->unit->sym = 'H';
                    this->field[i][j]->unit->attackRange = 2;
                    this->field[i][j]->unit->cost = 150;
                }
                if (this->field[i][j]->unit->id.code == 3 || this->field[i][j]->unit->id.code == 9){
                    this->field[i][j]->unit->sym = 'W';
                    this->field[i][j]->unit->attackRange = 3;
                    this->field[i][j]->unit->cost = 200;
                }
                if (this->field[i][j]->unit->id.code == 4 || this->field[i][j]->unit->id.code == 10){
                    this->field[i][j]->unit->sym = 'J';
                    this->field[i][j]->unit->attackRange = 1;
                    this->field[i][j]->unit->cost = 1000;
                }
                if (this->field[i][j]->unit->id.code == 5 || this->field[i][j]->unit->id.code == 11){
                    this->field[i][j]->unit->sym = 'K';
                    this->field[i][j]->unit->attackRange = 3;
                    this->field[i][j]->unit->cost = 50;
                }
                units[this->field[i][j]->unit->id.code][this->field[i][j]->unit->id.index] = new Unit;
                units[this->field[i][j]->unit->id.code][this->field[i][j]->unit->id.index]->x = j;
                units[this->field[i][j]->unit->id.code][this->field[i][j]->unit->id.index]->y = i;
                units[this->field[i][j]->unit->id.code][this->field[i][j]->unit->id.index]->hp = this->field[i][j]->unit->hp;
                units[this->field[i][j]->unit->id.code][this->field[i][j]->unit->id.index]->force = this->field[i][j]->unit->force;
                units[this->field[i][j]->unit->id.code][this->field[i][j]->unit->id.index]->id.code = this->field[i][j]->unit->id.code;
                units[this->field[i][j]->unit->id.code][this->field[i][j]->unit->id.index]->id.index = this->field[i][j]->unit->id.index;
                units[this->field[i][j]->unit->id.code][this->field[i][j]->unit->id.index]->cost = this->field[i][j]->unit->cost;
                units[this->field[i][j]->unit->id.code][this->field[i][j]->unit->id.index]->attackRange = this->field[i][j]->unit->attackRange;
                units[this->field[i][j]->unit->id.code][this->field[i][j]->unit->id.index]->sym = this->field[i][j]->unit->sym;
            }
            *loadFile >> str;
            if (str == "skip"){

            }
            else {
                field[i][j]->base = new Base;
                this->field[i][j]->base->hp = atoi(str.c_str());
                *loadFile >> this->field[i][j]->base->x;
                *loadFile >> this->field[i][j]->base->y;
                *loadFile >> this->field[i][j]->base->countOfUnits;
                *loadFile >> this->field[i][j]->base->gold;
            }
            *loadFile >> str;
            if (str == "skip"){

            }
            else {
                if (str == "g"){
                    this->field[i][j]->nObject = new Gold;
                }
                if (str == "s"){
                    this->field[i][j]->nObject = new Stone;
                }
                if (str == "l"){
                    this->field[i][j]->nObject = new LifeWell;
                }
                if (str == "f"){
                    this->field[i][j]->nObject = new ForceWell;
                }
            }
            *loadFile >> str;
            if (str == "skip"){
                field[i][j]->landScape = new Plain;
            }
            else {
                if (str == "|"){
                    field[i][j]->landScape = new Forest;
                }
                if (str == "_"){
                    field[i][j]->landScape = new Swamp;
                }
                *loadFile >> str;
            }
        }
        *loadFile >> str;
    }
}
