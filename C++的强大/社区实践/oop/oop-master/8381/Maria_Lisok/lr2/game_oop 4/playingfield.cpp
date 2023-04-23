#include "playingfield.h"

PlayingField::~PlayingField(){}
MoveMediator::MoveMediator(PlayingField* playingField, Unit* playingFieldItem)
    : playingField(playingField), playingFieldItem(playingFieldItem)
{
    this->playingField->setMoveMediator(this);
    this->playingFieldItem->setMoveMediator(this);
}
void MoveMediator::moveObj(Unit *item, int x, int y)
{
    playingField->moveUnit(item, x, y);
}
unsigned PlayingField::getMaxItems() const
{
    return maxItems;
}

bool PlayingField::isCellFreeForUnit(size_t x, size_t y)
{
    return items[x][y]->isUnitFree();
}


bool PlayingField::addUnit(Unit * item, unsigned x, unsigned y, int baseNum)
{
    if(maxItems == countOfItems){
        throw length_error("you can't add item!"
                           "items limit full");
    }
    if(x >= width || y >= height){
        throw out_of_range("check position coordinates of unit");
    }
    if(!item){
        throw invalid_argument("item can't be empty");
    }
    if(!items[x][y]->isUnitFree()){
        throw invalid_argument("this cell of field have unit");
    }
    Proxy* p = new Proxy(items[x][y]->getLandscape());
    if(!p->canStand()){
        throw invalid_argument("item  can't add to this landscape");
    }

    Base* base = (baseNum == 1) ? base1 : base2;
    if(!base){
        throw invalid_argument("create base!!!!");
    }
    base->addUnit(item);
    items[x][y]->addUnit(item);
    items[x][y]->getUnit()->addObserver(this);
    countOfItems++;
    new MoveMediator(this, item);
    return true;
}

bool PlayingField::deleteUnit(unsigned x, unsigned y)
{
    if(x >= width || y >= height){
        throw out_of_range("check coordinates for delete item");
    }
    if(items[x][y]->isUnitFree()){
        return false;
    }
    if (base1)
        base1->deleteUnit(items[x][y]->getUnit());
    if (base2)
        base2->deleteUnit(items[x][y]->getUnit());
    items[x][y]->getUnit()->removeObserver(this);
    items[x][y]->delUnit();
    countOfItems--;
    return true;
}

bool PlayingField::addNeutral(NeutralObj * item, unsigned x, unsigned y)
{
    if(x >= width || y >= height){
        throw out_of_range("check position coordinates of unit");
    }
    if(!item){
        throw invalid_argument("item can't be empty");
    }
    if(items[x][y]->getNeutral()){
        throw invalid_argument("this cell of field have unit");
    }
    items[x][y]->addNeutral(item);
    return true;
}

bool PlayingField::deleteNeutral(unsigned x, unsigned y)
{
    if(x >= width || y >= height){
        throw out_of_range("check coordinates for delete item");
    }
    if(!items[x][y]->getNeutral()){
        return false;
    }
    items[x][y]->delNeutral();
    return true;
}



PlayingField::PlayingField(unsigned x, unsigned y, unsigned maxIt)
    :width(x), height(y), maxItems(maxIt), countOfItems(0), base1(nullptr), base2(nullptr)
{  
    items = new Cell**[width];
    for(unsigned i = 0; i < width; i++){
        items[i] = new Cell*[height];
        for(unsigned j = 0; j < height; j++){
            int k = (i+j) % 2;
            if (i % 3 == 0 && j % 3 == 0){
                items[i][j] = new Cell();
                items[i][j]->setLandscape(new Mountain());
            }
            else{
                if (k == 0){
                    items[i][j] = new Cell();
                    items[i][j]->setLandscape(new River());
                }
                if (k == 1){
                    items[i][j] = new Cell();
                    items[i][j]->setLandscape(new Forest());
                }
            }
        }
    }
}



