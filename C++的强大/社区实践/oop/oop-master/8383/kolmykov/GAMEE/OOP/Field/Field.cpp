#include "Field.h"


Field::Field(int height, int width) {
	this->height = height;
	this->width = width;
	unitCount = 0;
    objFactory = std::shared_ptr<NeutralObjectFactory>(new NeutralObjectFactory);
	fieldArr = std::shared_ptr<std::shared_ptr<std::shared_ptr<FieldCell>[]>[]>(new std::shared_ptr<std::shared_ptr<FieldCell>[]>[height]);
	for (int i = 0; i < height; i++) {
		fieldArr[i] = std::shared_ptr<std::shared_ptr<FieldCell>[]>(new std::shared_ptr<FieldCell>[width]);
		for (int j = 0; j < width; j++) {
			fieldArr[i][j] = std::shared_ptr<FieldCell>(new FieldCell());
		}
	}
	unitArr = std::shared_ptr<std::shared_ptr<Unit>[]>(new std::shared_ptr<Unit> [width * height]);
}

Field::Field(const Field & other)
{
	this->height = other.height;
	this->width = other.width;
	this->unitCount = other.unitCount;
	unitArr = std::shared_ptr<std::shared_ptr<Unit>[]>(new std::shared_ptr<Unit>[width * height]);
	for (int i = 0; i < width * height; i++) {
		unitArr[i] = other.unitArr[i];
	}
	fieldArr = std::shared_ptr<std::shared_ptr<std::shared_ptr<FieldCell>[]>[]>(new std::shared_ptr<std::shared_ptr<FieldCell>[]>[height]);
	for (int i = 0; i < height; i++) {
		fieldArr[i] = std::shared_ptr<std::shared_ptr<FieldCell>[]>(new std::shared_ptr<FieldCell>[width]);
		for (int j = 0; j < width; j++) {
			fieldArr[i][j] = other.fieldArr[i][j];
		}
	}
}

Field::Field(Field && other)
{
	this->height = other.height;
	this->width = other.width;
	this->unitCount = other.unitCount;
	unitArr = std::shared_ptr<std::shared_ptr<Unit>[]>(new std::shared_ptr<Unit>[width * height]);
	for (int i = 0; i < width * height; i++) {
		unitArr[i] = other.unitArr[i];
	}
	fieldArr = std::shared_ptr<std::shared_ptr<std::shared_ptr<FieldCell>[]>[]>(new std::shared_ptr<std::shared_ptr<FieldCell>[]>[height]);
	for (int i = 0; i < height; i++) {
		fieldArr[i] = std::shared_ptr<std::shared_ptr<FieldCell>[]>(new std::shared_ptr<FieldCell>[width]);
		for (int j = 0; j < width; j++) {
			fieldArr[i][j] = other.fieldArr[i][j];
		}
	}

	other.fieldArr = nullptr;
	other.unitArr = nullptr;
}

Field& Field::operator=(const Field & other)
{
	this->height = other.height;
	this->width = other.width;
	this->unitCount = other.unitCount;
	unitArr = std::shared_ptr<std::shared_ptr<Unit>[]>(new std::shared_ptr<Unit>[width * height]);
	for (int i = 0; i < width * height; i++) {
		unitArr[i] = other.unitArr[i];
	}
	fieldArr = std::shared_ptr<std::shared_ptr<std::shared_ptr<FieldCell>[]>[]>(new std::shared_ptr<std::shared_ptr<FieldCell>[]>[height]);
	for (int i = 0; i < height; i++) {
		fieldArr[i] = std::shared_ptr<std::shared_ptr<FieldCell>[]>(new std::shared_ptr<FieldCell>[width]);
		for (int j = 0; j < width; j++) {
			fieldArr[i][j] = other.fieldArr[i][j];
		}
	}

	return *this;
}

Field & Field::operator=(Field && other)
{
	if (&other == this) {
		return *this;
	}

	this->height = other.height;
	this->width = other.width;
	this->unitCount = other.unitCount;
	unitArr = std::shared_ptr<std::shared_ptr<Unit>[]>(new std::shared_ptr<Unit>[width * height]);
	for (int i = 0; i < width * height; i++) {
		unitArr[i] = other.unitArr[i];
	}
	fieldArr = std::shared_ptr<std::shared_ptr<std::shared_ptr<FieldCell>[]>[]>(new std::shared_ptr<std::shared_ptr<FieldCell>[]>[height]);
	for (int i = 0; i < height; i++) {
		fieldArr[i] = std::shared_ptr<std::shared_ptr<FieldCell>[]>(new std::shared_ptr<FieldCell>[width]);
		for (int j = 0; j < width; j++) {
			fieldArr[i][j] = other.fieldArr[i][j];
		}
	}

	return *this;
}


