#include "GameField.h"
#include <iostream>
#include <iomanip>

using namespace std;

GameField::GameField()				//конструктор "по умолчанию"
{
	width = height = 10;
	step = 1;
	maxUnits = 6;
}

GameField::GameField(int height, int width) : GameField() //делегирующие конструкторы
{
	if (height > 3 && width > 3) {
		this->height = height;
		this->width = width;

		if (width >= height && (int)((width / 2) * (0.2)) > step&& height >= (width / 2)) {
			step = (int)((width / 2) * (0.2));
		}

		maxUnits *= step;
	}
	createField();
}

GameField::GameField(const GameField& other) { //GameField a(b);
	this->height = other.height;
	this->width = other.width;
	this->step = other.step;

	this->field = new Cell *[other.height];
	for (int i = 0; i < other.height; i++) {
		this->field[i] = new Cell [other.width];
		for (int j = 0; j < other.width; j++) {
			this->field[i][j] = other.field[i][j];
		}
	}
}

GameField& GameField::operator = (const GameField& other) {//a = b;
	if (&other == this) { //проверка на самоприсваивание
		return *this;
	}
	else {
		this->width = other.width;
		this->step = other.step;
		if (this->field != nullptr) { //если не пустой
			for (int i = 0; i < this->height; i++) {
				delete[] this->field[i];
			}
			delete[] this->field;
			//очищаем динамическую память, так как будет присвоено новое значение
		} 

		this->height = other.height;
		this->field = new Cell * [other.height];
		for (int i = 0; i < other.height; i++) {
			this->field[i] = new Cell[other.width];
			for (int j = 0; j < other.width; j++) {
				this->field[i][j] = other.field[i][j];
			}
		}
		return *this; //возвращаем адрес константного указателя на текущий объект
	}
}

GameField::GameField(GameField&& other) :field(nullptr), height(NULL), width(NULL), step(NULL) { 

	swap(*this, other);

}

GameField& GameField::operator = (GameField&& other) {
	if (&other == this) { //проверка на самоприсваивание
		return *this;
	}
	else {
		if (this->field != nullptr) { //если не пустой
			for (int i = 0; i < this->height; i++) {
				delete[] this->field[i];
			}
			delete[] this->field;
			//очищаем динамическую память, так как будет присвоено новое значение

			this->field = nullptr; 
			this->height = NULL;
			this->width = NULL;
			this->step = NULL;
			
		}

		swap(*this, other);
		return *this;
	}
	
}

void GameField::createField() { 
	field = new Cell*[height];
	for (int i = 0; i < height; i++) {
		field[i] = new Cell[width];
		for (int j = 0; j < width; j++) {
			field[i][j] = Cell();
		}
	}
	
	addBases();
	coveredLands();
}

void GameField::addBases() {
	field[0][width / 2].setBase(new BasePeople(step));
	field[0][width / 2].getBase()->setXY(0, width / 2);

	field[height - 1][0].setBase(new BaseMonster(step));
	field[height - 1][0].getBase()->setXY(height - 1, 0);

	field[height - 1][width-1].setBase(new BaseHero(step));
	field[height - 1][width - 1].getBase()->setXY(height - 1, width - 1);
}

void GameField::coveredLands() { //покрытие ландшафтом
	srand(time(NULL));
	int x, y, view;
	int area = width * height;
	int countGrass = (area * 3) / 4;								//75%
	int countLake = (area - countGrass) / 2;						//13%
	int countCircle = ((area - (countGrass + countLake)) * 2) / 3;  //8-10%
	int countPit = area - (countGrass + countLake + countCircle);

	countGrass -= 3; area -=3;
	field[0][width / 2].setLand(new Grass(1));
	field[height - 1][0].setLand(new Grass(2));
	field[height - 1][width - 1].setLand(new Grass(1));

	while (area != 0) { //все остальные клетки заполняются рандомно
		x = rand() % height;
		y = rand() % width;
		if (field[x][y].getLand() == nullptr) {
			if (countGrass != 0) {
				view = rand() % 3;
				field[x][y].setLand(new Grass(view));
				countGrass--;
			}
			else if (countLake != 0) {
				field[x][y].setLand(new Lake);
				countLake--;
			}
			else if (countCircle != 0) {
				field[x][y].setLand(new ritualCircle);
				countCircle--;
			}
			else if (countPit != 0) {
				field[x][y].setLand(new Pit);
				countPit--;
			}
			area--;
		}
	}
	addPeople();
}

