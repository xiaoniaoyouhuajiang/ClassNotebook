#include "gamefield.h"

GameField::GameField(int x, int y, int maxCount, int isCorrectCreated) : isCorrectCreated(isCorrectCreated), x(x), y(y), unitCount(0), maxCount(maxCount), base1(nullptr), base2(nullptr), base3(nullptr)
{		
    pointsMap = new Point** [y];

    for (int i = 0; i < y; i++) {
        pointsMap[i] = new Point*[x];
        for (int j = 0; j < x; j++){
            pointsMap[i][j] = new Point;
            pointsMap[i][j]->unit = nullptr;
            pointsMap[i][j]->base = nullptr;
            pointsMap[i][j]->nObject = nullptr;
            pointsMap[i][j]->y = i;
            pointsMap[i][j]->x = j;

            int k = (i+j) % 2;
            if (i % 3 == 0 && j % 3 == 0)
                pointsMap[i][j]->landscape = new Mountain();
            else{
                if (k == 0)
                    pointsMap[i][j]->landscape = new River();
                if (k == 1)
                    pointsMap[i][j]->landscape = new Forest();
            }
            if (i == 0 && j == 0)
                pointsMap[i][j]->nObject = new DrinkPoison();
            if (i == 0 && j == x - 1)
                pointsMap[i][j]->nObject = new GetArmor();
            if (i == y - 1 && j == 0)
                pointsMap[i][j]->nObject = new GetWeapon();
            if (i == y - 1 && j == x - 1)
                pointsMap[i][j]->nObject = new GetMedicine();
        }
    }
    LoggerProxy::fieldCreation(this);
}

//Конструктор копирования
GameField::GameField(const GameField &field) : isCorrectCreated(isCorrectCreated), x(field.x), y(field.y), unitCount(field.unitCount), maxCount(field.maxCount),
    pointsMap(new Point** [field.y]), base1(field.base1), base2(field.base2), base3(field.base3)
{
    for (int i = 0; i < y; i++){
        pointsMap[i] = new Point*[x];
        for (int j = 0; j < x; j++)
            pointsMap[i][j] = field.pointsMap[i][j];
    }
    LoggerProxy::fieldCreation(this);
}

GameField& GameField::operator=(const GameField& field)
{
    this->x = field.x;
    this->y = field.y;
    this->unitCount = field.unitCount;
    this->maxCount = field.maxCount;
    this->base1 = field.base1;
    this->base2 = field.base2;
    this->base3 = field.base3;
    this->isCorrectCreated = field.isCorrectCreated;
    this->pointsMap = new Point** [field.y];
    for (int i = 0; i < y; i++){
        pointsMap[i] = new Point*[x];
        for (int j = 0; j < x; j++)
            pointsMap[i][j] = field.pointsMap[i][j];
    }
    return *this;
}

//Конструктор перемещения
GameField::GameField(GameField &&field) : x(field.x), y(field.y), unitCount(field.unitCount), maxCount(field.maxCount),
    pointsMap(new Point**[field.y]), base1(field.base1), base2(field.base2), base3(field.base3)
{
    for (int i = 0; i < y; i++) {
        pointsMap[i] = new Point*[x];
        for (int j = 0; j < x; j++)
            pointsMap[i][j] = field.pointsMap[i][j];
    }
    for(int i = 0; i < y; i++)
        delete[] field.pointsMap[i];
    delete[] field.pointsMap;
    LoggerProxy::fieldCreation(this);
}

bool GameField::canStand(std::string unit, int xx, int yy)
{
    if ((xx <= this->x - 1) && (yy <= this->y - 1) && (xx >= 0) && (yy >= 0) && (!pointsMap[yy][xx]->unit)
            && pointsMap[yy][xx]->landscape->canStand(unit) && (!pointsMap[yy][xx]->base))
        return true;
    else
        return false;
}

bool GameField::createUnit(std::string unit, Base* base, Mediator* mediator)
{
    if ((maxCount > unitCount) && (unit == unitsNames[0] || unit == unitsNames[1] || unit == unitsNames[2]
                                   || unit == unitsNames[3] || unit == unitsNames[4] || unit == unitsNames[5])){
        int xx = base->getX();
        int yy = base->getY();
        int xPos;
        int yPos;

        if (canStand(unit, xx - 1, yy - 1)) {xPos = xx-1; yPos = yy-1;}
        else if (canStand(unit, xx, yy - 1)) {xPos = xx; yPos = yy-1;}
        else if (canStand(unit, xx + 1, yy - 1)) {xPos = xx+1; yPos = yy-1;}
        else if (canStand(unit, xx - 1, yy)) {xPos = xx-1; yPos = yy;}
        else if (canStand(unit, xx + 1, yy)) {xPos = xx+1; yPos = yy;}
        else if (canStand(unit, xx - 1, yy + 1)) {xPos = xx-1; yPos = yy+1;}
        else if (canStand(unit, xx, yy + 1)) {xPos = xx; yPos = yy+1;}
        else if (canStand(unit, xx + 1, yy + 1)) {xPos = xx+1; yPos = yy+1;}
        else{
            std::cout << "No more place around the base\n";
            return false;
        }

        pointsMap[yPos][xPos]->unit = base->createUnit(unit);
        pointsMap[yPos][xPos]->unit->addObserver(this);
        pointsMap[yPos][xPos]->unit->setMediator(mediator);
        unitCount++;
        LoggerProxy::unitCreation(pointsMap[yPos][xPos]->unit, xPos, yPos, (base == base1) ? 1 : 2);
        return true;
    } else {
        if (maxCount <= unitCount)
            std::cout << "Max unit count on field\n";
        else
            std::cout << "Unit's name is wrong\n";
        return false;
    }
}

