//
// Created by Artem Butko on 14/05/2020.
//

#include "Field.h"
#include "../../Exсeptions/OutOfRange/OutOfRangeError.h"

Field::Field(int height, int width, int numberOfPlayers)
{
    this->height = height;
    this->width = width;
    this->objCount = 0;
    this->objLimit = width * height;
    basesOnField.resize(numberOfPlayers);
    for (int i = 0; i != numberOfPlayers; ++i) basesOnField[numberOfPlayers] = nullptr;
    this->logging = new LoggingProxy;
    int land;
    int neutral;
    std::srand(unsigned(std::time(nullptr)));
    field = new Tile*[height];

    for (int i = 0; i < height; ++i)
        field[i] = new Tile[width];
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
        {

            land = rand() % 4;
            if (land == 0) field[i][j].landscape = landscapeFactory.getForest();
            else if (land == 1) field[i][j].landscape = landscapeFactory.getMountain();
            else if (land == 2) field[i][j].landscape = landscapeFactory.getWater();
            else field[i][j].landscape = nullptr;

            neutral = rand() % 16;
            if (neutral == 0) field[i][j].neutral = neutralFactory.createTrap();
            else if (neutral == 1) field[i][j].neutral = neutralFactory.createAidKit();
            else if (neutral == 2) field[i][j].neutral = neutralFactory.createCurse();
            else if (neutral == 3) field[i][j].neutral = neutralFactory.createPotion();
            else field[i][j].neutral = nullptr;

            field[i][j].object = nullptr;
            field[i][j].x = i;
            field[i][j].y = j;

            field[i][j].isBrightView = false;
            field[i][j].isDarkView = false;
            field[i][j].isUndeadView = false;
        }
}

Field::Field(const Field &other)
{
    height = other.height;
    width = other.width;
    objLimit = other.objLimit;
    objCount = other.objCount;

    field = new Tile*[height];
    for (int i = 0; i < height; ++i)
        field[i] = new Tile[width];

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            field[i][j] = other.field[i][j];
}

Field::Field(Field&& other)
{
    height = other.height;
    width = other.width;
    objLimit = other.objLimit;
    objCount = other.objCount;

    field = new Tile*[height];
    for (int i = 0; i < height; ++i)
        field[i] = new Tile[width];

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            field[i][j] = other.field[i][j];

    for (int i = 0; i < other.height; ++i)
        delete[] other.field[i];
    delete[] other.field;
}

Field& Field::operator=(const Field& other)
{
    this->height = other.height;
    this->width = other.width;
    this->base = other.base;

    this->field = new Tile*[height];
    for (int i = 0; i < height; ++i)
    {
        field[i] = new Tile[width];
        for (int j = 0; j < width; ++j)
            field[i][j] = other.field[i][j];
    }
    return *this;
};

void Field::addObject(Object *object, int x, int y)
{
    if (objCount > objLimit) throw OutOfRangeError("Field::addObject()", "objects on field can't exceed the limit");

    field[x][y].object = object;
    field[x][y].x = x;
    field[x][y].y = y;
    field[x][y].object->x = x;
    field[x][y].object->y = y;

    logging->loggingGetUnit(field[x][y].object, x, y);
    objCount++;
}

void Field::moveObject(int x, int y, int i, int j)
{
    if (field[i][j].neutral != nullptr)
    {
        std::cout << "UNIT on neutral object " << field[i][j].neutral->id << "!" << std::endl;
        field[i][j].neutral->action->impact(field[x][y].object);
        field[x][y].object->getInformation();
        field[i][j].neutral = nullptr;
    }
    if (field[i][j].landscape != nullptr)
    {
        std::cout << "UNIT on landscape  " << field[i][j].landscape->getID() << "!" << std::endl;
        field[i][j].landscape->getEffect(field[x][y].object);
        field[x][y].object->getInformation();
    }
    logging->loggingMoveUnit(field[x][y].object, x, y, i, j);

    field[i][j].object = field[x][y].object;
    field[x][y].object = nullptr;

    if (field[i][j].object->health.get() < 0)
    {
        std::cout << field[i][j].object->id << " is dead!" << std::endl;
        field[i][j].object->death();
        this->deleteObject(i, j);
    }
}

void Field::deleteObject(int x, int y)
{
    field[x][y].object = nullptr;
    objCount --;
}