PlayingField::PlayingField(const PlayingField& playingField)
    :width(playingField.width), height(playingField.height),
    maxItems(playingField.maxItems), countOfItems(playingField.countOfItems),
    base1(playingField.base1), base2(playingField.base2) 
{
    items = new Cell**[width];
    for(unsigned i = 0; i < width; i++){
        items[i] = new Cell*[height];
        for(unsigned j = 0; j < height; j++){
            if(playingField.items[i][j] != nullptr){
                items[i][j] = playingField.items[i][j];
            }else{
                items[i][j] = nullptr;
            }
        }
    }
}


PlayingField &PlayingField::operator=(const PlayingField & playingField)
{
    if(&playingField == this)
        return *this;
    for(unsigned i=0; i<width; i++){
        for(unsigned j=0; j<height; j++){
            delete items[i][j];
        }
        delete[] items[i];
    }
    delete[] items;
    items = new Cell**[width];
    for (unsigned i=0; i<width; i++)
    {
        items[i] = new Cell*[height];
        for (unsigned j=0; j<height; j++){
            if(playingField.items[i][j] != nullptr){
                items[i][j] = playingField.items[i][j];
                if(!items[i][j]->isUnitFree())
                    new MoveMediator(this, items[i][j]->getUnit());
            }else{
                items[i][j] = nullptr;
            }
        }
    }
    delete base1;
    base1 = playingField.base1;
    delete base2;
    base2 = playingField.base2;
    return *this;
}


PlayingField &PlayingField::operator=(PlayingField && playingField)
{
    if(&playingField == this)
        return *this;
    for(unsigned i=0; i<width; i++){
        for(unsigned j=0; j<height; j++){
            delete items[i][j];
        }
        delete[] items[i];
    }
    delete[] items;
    items = playingField.items;
    countOfItems = playingField.countOfItems;
    for(unsigned i=0; i < width; i++)
        delete []  playingField.items[i];
    delete [] playingField.items;
    base1 = playingField.base1;
    base2 = playingField.base2;
    return *this;
}


PlayingField::PlayingField(PlayingField && playingField)
    :width(playingField.width), height(playingField.height),
      maxItems(playingField.maxItems), countOfItems(playingField.countOfItems),
      items( new Cell**[width]), base1(playingField.base1), base2(playingField.base2)
{
    for(unsigned i=0; i < width; i++){
        items[i] = new Cell*[height];
        for(unsigned j = 0; j < height; j++){
            items[i][j] = playingField.items[i][j];
        }
    }
    for(unsigned i=0; i < width; i++)
        delete []  playingField.items[i];
    delete [] playingField.items;
}


unsigned PlayingField::getWidth() const
{
    return width;
}

unsigned PlayingField::getHeight() const
{
    return height;
}

bool PlayingField::moveUnit(Unit * item, int x , int y)
{
    for(int i=0; i < static_cast<int>(width); i++){
        for(int j=0; j < static_cast<int>(height); j++){

            if(items[i][j]->getUnit() == item){
                if(x + i >= static_cast<int>(width) || y +j >= static_cast<int>(height) || x + i < 0 || y + j < 0){
                    throw out_of_range("check position coordinates of item");
                }
                Proxy* p = new Proxy(items[x+i][y+j]->getLandscape());
                if(!p->canStand()){
                    throw invalid_argument("item  can't move to this landscape");
                }
                if(!item->isMovable()){
                    throw invalid_argument("item  must be movable");
                }
                if(!items[x+i][y+j]->isUnitFree()){
                    throw invalid_argument("there is other unit on this cell ");
                }
                if(items[x+i][y+j]->getNeutral()){
                    *(items[x+i][y+j]->getNeutral()) += *(items[i][j]->getUnit());
                    items[x+i][y+j]->delNeutral();
                }
                swap(items[x+i][y+j], items[i][j]);
                return true;
            }
        }
    }
    return false;
}