Field::~Field() {

}

std::shared_ptr<Tower> Field::createTower(int x, int y, std::shared_ptr<UnitFactory> factory) {
	std::shared_ptr<Tower> tower(new Tower(x, y, factory));
	tower->setMediator(mediator);
	fieldArr[y][x]->setTower(tower);
	return tower;
}



void Field::printField() {
    emit updateSignal();
	for (int i = 0; i < width; i++) {
		std::cout << "_";
	}
	std::cout << std::endl;
	for (int i = 0; i < height; i++) {
		std::cout << "|";
		for (int j = 0; j < width; j++) {
			if (fieldArr[i][j]->hasTower()) {
				std::cout << "*";
			}
			else if (fieldArr[i][j]->getUnit() == nullptr) {
				std::cout << fieldArr[i][j]->getLand()->getChar();
			}
			else {
				std::cout << fieldArr[i][j]->getUnit()->getChar();
			}
		}
		std::cout << "|\n";
	}
	for (int i = 0; i < width; i++) {
		std::cout << "_";
	}
	std::cout << std::endl;
}

void Field::reload()
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			fieldArr[i][j]->setUnit(nullptr);
		}
	}

	for (int i = 0; i < unitCount; i++) {
		unitArr[i]->performMove();
		fieldArr[unitArr[i]->getY()][unitArr[i]->getX()]->setUnit(unitArr[i]);
	}
}

std::shared_ptr<FieldIterator> Field::createIterator()
{
	return std::shared_ptr<FieldIterator>(new FieldIterator(std::shared_ptr<Field>(this)));
}

void Field::addUnit(std::shared_ptr<Unit> unit)
{
	if (unit == nullptr) {
		return;
	}
	fieldArr[unit->getY()][unit->getX()]->setUnit(unit);
	for (int i = 0; i < height*width; i++) {
		if (unitArr[i] == nullptr) {
			unitArr[i] = unit;
			unitCount++;
			break;
		}
	}
}

std::shared_ptr<FieldCell> Field::getCell(int x, int y)
{
	return fieldArr[y][x];
}

int Field::getHeight()
{
	return height;
}

int Field::getWidth()
{
	return width;
}

void Field::setMediator(std::shared_ptr<Mediator> mediator)
{
	this->mediator = mediator;
}

std::shared_ptr<Mediator> Field::getMediator()
{
	return mediator;
}

std::shared_ptr<FieldIterator> Field::begin()
{
	return std::shared_ptr<FieldIterator>(new FieldIterator(shared_from_this()));
}

std::shared_ptr<FieldIterator> Field::end()
{
	 std::shared_ptr<FieldIterator> iterator (new FieldIterator(shared_from_this()));
	 while (!iterator->isDone()) {
		 iterator->next();
	 }
	 iterator->next();
	 return iterator;
}


FieldIterator::FieldIterator(std::shared_ptr<Field> field) {
	this->field = field;
}

FieldIterator::~FieldIterator()
{
}

void FieldIterator::first() {
	yCoord = 0;
	xCoord = 0;
}

void FieldIterator::end() {
	xCoord = field->width - 1;
	yCoord = field->height - 1;
}

void FieldIterator::prev() {
	xCoord--;
	yCoord--;
}

void FieldIterator::next() {
	if (xCoord < field->width - 1) {
		xCoord++;
	}
	else {
		yCoord++;
		xCoord = 0;
	}
}

bool FieldIterator::isDone()
{
	return xCoord == field->width - 1 && yCoord == field->height - 1;
}

bool FieldIterator::isBegin()
{
	return xCoord == 0 && yCoord == 1;
}

std::shared_ptr<FieldCell> FieldIterator::current()
{
	return field->fieldArr[yCoord][xCoord];
}


bool Field::isGameEnd(Kind kind) {
    int y;
    switch (kind) {
    case Kind::ZOMBY:
        y = height - 1;
        break;
    case Kind::HUMAN:
        y = 0;
    }
    bool towerExist = false;
    for (int x = 0; x < width; x++) {
        if (getCell(x, y)->getTower() != nullptr) {
            towerExist = true;
            break;
        }
    }
    if (!towerExist) {
        emit gameEndSignal();
    }
    return towerExist;
}


void Field::createObj() {
    int flag = rand()%10;
    if (flag >= 7) {
        int rX = rand()%width;
        int rY = 1 + rand()%(height - 2);
        if(fieldArr[rY][rX]->getUnit() == nullptr) {
            fieldArr[rY][rX]->setObj(objFactory->create());
            printField();
        }
    }
}

