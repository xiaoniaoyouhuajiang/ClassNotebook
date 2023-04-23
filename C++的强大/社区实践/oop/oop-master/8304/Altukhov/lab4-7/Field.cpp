#include "Field.h"
#include "Tile.h"
#include <iostream>
#include "MainUnitFactory.h"
#include "MeleeFactory.h"
#include "RangeFactory.h"
#include "HorsemanFactory.h"

Field::Field() : width(DEFAULT_W), height(DEFAULT_H), amountOfObjects(0) {

	fieldArr = new Tile * [width];
	for (int i = 0; i < width; i++) {
		fieldArr[i] = new Tile[height];
	}
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			fieldArr[i][j] = { i, j };
		}
	}
}

Field::Field(int w, int h) : width(w), height(h), amountOfObjects(0) {

	fieldArr = new Tile * [width];
	for (int i = 0; i < width; i++) {
		fieldArr[i] = new Tile[height];
	}
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			fieldArr[i][j] = { i, j };
		}
	}
}

Field::Field(const Field& field) {//копирование без юнитов, они удаляются


	Tile** anotherFieldArr = new Tile * [field.width];
	for (int i = 0; i < field.width; i++) {
		anotherFieldArr[i] = new Tile[field.height];
	}
	for (int i = 0; i < field.width; i++) {
		for (int j = 0; j < field.height; j++) {
			anotherFieldArr[i][j] = { i, j};
		}
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (this->getTile(i, j).isOccupiedByBase) {
				this->deleteBase(this->getTile(i, j).occupiedByBase);
			}
		}

		delete[] fieldArr[i];
	}
	delete[] fieldArr;

	width = field.width;
	height = field.height;
	amountOfObjects = 0;
	fieldArr = anotherFieldArr;

}

void Field::totalCopy(Field*& fToCopy, Field*& fToPaste) {//this==fToPaste

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (this->getTile(i, j).isOccupiedByBase) {
				this->deleteBase(this->getTile(i, j).occupiedByBase);
			}
		//	if (this->getTile(i, j).isOccupiedByNeutral) {
		//		this->deleteNeutral(this->getTile(i, j).occupiedByNeutral);
		//	}
			//if (this->getTile(i, j).isOccupied) {
			//	this->deleteUnit(this->getTile(i, j).occupiedBy);
			//}
		}

		delete[] fieldArr[i];
	}
	delete[] fieldArr;


	fieldArr = new Tile * [fToCopy->width];
	for (int i = 0; i < fToCopy->width; i++) {
		fieldArr[i] = new Tile[fToCopy->height];
	}
	for (int i = 0; i < fToCopy->width; i++) {
		for (int j = 0; j < fToCopy->height; j++) {
			fieldArr[i][j] = { i, j };
			if ((i == 0) && (j == 0)) {
				this->createAndSetBase(fToPaste, 1); //////////attention!!!!!!
			}
		//	if (fToCopy->getTile(i, j).isOccupiedByBase) {
		//		this->createAndSetBase(fToPaste);
		//	}
			if (fToCopy->getTile(i, j).isOccupied) {
				this->getTile(0, 0).occupiedByBase->createAndSetUnit(fToCopy->getTile(i, j).occupiedBy->getUnitType(), fToCopy->getTile(i, j).occupiedBy->getLevel(), i, j);
				//this->createAndSetUnit(fToCopy->getTile(i, j).occupiedBy->getUnitType(), fToCopy->getTile(i, j).occupiedBy->getLevel(), i, j, fToPaste);
			}
		//	if (fToCopy->getTile(i, j).isOccupiedByNeutral) {
		//		this->createAndSetNeutral(fToCopy->getTile(i, j).occupiedByNeutral->getNeutralType(), i, j, fToPaste);
		//	}
		}
	}

	width = fToCopy->width;
	height = fToCopy->height;
	amountOfObjects = fToCopy->amountOfObjects;
}


Field::~Field() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (this->getTile(i, j).isOccupiedByBase) {
				this->deleteBase(this->getTile(i, j).occupiedByBase);
			}
		}

		delete[] fieldArr[i];
	}
	delete[] fieldArr;
}

int Field::getW() {
	return width;
}

int Field::getH() {
	return height;
}

Tile& Field::getTile(int x, int y) {
	//надо обработать выход за пределы
	return fieldArr[x][y];
}