void PlayingField::setMoveMediator(MoveMediator * val)
{
    moveMediator = val;
}


string PlayingField::getAbout(unsigned x, unsigned y)
{

    if (x >= width || y >= height)
        return "X=" + std::to_string(x) + ",Y=" + std::to_string(y) + ": is out of field\n";

    return "At X=" + std::to_string(x) + ",Y=" + std::to_string(y) + " is set:\n" + items[x][y]->characteristic(x, y);
}

Cell *PlayingField::getCell(unsigned x, unsigned y)
{
    if (x >= width || y >= height)
        throw out_of_range("coords are not on field");
    return items[x][y];
}

Cell *PlayingField::findUnit(Unit *unit)
{
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            if (items[i][j]->getUnit() == unit){
                return items[i][j];
            }
        }
    }
    return nullptr;
}

void PlayingField::update(Subject * subject)
{
    deleteUnit(subject);
}

void PlayingField::deleteUnit(Subject * unit)
{
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (unit == items[i][j]->getUnit()) {
                items[i][j]->delUnit();
                countOfItems--;
                if (base1)
                    base1->deleteUnit(unit);
                if (base2)
                    base2->deleteUnit(unit);
                unit->removeObserver(this);
                return;
            }
        }
    }
}

void PlayingField::setBase(Base* base)
{
    if(base->getMaxCount() <= 0)
        throw invalid_argument("maxCount must be >0");
    if(base->getHealth() <= 0)
        throw invalid_argument("health must be >0");
    if(base->getX() > width)
        throw invalid_argument("width must be < curr width");
    if(base->getY() > height)
        throw invalid_argument("height must be < curr height");

    if (base->getBaseNumb() == 1){
        if(base1){
            throw invalid_argument("there is base with such num(1)");
        }
        base1 = new Base(base->getMaxCount(), base->getHealth(), base->getX(), base->getY(), base->getBaseNumb());

    }
    else if (base->getBaseNumb() == 2){
        if(base2){
            throw invalid_argument("there is base with such num(2)");
        }
        base2 = new Base(base->getMaxCount(), base->getHealth(), base->getX(), base->getY(), base->getBaseNumb());

    }else{
        throw invalid_argument("there are two num of bases 1 and 2");
    }
}

string PlayingField::printBase(Base *base)
{
    Unit* unit;
    Cell* point;
    string str{};
    str+="Base ";
    str += base->getBaseNumb() + "\n";
    std::cout<<"Count of units in base " << base->getUnitCount() << endl;
    for (int i = 0; i < base->getUnitCount(); i++){
        unit = base->getCurrUnit();
        point = findUnit(unit);
        str.append( unit->characteristic()+"\n");
    }
    return str;
}

Base *PlayingField::getBase1() const
{
    return base1;
}

Base *PlayingField::getBase2() const
{
    return base2;
}

PlayingFieldIterator::PlayingFieldIterator(PlayingField * current)
    :playingField(current), curWidth(0), curHeight(0)
{}

PlayingFieldIterator &PlayingFieldIterator::operator =(const PlayingFieldIterator & other)
{
    if (this != &other)
    {
        playingField = other.playingField;
    }

    return *this;
}

Cell *PlayingFieldIterator::operator ++()
{
    curWidth++;
    curHeight++;
    if(playingField->getCell(curWidth, curHeight) == nullptr)
        return nullptr;
    return playingField->getCell(curWidth, curHeight);
}

Cell* PlayingFieldIterator::operator ++(int x)
{
    unsigned iWidth = curWidth;
    unsigned iHeight = curHeight;
    curWidth++;
    curHeight++;
    if(playingField->getCell(curWidth, curHeight) == nullptr)
        return nullptr;
    return playingField->getCell(iWidth, iHeight);
}



Cell *PlayingFieldIterator::operator ->()
{
    return playingField->getCell(curWidth, curHeight);
}