void Field::show(char side)
{
    std::cout << "[\\]";
    for (int i = 0; i < width; ++i)
        std::cout << "[" << i << "]";
    std::cout << "--Y" << std::endl;
    for (int i = 0; i < height; ++i)
    {
        std::cout << "[" << i << "]";
        for (int j = 0; j < width; ++j)
        {
            bool isNeutral = (field[i][j].neutral != nullptr);
            bool isObject = (field[i][j].object != nullptr);
            bool isLandscape = (field[i][j].landscape != nullptr);
            if (side == 'M')
            {
                if (isNeutral) std::cout << "[" << field[i][j].neutral->id << "]";
                else if (isObject && (field[i][j].object->id == 'B' || field[i][j].object->id == 'D'||  field[i][j].object->id == 'U')) std::cout << "{" << field[i][j].object->id << "}";
                else std::cout << "[ ]";
                if (isObject && (field[i][j].object->id == 'B' || field[i][j].object->id == 'D'||  field[i][j].object->id == 'U'))
                {
                    field[i][j].isBrightView = true;
                    field[i][j].isUndeadView = true;
                    field[i][j].isDarkView = true;
                }
            }
            else if (side == 'B')
            {
                bool isVision = field[i][j].isBrightView;
                if (!isVision) std::cout << "( )";
                else if (isObject && (field[i][j].object->id == 'B' || field[i][j].object->id == 'D'||  field[i][j].object->id == 'U')) std::cout << "{" << field[i][j].object->id << "}";
                else if (isLandscape && isObject && field[i][j].object != nullptr) std::cout << field[i][j].landscape->getID() << field[i][j].object->id << field[i][j].landscape->getID();
                else if (!isLandscape && isObject && field[i][j].object != nullptr) std::cout << "[" << field[i][j].object->id << "]";
                else if (isLandscape && isNeutral) std::cout << field[i][j].landscape->getID() << field[i][j].neutral->id << field[i][j].landscape->getID();
                else if (!isLandscape && isNeutral) std::cout << "[" << field[i][j].neutral->id << "]";
                else if (isLandscape) std::cout << field[i][j].landscape->getID() << " " << field[i][j].landscape->getID();
                else std::cout << "[ ]";
            }
            else if (side == 'D')
            {
                bool isVision = field[i][j].isDarkView;
                if (!isVision) std::cout << "( )";
                else if (isObject && (field[i][j].object->id == 'B' || field[i][j].object->id == 'D'||  field[i][j].object->id == 'U')) std::cout << "{" << field[i][j].object->id << "}";
                else if (isLandscape && isObject && field[i][j].object != nullptr) std::cout << field[i][j].landscape->getID() << field[i][j].object->id << field[i][j].landscape->getID();
                else if (!isLandscape && isObject && field[i][j].object != nullptr) std::cout << "[" << field[i][j].object->id << "]";
                else if (isLandscape && isNeutral) std::cout << field[i][j].landscape->getID() << field[i][j].neutral->id << field[i][j].landscape->getID();
                else if (!isLandscape && isNeutral) std::cout << "[" << field[i][j].neutral->id << "]";
                else if (isLandscape) std::cout << field[i][j].landscape->getID() << " " << field[i][j].landscape->getID();
                else std::cout << "[ ]";
            }
            else if (side == 'U')
            {
                bool isVision = field[i][j].isUndeadView;
                if (!isVision) std::cout << "( )";
                else if (isObject && (field[i][j].object->id == 'B' || field[i][j].object->id == 'D'||  field[i][j].object->id == 'U')) std::cout << "{" << field[i][j].object->id << "}";
                else if (isLandscape && isObject) std::cout << field[i][j].landscape->getID() << field[i][j].object->id << field[i][j].landscape->getID();
                else if (!isLandscape && isObject) std::cout << "[" << field[i][j].object->id << "]";
                else if (isLandscape && isNeutral) std::cout << field[i][j].landscape->getID() << field[i][j].neutral->id << field[i][j].landscape->getID();
                else if (!isLandscape && isNeutral) std::cout << "[" << field[i][j].neutral->id << "]";
                else if (isLandscape) std::cout << field[i][j].landscape->getID() << " " << field[i][j].landscape->getID();
                else std::cout << "[ ]";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "| "<< std::endl;
    std::cout << "X" << std::endl;
}

Field::~Field()
{
    for (int i = 0; i < height; ++i) delete[] field[i];
    delete[] field;
}

FieldIterator *Field::iterator()
{
    return (new FieldIterator(*this));
}

FieldIterator *Field::end()
{
    auto* end = new FieldIterator(*this);
    end->end();
    return end;
}

FieldIterator* Field::begin()
{
    auto* begin = new FieldIterator(*this);
    begin->begin();
    return begin;
}

void Field::createBase(int x, int y, int unitLimit, char id, int number)
{
    if (x + 1 < height && y + 1 < width && x >= 0 && y >= 0)
    {
        if (field[x][y].object == nullptr && field[x + 1][y + 1].object == nullptr && field[x][y + 1].object == nullptr && field[x + 1][y].object == nullptr)
        {
            basesOnField[number] = new Base(this, x, y, unitLimit);
            basesOnField[number]->x = x;
            basesOnField[number]->y = y;
            basesOnField[number]->id = id;
            field[x][y].object = basesOnField[number];
            field[x + 1][y].object = field[x][y].object;
            field[x][y + 1].object = field[x][y].object;
            field[x + 1][y + 1].object = field[x][y].object;
            logging->loggingCreateBase(basesOnField[number]);
            field[x][y].landscape = nullptr;
            field[x + 1][y].landscape = nullptr;
            field[x][y + 1].landscape = nullptr;
            field[x + 1][y + 1].landscape = nullptr;
            field[x][y].neutral = nullptr;
            field[x + 1][y].neutral = nullptr;
            field[x][y + 1].neutral = nullptr;
            field[x + 1][y + 1].neutral = nullptr;
            if (number == 0)
            {
                field[x + 2][y].isBrightView = true;
                field[x + 2][y + 1].isBrightView = true;
                field[x + 2][y + 2].isBrightView = true;
                field[x + 1][y + 2].isBrightView = true;
                field[x][y + 2].isBrightView = true;
            }
            else if (number == 1)
            {
                field[x - 1][y].isDarkView = true;
                field[x - 1][y + 1].isDarkView = true;
                field[x - 1][y - 1].isDarkView = true;
                field[x][y - 1].isDarkView = true;
                field[x + 1][y - 1].isDarkView = true;
            }
            else if (number == 2)
            {
                field[x - 1][y].isUndeadView = true;
                field[x - 1][y + 1].isUndeadView = true;
                field[x - 1][y + 2].isUndeadView = true;
                field[x][y + 2].isUndeadView = true;
                field[x + 1][y + 2].isUndeadView = true;
            }
        }
    }
}

void Field::makeDamage(int x, int y, int i, int j)
{
     static_cast<IUnit*>(field[x][y].object)->makeDamage(static_cast<IUnit*>(field[x][y].object)->damage.getDamage(), field[i][j].object);
     logging->loggingAttackUnit(field[x][y].object, x, y, i, j);
     if (field[i][j].object->health.get() < 0)
     {
         std::cout << field[i][j].object->id << " is dead!" << std::endl;
         field[i][j].object->death();
         this->deleteObject(i, j);
     }
     else field[i][j].object->getInformation();
}

Snapshot* Field::createSnapshot(std::string mode)
{
    Snapshot* snap;
    if (mode == "save")
    {
        if (base != nullptr) snap = new Snapshot(this, height, width, objLimit, objCount, base->unitLimit, base->unitCount);
        snap = new Snapshot(this, height, width, objLimit, objCount, 0, 0);
    }
    else
    {
        snap = new Snapshot(this);
    }
    return snap;
}


void Field::getVision(char side, int x, int y)
{

    if (side == 'B')
    {
        field[x][y].isBrightView = true;
        if (x + 1 < height) field[x + 1][y].isBrightView = true;
        if (x - 1 >= 0) field [x - 1][y].isBrightView = true;
        if (y + 1 < width) field[x][y + 1].isBrightView = true;
        if (y - 1 >= 0) field[x][y - 1].isBrightView = true;
        if (x + 1 < height && y - 1 >= 0) field[x + 1][y - 1].isBrightView = true;
        if (x + 1 < height && y + 1 < width) field[x + 1][y + 1].isBrightView = true;
        if (x - 1 >= height && y - 1 >= 0) field[x - 1][y - 1].isBrightView = true;
        if (x - 1 < height && y + 1 < width) field[x - 1][y + 1].isBrightView = true;
    }
    else if (side == 'D')
    {
        field[x][y].isDarkView = true;
        if (x + 1 < height) field[x + 1][y].isDarkView = true;
        if (x - 1 >= 0) field [x - 1][y].isDarkView = true;
        if (y + 1 < width) field[x][y + 1].isDarkView  = true;
        if (y - 1 >= 0) field[x][y - 1].isDarkView  = true;
        if (x + 1 < height && y - 1 >= 0) field[x + 1][y - 1].isDarkView = true;
        if (x + 1 < height && y + 1 < width) field[x + 1][y + 1].isDarkView = true;
        if (x - 1 >= height && y - 1 >= 0) field[x - 1][y - 1].isDarkView = true;
        if (x - 1 < height && y + 1 < width) field[x - 1][y + 1].isDarkView = true;
    }
    else
    {
        field[x][y].isUndeadView = true;
        if (x + 1 < height) field[x + 1][y].isUndeadView = true;
        if (x - 1 >= 0) field[x - 1][y].isUndeadView = true;
        if (y + 1 < width) field[x][y + 1].isUndeadView  = true;
        if (y - 1 >= 0) field[x][y - 1].isUndeadView  = true;
        if (x + 1 < height && y - 1 >= 0) field[x + 1][y - 1].isUndeadView = true;
        if (x + 1 < height && y + 1 < width) field[x + 1][y + 1].isUndeadView = true;
        if (x - 1 >= height && y - 1 >= 0) field[x - 1][y - 1].isUndeadView = true;
        if (x - 1 < height && y + 1 < width) field[x - 1][y + 1].isUndeadView = true;
    }
}