void GameField::addPeople() {
	int view, x, y;
	srand(time(NULL));
	while (field[0][width / 2].getBase()->getCounterUnits() != field[0][width / 2].getBase()->getmaxUnitsSt()) {
		view = rand() % 2 + 5;	//5 или 6
		x = rand() % height;
		y = rand() % width;
		
		if (!addUnit(field[0][width / 2].getBase()->createUnit(view), x, y))
			field[0][width / 2].getBase()->setCounterUnits(field[0][width / 2].getBase()->getCounterUnits() + 1);	//counter++
	}
} 

void GameField::addNeutralObject() {
	srand(time(NULL));
	int x, y, viewBox;
	int count1, count2, count3, count4, count;
	count3 = count1 = maxUnits / 2;
	count4 = count2 = (maxUnits / 3) * 2;
	count = count1 * 2 + count2 * 2;

	while (count != 0) {
		x = rand() % height;
		y = rand() % width;
		if (field[x][y].getNeutralObject() == nullptr && field[x][y].getUnit() == nullptr && field[x][y].getBase() == nullptr && field[x][y].getLand()->getType() != 4) {	 //если на позиции свободно
			if (count1 != 0) {
				field[x][y].setNeutralObject(new HolyCross());
				field[x][y].getNeutralObject()->setXY(x, y);
				count1--;
			}
			else if (count2 != 0) {
				field[x][y].setNeutralObject(new Tablet());
				field[x][y].getNeutralObject()->setXY(x, y);
				count2--;
			}
			else if (count3 != 0) {
				field[x][y].setNeutralObject(new Snake());
				field[x][y].getNeutralObject()->setXY(x, y);
				count3--;
			}
			else if (count4 != 0) {
				viewBox = rand() % 2 + 1;
				field[x][y].setNeutralObject(new SurpriseBox(viewBox));
				field[x][y].getNeutralObject()->setXY(x, y);
				count4--;
			}
			count--;
		}
	}
}

int GameField::addUnit(Unit* unit, int x, int y) {
	unit->setXY(x, y);
	if (field[x][y].getUnit() != nullptr || field[x][y].getBase() != nullptr || field[x][y].getNeutralObject() != nullptr) {
		return 1;	//занято
	}
	else if (field[x][y].getLand()->noPassage(unit->getView()) == 1) {
		return 2;	//нельзя ставить на этот ландшафт
	}
	else {
		field[x][y].setUnit(unit);
		return 0;	//good
	}
}

void GameField::swapUnits(Cell& a, Cell& b) {
	Unit* temp = a.getUnit();
	a.setUnit(b.getUnit());
	b.setUnit(temp);
	temp = nullptr;
}

int GameField::checkSteps(int steps, int x, int y) {

	switch ((field[x][y].getUnit())->getView()) {
	case 1:
		if (steps > 3) {
			return 1;
		}
		break;
	case 2:
		if (steps > 2) {
			return 1;
		}
		break;
	case 3:
		if (steps > 1) {
			return 1;
		}
		break;
	case 4:
		if (steps > 2) {
			return 1;
		}
		break;
	}
	return 0;
}