void Field::visualizeField() {

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			
			if (this->getTile(i, j).isOccupied) {
				if (this->getTile(i, j).occupiedBy->getPlayer() == 1) {
					std::cout << " \x1b[32m" << this->getTile(i, j).occupiedBy->getId() << "\x1b[0m";
				}
				else {
					std::cout << " \x1b[31m" << this->getTile(i, j).occupiedBy->getId() << "\x1b[0m";
				}
				
				//log << (" " + std::to_string(this->getTile(i, j).occupiedBy->getId()));
			}
			else if (this->getTile(i, j).isOccupiedByBase) {
				if (this->getTile(i, j).occupiedByBase->getPlayer() == 1)
					std::cout << "\x1b[32m";
				else
					std::cout << "\x1b[31m";
				std::cout << " " << "*\x1b[0m";
			}
				
				//log << ((std::string)" *");
			else if (this->getTile(i, j).isOccupiedByNeutral) {
				std::string letter;
				if (this->getTile(i, j).occupiedByNeutral->getNeutralObjectType() == NeutralObjectTypes::TOWER)
					letter = "T";
					//std::cout << " " << "T";
					//log << ((std::string)" T");
				if (this->getTile(i, j).occupiedByNeutral->getNeutralObjectType() == NeutralObjectTypes::WEAPONRY)
					//std::cout << " " << "W";
					letter = "W";
					//log << ((std::string)" W");
				if (this->getTile(i, j).occupiedByNeutral->getNeutralObjectType() == NeutralObjectTypes::CANNON)
					//std::cout << " " << "C";
					letter = "C";
					//log << ((std::string)" C");
				if (this->getTile(i, j).occupiedByNeutral->getNeutralObjectType() == NeutralObjectTypes::SHRINE)
					//std::cout << " " << "S";
					letter = "S";
					//log << ((std::string)" S");
				if (this->getTile(i, j).capturedBy) {
					if (this->getTile(i, j).capturedBy == 1)
						std::cout << "\x1b[32m";
					else
						std::cout << "\x1b[31m";
				}

				std::cout << " " << letter << "\x1b[0m";
			}
			else if (this->getTile(i, j).terrain->getTerrainType() == TerrainTypes::FIELD) {
				if (this->getTile(i, j).capturedBy) {
					if (this->getTile(i, j).capturedBy == 1)
						std::cout << "\x1b[32m";
					else
						std::cout << "\x1b[31m";
				}
				std::cout << " " << "0" << "\x1b[0m";
				//log << ((std::string)" 0");
			}
				
			else if (this->getTile(i, j).terrain->getTerrainType() == TerrainTypes::FOREST) {
				if (this->getTile(i, j).capturedBy) {
					if (this->getTile(i, j).capturedBy == 1)
						std::cout << "\x1b[32m";
					else
						std::cout << "\x1b[31m";
				}
				std::cout << " " << "|" << "\x1b[0m";
				//log << ((std::string)" |");
			}
				
			else if (this->getTile(i, j).terrain->getTerrainType() == TerrainTypes::SWAMP) {
				if (this->getTile(i, j).capturedBy) {
					if (this->getTile(i, j).capturedBy == 1)
						std::cout << "\x1b[32m";
					else
						std::cout << "\x1b[31m";
				}
				std::cout << " " << "_" << "\x1b[0m";
				//log << ((std::string)" _");
			
			}	

		}
		std::cout << "\n";
		//log << ((std::string)"\n");
	}
	std::cout << "\n\n";
	//log << ((std::string)"\n\n");
}

/*Unit* Field::createAndSetUnit(UnitTypes type, int lvl, int x, int y, Field*& f) {

	if (MAX_OBJECTS_AMOUNT == amountOfObjects) {
		std::cout << "Поле переполнено!\n";
		return nullptr;
	}
	if (this->getTile(x, y).isOccupied) {
		std::cout << "Клетка занята!\n";
		return nullptr;
	}
	if ((x >= width) || (y >= height)) {
		std::cout << "Выход за пределы поля!\n";
	}

	MainUnitFactory* factory;
	Unit* unit;
	if (type == UnitTypes::MELEE) {
		factory = new MeleeFactory;
	}
	else if (type == UnitTypes::RANGE) {
		factory = new RangeFactory;
	}
	else {//if (type == UnitTypes::HORSEMAN) {
		factory = new HorsemanFactory;
	}
	if (lvl == 1) {
		unit = factory->createLvl1Unit();
	}
	else {
		unit = factory->createLvl2Unit();
	}


	amountOfObjects++;
	unit->setParentField(f);

	unit->doMove(x, y);
	return unit;
}*/

