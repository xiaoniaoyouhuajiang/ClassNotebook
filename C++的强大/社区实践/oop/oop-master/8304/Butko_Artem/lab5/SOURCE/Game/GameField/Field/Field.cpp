//
// Created by Artem Butko on 14/05/2020.
//

#include "Field.h"

Field::Field(int height, int width)
{
    this->height = height;
    this->width = width;
    this->objCount = 0;
    this->objLimit = width * height;
    this->base = nullptr;
    this->logging = new LoggingProxy;
    int land;
    int neutral;
    std::srand(unsigned(std::time(nullptr)));
    field = new Tale*[height];

    for (int i = 0; i < height; ++i)
        field[i] = new Tale[width];
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
        }
}

Field::Field(const Field &other)
{
    height = other.height;
    width = other.width;
    objLimit = other.objLimit;
    objCount = other.objCount;

    field = new Tale*[height];
    for (int i = 0; i < height; ++i)
        field[i] = new Tale[width];

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

    field = new Tale*[height];
    for (int i = 0; i < height; ++i)
        field[i] = new Tale[width];

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

    this->field = new Tale*[height];
    for (int i = 0; i < height; ++i)
    {
        field[i] = new Tale[width];
        for (int j = 0; j < width; ++j)
            field[i][j] = other.field[i][j];
    }
    return *this;
};

int Field::addObject(Object *object, int x, int y)
{
    if (objCount > objLimit)
    {
        std::cout << "ERROR: limit of objects on the field is exceeded!" << std::endl;
        return 1;
    }
    if (field[x][y].object != nullptr)
    {
        std::cout << "ERROR: this tale is not empty!" << std::endl;
        return 1;
    }

    field[x][y].object = object;
    field[x][y].x = x;
    field[x][y].y = y;
    field[x][y].object->x = x;
    field[x][y].object->y = y;
    logging->loggingGetUnit(field[x][y].object, x, y);
    objCount++;
    return 0;
}

int Field::moveObject(int x, int y, int i, int j)
{
    /*TODO выход за границы поля*/
    if (field[x][y].object != nullptr && field[i][j].object == nullptr && field[x][y].object->id != 'B')
    {
        if (field[x][y].object->id == 'M' || field[x][y].object->id == 'W' || field[x][y].object->id == 'K' || field[x][y].object->id == 'S' || field[x][y].object->id == 'A' || field[x][y].object->id == 'C')
        {
            if (field[i][j].neutral != nullptr)
            {
                field[i][j].neutral->action->impact(field[x][y].object);
                std::cout << "UNIT on neutral object " << field[i][j].neutral->id << "!" << std::endl;
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
        }

        field[i][j].object = field[x][y].object;
        field[x][y].object = nullptr;
    }
    else
    {
        std::cout << "ERROR: impossible to move!" << std::endl;
        return 1;
    }
    return 0;
}

int Field::deleteObject(int x, int y)
{
    if (field[x][y].object != nullptr)
    {
        field[x][y].object = nullptr;
        objCount --;
    }
    else
    {
        std::cout << "ERROR: impossible to delete!" << std::endl;
        return 1;
    }
    return 0;
}

void Field::show()
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
            if (!isNeutral && !isObject && !isLandscape) std::cout << "[ ]";
            else if (isObject && !isLandscape) std::cout << '[' << field[i][j].object->id << ']';
            else if (!isObject && isLandscape && isNeutral) std::cout << field[i][j].landscape->getID() << field[i][j].neutral->id << field[i][j].landscape->getID();
            else if (!isObject && !isNeutral && isLandscape) std::cout << field[i][j].landscape->getID() << ' ' << field[i][j].landscape->getID();
            else if (isLandscape && isObject) std::cout << field[i][j].landscape->getID() << field[i][j].object->id << field[i][j].landscape->getID();
            else std::cout << '[' << field[i][j].neutral->id << ']';
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

FieldIterator *Field::end() {
    auto* end = new FieldIterator(*this);
    end->end();
    return end;
}

FieldIterator* Field::begin() {
    auto* begin = new FieldIterator(*this);
    begin->begin();
    return begin;
}

int Field::createBase(int x, int y, int unitLimit)
{
    if (x + 1 < height && y + 1 < width && x >= 0 && y >= 0)
    {
        if (field[x][y].object == nullptr && field[x + 1][y + 1].object == nullptr && field[x][y + 1].object == nullptr && field[x + 1][y].object == nullptr)
        {
            base = new Base(this, x, y, unitLimit);
            base->x = x;
            base->y = y;
            field[x][y].object = base;
            field[x + 1][y].object = field[x][y].object;
            field[x][y + 1].object = field[x][y].object;
            field[x + 1][y + 1].object = field[x][y].object;
            logging->loggingCreateBase(base);
            field[x][y].landscape = nullptr;
            field[x + 1][y].landscape = nullptr;
            field[x][y + 1].landscape = nullptr;
            field[x + 1][y + 1].landscape = nullptr;

        }
    }

    return 0;
}

void Field::immediateDeath(int x, int y)
{
    field[x][y].object->death();
    this->deleteObject(x, y);
}

void Field::makeDamage(int x, int y, int i, int j)
{
    if (field[i][j].object != nullptr && field[x][y].object != nullptr && (field[x][y].object->id == 'M' || field[x][y].object->id == 'W'  || field[x][y].object->id == 'K' || field[x][y].object->id == 'S' || field[x][y].object->id == 'A' || field[x][y].object->id == 'C' ))
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
    else std::cout << "ERROR: impossible to attack!" << std::endl;
}

Object *Field::getObject(int x, int y)
{
    if(field[x][y].object != nullptr) return field[x][y].object;
    else return nullptr;
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