int GameField::movingUnit(int x, int y, int x2, int y2, int steps) { //'r' - право 'l' - лево 'd' - вниз 'u' - вверх
	if (field[x][y].getUnit() == nullptr) return 3; //некого перемещать
	if (checkSteps(steps, x, y)) return 4;

	if (field[x2][y2].getUnit() == nullptr && field[x2][y2].getBase() == nullptr && y2 < width && y2 > -1 && x2 < height && x2 > -1) { //пока можно перемещаться только на свободные позиции
		if (field[x2][y2].getLand()->noPassage(field[x][y].getUnit()->getView()) == 1) {
			return 2; //нельзя перемещать на данный ландшафт
		}

		swapUnits(field[x][y], field[x2][y2]);					 //можно перемещаться на поле противника
		field[x2][y2].getUnit()->setXY(field[x2][y2].getUnit()->getX() + (x2 - x), field[x2][y2].getUnit()->getY() + (y2 - y));
			
		if (field[x2][y2].getNeutralObject() != nullptr) { //если наступили на нейтральный объект
			*(field[x2][y2].getNeutralObject())+=*(field[x2][y2].getUnit());
			deleteNeutralObject(x2, y2);
			if (field[x2][y2].getUnit()->getHealth() <= 0) { //наступил и умер
				deleteUnit(x2, y2); //умер
			}
			
		}
	}
	else if (field[x2][y2].getUnit() != nullptr && field[x2][y2].getBase() == nullptr && y2 < width && y2 > -1 && x2 < height && x2 > -1) { //хотим напасть
		if (field[x2][y2].getLand()->noPassage(field[x][y].getUnit()->getView()) == 1) { //и можно переместиться на ландшафт
			return 2; //нельзя перемещать на данный ландшафт
		}
		//тогда нападаем
		*(field[x][y].getUnit()) -= *(field[x2][y2].getUnit()); //field[x][y] attack by field[x2][y2]
		if (field[x2][y2].getUnit()->getHealth() <= 0) {
			deleteUnit(x2, y2); //умер
			swapUnits(field[x][y], field[x2][y2]);					 //можно перемещаться на его место
			field[x2][y2].getUnit()->setXY(field[x2][y2].getUnit()->getX() + (x2 - x), field[x2][y2].getUnit()->getY() + (y2 - y));
			
		}
		else { //не умер
			//тогда после атаки меняемся местами с юнитом
			
			swapUnits(field[x][y], field[x2][y2]);
			field[x2][y2].getUnit()->setXY(field[x2][y2].getUnit()->getX() + (x2 - x), field[x2][y2].getUnit()->getY() + (y2 - y));
			field[x][y].getUnit()->setXY(field[x][y].getUnit()->getX() - (x2 - x), field[x][y].getUnit()->getY() - (y2 - y));
		}
	}
	else if (field[x2][y2].getBase() != nullptr && field[x2][y2].getUnit() == nullptr && y2 < width && y2 > -1 && x2 < height && x2 > -1) { //если нападаем на базу
		if (field[x2][y2].getLand()->noPassage(field[x][y].getUnit()->getView()) == 1) { //и можно переместиться на ландшафт
			return 2; //нельзя перемещать на данный ландшафт
		}
		
		*(field[x2][y2].getBase()) -= *(field[x][y].getUnit());//тогда нападаем
		if (field[x2][y2].getBase()->getHealthBase() <= 0) { //у базы больше нет здоровья..
			deleteBase(x2, y2); //уничтожаем ее 
			swapUnits(field[x][y], field[x2][y2]);					 //можно перемещаться на его место
			field[x2][y2].getUnit()->setXY(field[x2][y2].getUnit()->getX() + (x2 - x), field[x2][y2].getUnit()->getY() + (y2 - y));
		}
		else { //иначе ничего не делаем, меняться с базой местами нельзя)
			return 0; 
		}
	}
	else {
		return 1;
	}

	return 0;
}

int GameField::deleteUnit(int x, int y) {
	if (field[x][y].getUnit() != nullptr) {

		//фиксируем смерть в базе
		if (field[x][y].getUnit()->getView() == 1 || field[x][y].getUnit()->getView() == 2) //monster
			field[height - 1][0].getBase()->setCounterUnits(field[height - 1][0].getBase()->getCounterUnits() - 1);
		if (field[x][y].getUnit()->getView() == 3 || field[x][y].getUnit()->getView() == 4) //hero
			field[height - 1][width - 1].getBase()->setCounterUnits(field[height - 1][width - 1].getBase()->getCounterUnits() - 1);
		if (field[x][y].getUnit()->getView() == 5 || field[x][y].getUnit()->getView() == 6) //people
			field[0][width / 2].getBase()->setCounterUnits(field[0][width / 2].getBase()->getCounterUnits() - 1);

		delete field[x][y].getUnit();
		field[x][y].setUnit(nullptr);
		return 0;
	}
	else {
		return 1;
	}
}

int GameField::deleteNeutralObject(int x, int y) {
	if (field[x][y].getNeutralObject() != nullptr) {
		delete field[x][y].getNeutralObject();
		field[x][y].setNeutralObject(nullptr);
		return 0;
	}
	else {
		return 1;
	}

}

int GameField::deleteBase(int x, int y) {
	if (field[x][y].getBase() != nullptr) {
		delete field[x][y].getBase();
		field[x][y].setBase(nullptr);
	}
	else {
		return 1;
	}
}

Unit* GameField::getUnit(int x, int y) {
	return field[x][y].getUnit();
}

Landscape* GameField::getLandscape(int x, int y) {
	return field[x][y].getLand();
}

NeutralObject* GameField::getNeutralObject(int x, int y) {
	return field[x][y].getNeutralObject();
}

Base* GameField::getBase(char type) {
	switch (type) {
	case 'm':
		return field[height - 1][0].getBase();
		break;
	case 'h':
		return field[height - 1][width - 1].getBase();
		break;
	case 'p':
		return field[0][width / 2].getBase();
		break;
	}
}

Base* GameField::getBase(int x, int y) {
	return field[x][y].getBase();
}

int GameField::getHeight() {
	return height;
}

int GameField::getWidth() {
	return width;
}

int GameField::getStep() {
	return step;
}

int GameField::getMaxUnits() {
	return maxUnits;
}

GameField::~GameField() {
	for (int i = 0; i < height; i++) {
		delete[] field[i];
	}
	delete[] field;
}