/*void Field::deleteUnit(Unit*& unit) {
	amountOfObjects--;
	delete unit;
}*/
void Field::deleteBase(Base*& base) {
	amountOfObjects--;
	delete base;
}

void Field::addLog(ProxyLog* log)
{
	this->log = log;
}


Base* Field::createAndSetBase(Field*& f, int baseNum) {

	Base* base = new Base(baseNum);
	amountOfObjects++;

	base->setParentField(f);
	base->setBase(baseNum==1?0:f->getW()-1, baseNum == 1 ? 0 : f->getH()-1);

	return base;
}

void Field::fillMemento(Memento*& snapshot) {
	snapshot->fieldW = width;
	snapshot->fieldH = height;
	snapshot->tiles.clear();

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int terType = this->getTile(i, j).terrain->getTerrainType() == TerrainTypes::FIELD?  1: this->getTile(i, j).terrain->getTerrainType() == TerrainTypes::FOREST ? 2 : this->getTile(i, j).terrain->getTerrainType() == TerrainTypes::SWAMP ? 3 : 0;
			int neutralType = 0;
			if (this->getTile(i, j).isOccupiedByNeutral) {
				if (this->getTile(i, j).occupiedByNeutral->getNeutralObjectType() == NeutralObjectTypes::TOWER)
					neutralType = 1;
				if (this->getTile(i, j).occupiedByNeutral->getNeutralObjectType() == NeutralObjectTypes::WEAPONRY)
					neutralType = 2;
				if (this->getTile(i, j).occupiedByNeutral->getNeutralObjectType() == NeutralObjectTypes::CANNON)
					neutralType = 3;
				if (this->getTile(i, j).occupiedByNeutral->getNeutralObjectType() == NeutralObjectTypes::SHRINE)
					neutralType = 4;
			
			}
			
			snapshot->tiles.push_back({ i, j, terType, neutralType, this->getTile(i,j).capturedBy});
		}
		
	}
}

void Field::newField(Memento*& snapshot) {

	Base* base1 = this->getTile(0, 0).occupiedByBase;
	Base* base2 = this->getTile(width - 1, height - 1).occupiedByBase;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			//if (this->getTile(i, j).isOccupiedByBase) {
			//	this->deleteBase(this->getTile(i, j).occupiedByBase);
			//}
		}

		delete[] fieldArr[i];
	}
	delete[] fieldArr;
	amountOfObjects = 0;
	width = snapshot->fieldW;
	height = snapshot->fieldH;
	fieldArr = new Tile * [snapshot->fieldW];
	for (int i = 0; i < snapshot->fieldW; i++) {
		fieldArr[i] = new Tile[snapshot->fieldH];
	}
	for (int i = 0; i < snapshot->tiles.size(); i++) {
		Terrain* ter;
		if (snapshot->tiles[i].type == 1) {
			ter = new FieldTerrain;
		}
		else if (snapshot->tiles[i].type == 2) {
			ter = new ForestTerrain;
		}
		else if (snapshot->tiles[i].type == 3) {
			ter = new SwampTerrain;
		}
		NeutralObject* neutral = nullptr;
		if (snapshot->tiles[i].typeNeutral == 1) {
			neutral = new TowerNeutral;
		}
		else if (snapshot->tiles[i].typeNeutral == 2) {
			neutral = new WeaponryNeutral;
		}
		else if (snapshot->tiles[i].typeNeutral == 3) {
			neutral = new CannonNeutral;
		}
		else if (snapshot->tiles[i].typeNeutral == 4) {
			neutral = new ShrineNeutral;
		}
		fieldArr[snapshot->tiles[i].x][snapshot->tiles[i].y] = { snapshot->tiles[i].x , snapshot->tiles[i].y , ter, neutral?true:false, neutral, snapshot->tiles[i].capturedBy};
	}

	fieldArr[0][0].isOccupiedByBase = true;
	fieldArr[0][0].occupiedByBase = base1;

	fieldArr[width-1][height-1].isOccupiedByBase = true;
	fieldArr[width - 1][height - 1].occupiedByBase = base2;






}