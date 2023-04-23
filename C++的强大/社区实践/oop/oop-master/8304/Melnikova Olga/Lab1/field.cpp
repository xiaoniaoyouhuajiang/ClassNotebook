#include "field.h"
#include <string>
#include "object.h"
#include "cell.h"

Field::Field(int height, int width) : H(height), W(width)
{
    _cells = new Cell*[this->W];          // выделили память под массив ячеек
    for (int x = 0; x < this->W; x++)     //
        _cells[x] = new Cell[this->H];   //

    for (int x = 0; x < this->W; x++) {
        for (int y = 0; y < this->H; y++) {
            this->_cells[x][y].x = x;
            this->_cells[x][y].y = y;
            this->_cells[x][y].innerObject = nullptr;
        }
    }
}
Field::~Field() {
    for (int x = 0; x < this->W; x++) {
        //for (int y = 0; y < this->H; y++) {
            delete[] this->_cells[x];
        //}
    }
    delete[] this->_cells;
}

Field::Field(const Field& field) : H(field.H), W(field.W)
{
    this->_cells = new Cell*[this->W];          // выделили память под массив ячеек
    for (int x = 0; x < this->W; x++)     //
        _cells[x] = new Cell[this->H];    //

    for (int x = 0; x < this->W; x++) {
        for (int y = 0; y < this->H; y++) {
            this->_cells[x][y] = field._cells[x][y];
        }
    }
}
Field::Field(Field&& field) : _cells(field._cells), H(field.H), W(field.W) {}

Field& Field::operator=(const Field& field) {
    if (&field == this)
        return *this;
    for (int x = 0; x < this->W; x++) {
        for (int y = 0; y < this->H; y++) {
            delete &this->_cells[x][y];
        }
    }
    delete this->_cells;

    this->H = field.H;
    this->W = field.W;

    this->_cells = new Cell*[this->W];          // выделили память под массив ячеек
    for (int x = 0; x < this->W; x++)     //
        _cells[x] = new Cell[this->H];   //

    for (int x = 0; x < this->W; x++) {
        for (int y = 0; y < this->H; y++) {
            this->_cells[x][y] = field._cells[x][y];
        }
    }
    return *this;
}
Field& Field::operator=(Field&& field)
{
    if (&field == this)
        return *this;
    for (int x = 0; x < this->W; x++) {
        for (int y = 0; y < this->H; y++) {
            delete &this->_cells[x][y];
        }
    }
    delete this->_cells;

    this->H = field.H;
    this->W = field.W;

    this->_cells = field._cells;
    return *this;
}

int Field::addObject(Object *object, int x, int y) {
    if ((x <= this->W) && (y <= this->H)){ //проверка на правильность координаты
        if (this->cells(x,y).innerObject) return 0; // проверка наличия объекта в ячейке
        if (object->x || object->y) return 0; // проверка - объект не должен находиться в другой ячейке
        this->cells(x,y).innerObject = object;
        object->x = x;
        object->y = y;
        return 1;
    }
    return 0;
}
int Field::addObject(Object *object, Cell &cell) {
    return this->addObject(object, cell.x, cell.y);
}

int Field::deleteObject(int x, int y) {
    if (this->cells(x,y).innerObject) {
        //this->cells(x,y).innerObject->cell = NULL;
        //delete this->cells(x,y).innerObject;
        this->cells(x,y).innerObject = NULL;
        return 1;
    } else { return 0; }
}
int Field::deleteObject(Cell &cell){
    if (cell.innerObject) {
        return this->deleteObject(cell.x, cell.y);
    } else {
        return 0;
    }
}


void Field::print(){
    int check_count_W = 2;
    int check_count_H = 1;
    int count_H = 1;
    int count_W = 1;
    char char_count_W;
    char char_count_H;
    int dec_H = 1;
    int dec_W = 1;
    char char_dec_W = 0;
    char char_dec_H = 0;
    int notCenter;

    for(int j=0; j<2+4*W; j++){
        if(j==0) std::cout<< '0';
        if((j==39 || j==79 || j==119 || j==159 || j==199)){
            char_dec_W = dec_W+'0';
            std::cout<< char_dec_W;
            dec_W++;
        }
        std::cout<<' ';

    }
    std::cout<<std::endl;

    for(int i=0; i<1+2*H; i++){
        for(int j=0; j<1+4*W; j++){

            notCenter = j-2;
            if(notCenter<0) notCenter=1;
            if(notCenter>0){
                while(1){
                    notCenter-=4;
                    if(notCenter==0){
                        break;
                    }
                    if(notCenter<0){
                        notCenter = 1;
                        break;
                    }
                }
            }

            if(j==0){
                if(!(i%20) && i!=0){
                    char_dec_H = dec_H+'0';
                    std::cout<< char_dec_H;
                    dec_H++;
                }else{
                    std::cout<<' ';
                }
            }

            if(!notCenter && (i%2) && (cells((j-2)/4 + 1, (i-1)/2 + 1).innerObject)){
                std::cout << cells((j-2)/4 + 1, (i-1)/2 + 1).innerObject->symb;
            }
            else if(!(j%4)){
                if(i==check_count_H){
                    char_count_H = count_H + '0';
                    std::cout << char_count_H;
                    count_H++;
                    if(count_H==10) count_H=0;
                    check_count_H+=2;
                }else{
                std::cout<<  '|';
                }
            }
            else if(!(i%2) ){
                if((j==check_count_W) && (i==0)){
                    char_count_W = count_W + '0';
                    std::cout << char_count_W;
                    count_W++;
                    if(count_W==10) count_W=0;
                    check_count_W+=4;
                }else{
                    std::cout<<  '-';
                }
            }

            else std::cout << ' ';
        }
        std::cout<<std::endl;
    }
}

Cell** Field::getCells() {
    return this->_cells;
}
Cell& Field::cells(int x, int y) {
    return this->_cells[x-1][y-1];
}

int Field::moveObject(int x1, int y1, int x2, int y2) {
    if (this->cells(x1, y1).innerObject) {
        if (this->cells(x1, y1).innerObject->canMove(x2, y2)) {
            this->cells(x2, y2).innerObject = cells(x1, y1).innerObject;
            cells(x1,y1).innerObject = NULL;
            this->cells(x2, y2).innerObject->x = x2;
            this->cells(x2, y2).innerObject->y = y2;
            return 1;
        }
    }
    return 0;
}
int Field::moveUnit(int x1, int y1, int x2, int y2) {
    if (this->cells(x1, y1).innerObject) {
        if (((Unit*)this->cells(x1, y1).innerObject)->canMove(x2, y2)) {
            this->cells(x2, y2).innerObject = cells(x1, y1).innerObject;
            cells(x1,y1).innerObject = NULL;
            this->cells(x2, y2).innerObject->x = x2;
            this->cells(x2, y2).innerObject->y = y2;
            return 1;
        }
    }
    return 0;
}