Unit* GameField::createUnit(int xx, int yy, std::string unit, int baseNumb, Mediator* mediator)
{
    Base* base = (baseNumb == 1) ? base1 : base2;
    pointsMap[yy][xx]->unit = base->createUnit(unit);
    pointsMap[yy][xx]->unit->addObserver(this);
    pointsMap[yy][xx]->unit->setMediator(mediator);
    unitCount++;
    LoggerProxy::unitCreation(pointsMap[yy][xx]->unit, xx, yy, baseNumb);
    return pointsMap[yy][xx]->unit;
}

void GameField::deleteUnit(Subject* unit)
{
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (unit == pointsMap[i][j]->unit) {
                pointsMap[i][j]->unit = nullptr;
                unitCount--;
                if (base1)
                    base1->deleteUnit(unit);
                if (base2)
                    base2->deleteUnit(unit);
                unit->deleteObserver(this);
                return;
            }
        }
    }
}

Point* GameField::findUnit(Unit *unit)
{
    for (int i = 0; i < this->y; i++){
        for (int j = 0; j < this->x; j++){
            if (pointsMap[i][j]->unit == unit){
                return pointsMap[i][j];
            }
        }
    }
    return nullptr;
}

void GameField::setUnit(Unit* unit, int xx, int yy, Base* base)
{
    pointsMap[yy][xx]->unit = base->createUnit(unit->getName());
    unitCount++;
}

void GameField::moveUnit(Unit* unit, int xx, int yy, Base* base)
{
    if ((xx <= this->x - 1) && (yy <= this->y - 1) && (xx >= 0) && (yy >= 0) && (!pointsMap[yy][xx]->unit) &&
            (!pointsMap[yy][xx]->base) && pointsMap[yy][xx]->landscape->canStand(unit)) {
        deleteUnit(unit);
        setUnit(unit, xx, yy, base);
        LoggerProxy::unitMoving(unit, xx, yy, (base == base1) ? 1 : 2);
    }
    else{
        std::cout << "Can't move\n";
    }
}

void GameField::moveUnitLeft(Unit *unit, Base* base)
{
    Point* p = this->findUnit(unit);
    moveUnit(unit, p->x - 1, p->y, base);
}

void GameField::moveUnitRight(Unit *unit, Base* base)
{
    Point* p = this->findUnit(unit);
    moveUnit(unit, p->x + 1, p->y, base);
}

void GameField::moveUnitUp(Unit *unit, Base* base)
{
    Point* p = this->findUnit(unit);
    moveUnit(unit, p->x, p->y - 1, base);
}

void GameField::moveUnitDown(Unit *unit, Base* base)
{
    Point* p = this->findUnit(unit);
    moveUnit(unit, p->x, p->y + 1, base);
}

void GameField::printAll() const
{
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (pointsMap[i][j]->base != nullptr){
                if (pointsMap[i][j]->base == base1)
                    std::cout << "1 ";
                else if (pointsMap[i][j]->base == base2)
                    std::cout << "2 ";
                else
                    std::cout << "3 ";
                continue;
            }
            if (pointsMap[i][j]->unit != nullptr) {

                std::cout << "u ";
            }
            else
                std::cout << "0 ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (pointsMap[i][j]->landscape->getLandscapeType() == "Forest") {
                std::cout << "* ";
            }
            else if (pointsMap[i][j]->landscape->getLandscapeType() == "Mountain")
                std::cout << "^ ";
            else
                std::cout << "~ ";
        }
        std::cout << std::endl;
    }
}

void GameField::printBase(Base *base)
{
    Unit* unit;
    Point* point;
    for (int i = 0; i < base->getCount(); i++){
        unit = base->getCurrUnit();
        point = findUnit(unit);
        std::cout << "\t" << unit->getName() << " (" << point->x << ";" << point->y << ") Health: " << unit->getHealth() << "\n";
    }
}

void GameField::setBase(int maxCount, int health, int xx, int yy)
{
    if ((xx <= this->x - 1) && (yy <= this->y - 1) && (xx >= 0) && (yy >= 0) && (health > 0)) {
        Base* base = nullptr;
        if (base1 == nullptr){
            base1 = new Base(maxCount, health, xx, yy, 1);
            base = base1;
        }
        else if (base2 == nullptr){
            base2 = new Base(maxCount, health, xx, yy, 2);
            base = base2;
        }
        else if (base3 == nullptr){
            base3 = new Base(maxCount, health, xx, yy, 2);
            base = base3;
        }
        pointsMap[yy][xx]->base = base;

        LoggerProxy::baseCreation(base);
    }
}

void GameField::update(Subject* subject)
{
    Point* point = findUnit(static_cast<Unit*>(subject));
    LoggerProxy::unitDeletion(static_cast<Unit*>(subject), point->x, point->y);
    deleteUnit(subject);
}

FieldSnapshot* GameField::getSnapshot()
{
    FieldSnapshot* snap = new FieldSnapshot(this, isCorrectCreated, x, y, unitCount, maxCount, pointsMap, base1, base2);
    return snap;
}

int GameField::getX(){
    return x;
}

int GameField::getY(){
    return y;
}

bool GameField::isBasesCreated(){
    if (base1 && base2)
        return true;
    else {
        return false;
    }
}
