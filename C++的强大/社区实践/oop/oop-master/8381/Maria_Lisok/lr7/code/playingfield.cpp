#include "playingfield.h"
#include "exception.h"

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


bool PlayingField::addUnit(Unit * item, unsigned x, unsigned y)
{
    if(maxItems == countOfItems){
        throw SimpleFieldException("you can't add item!"
                           "items limit full");
    }
    if(x >= width || y >= height){
        throw CoordsException(x, y, width, height);
    }
    if(!item){
        throw SimpleFieldException("item can't be empty");
    }
    if(!items[x][y]->isUnitFree()){
        throw CellBusyExpeption(x, y);
    }
    Proxy* p = new Proxy(items[x][y]->getLandscape());
    if(!p->canStand()){
        throw LandExeption(x, y);
    }
    items[x][y]->addUnit(item);
    items[x][y]->getUnit()->addObserver(this);
    countOfItems++;
    new MoveMediator(this, item);
    return true;
}

bool PlayingField::deleteUnit(unsigned x, unsigned y)
{
    if(x >= width || y >= height){
        throw CoordsException(x, y, width, height);
    }
    if(items[x][y]->isUnitFree()){
        return false;
    }
    items[x][y]->getUnit()->removeObserver(this);
    items[x][y]->delUnit();
    countOfItems--;
    return true;
}

bool PlayingField::addNeutral(NeutralObj * item, unsigned x, unsigned y)
{
    if(x >= width || y >= height){
        throw CoordsException(x, y, width, height);
    }
    if(!item){
        throw SimpleFieldException("item can't be empty");
    }
    if(items[x][y]->getNeutral()){
        throw CellBusyExpeption(x, y);
    }
    items[x][y]->addNeutral(item);
    return true;
}

bool PlayingField::deleteNeutral(unsigned x, unsigned y)
{
    if(x >= width || y >= height){
        throw CoordsException(x, y, width, height);
    }
    if(!items[x][y]->getNeutral()){
        return false;
    }
    items[x][y]->delNeutral();
    return true;
}

bool PlayingField::createNeutral(NeutralType net, unsigned x, unsigned y)
{
    NeutralObj* obj=nullptr;
    switch(net){
    case  HELMET:
        obj = new GetArmor(new Helmet());
        break;
    case MITTENS:
        obj = new GetArmor(new Mittens());
        break;
    case SABATON:
        obj = new GetArmor(new Sabaton());
        break;
    case   BANDAGE:
        obj = new GetMedicine(new Bandage());
        break;
    case   POWERPOTION:
        obj = new GetMedicine(new PowerPotion());
        break;
    case   COVID19:
        obj = new DrinkPoison(new Covid19());
        break;
    case CODID37:
        obj = new DrinkPoison(new Covid37());
        break;
    case SWORD:
        obj = new GetWeapon(new Sword());
        break;
    case HATCHET:
        obj = new GetWeapon(new Hatchet());
        break;

    }
    return addNeutral(obj, x, y);
}

PlayingField::PlayingField(unsigned x, unsigned y, unsigned maxIt)
    :width(x), height(y), maxItems(maxIt), countOfItems(0)
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
    maxItems(playingField.maxItems), countOfItems(playingField.countOfItems)

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
    return *this;
}


PlayingField::PlayingField(PlayingField && playingField)
    :width(playingField.width), height(playingField.height),
      maxItems(playingField.maxItems), countOfItems(playingField.countOfItems),
      items( new Cell**[width])
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
                    throw CoordsException(x + i, y+j, width, height);
                }
                Proxy* p = new Proxy(items[x+i][y+j]->getLandscape());
                if(!p->canStand()){
                    throw LandExeption(x+i, y+j);
                }
                if(!item->isMovable()){
                    throw SimpleFieldException("item  must be movable");
                }
                if(!items[x+i][y+j]->isUnitFree()){
                    throw  CellBusyExpeption(x + i, y+j);
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
        throw CoordsException(x, y, width, height);
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
                unit->removeObserver(this);
                return;
            }
        }
    }
}

void PlayingField::addBase(Base* base)
{
    if(base->getMaxCount() <= 0)
        throw SimpleFieldException("maxCount must be >0");
    if(base->getHealth() <= 0)
        throw SimpleFieldException("health must be >0");
    unsigned posX = static_cast<unsigned>(base->getX());
    unsigned posY = static_cast<unsigned>(base->getY());
    if(posX > width || posY > height)
        throw CoordsException(posX, posY, width, height);
    Proxy* p = new Proxy(items[posX][posY]->getLandscape());
    if(!p->canStand()){
        throw LandExeption(posX, posY);
    }
    if(items[posX][posY]->getBase()){
        throw CellBusyExpeption(posX, posY);
    }
    items[posX][posY]->setBase(base);
}

unsigned PlayingField::getCountOfItems() const
{
    return countOfItems;
}

void PlayingField::setCreateMediator(CreateMediator *value)
{
    createMediator = value;
}

bool PlayingField::addLandscape(Landscape * landscape, unsigned x, unsigned y)
{
    if (x >= width || y >= height)
        throw CoordsException(x, y, width, height);
    items[x][y]->setLandscape(landscape);
    return true;
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
