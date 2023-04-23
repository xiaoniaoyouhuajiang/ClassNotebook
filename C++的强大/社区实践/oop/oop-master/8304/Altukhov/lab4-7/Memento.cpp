#include "Memento.h"

void Memento::getInfoFromBase(Base* base, bool myTurn)
{
	Memento* mem = const_cast<Memento*>(this);
	base->fillMemento(mem, myTurn);
}

void Memento::getInfoFromField(Field* field)
{
	Memento* mem = const_cast<Memento*>(this);
	field->fillMemento(mem);
}

void Memento::saveToFile(std::string& fileName) {
	std::ofstream file(fileName);
	file << whatPlayerTurn << " " << fieldW << " " << fieldH << " " << (fieldW*fieldH) << std::endl;
	for (int i = 0; i < tiles.size(); i++) {
		file << tiles[i].x << " " << tiles[i].y << " " << tiles[i].type << " " << tiles[i].typeNeutral << " " << tiles[i].capturedBy << std::endl;
	}

	file << hp1 << " " << money1 << " " << turn1 << " " << units1.size() << std::endl;
	for (int i = 0; i < units1.size(); i++) {
		file << units1[i].x << " " << units1[i].y << " " << units1[i].type << " " << units1[i].level << " " << units1[i].hp << " " << units1[i].canMove << " " << units1[i].canAttack << std::endl;
	}

	file << hp2 << " " << money2 << " " << turn2 << " " << units2.size() << std::endl;
	for (int i = 0; i < units2.size(); i++) {
		file << units2[i].x << " " << units2[i].y << " " << units2[i].type << " " << units2[i].level << " " << units2[i].hp << " " << units2[i].canMove << " " << units2[i].canAttack << std::endl;
	}

	file.close();
}

bool Memento::loadFromFile(Field* field, Base* myBase, Base* otherBase, std::string& fileName) {
	std::ifstream file(fileName);
	if (!file) {
		return false;
	}
	int check = 0;
	file >> whatPlayerTurn >> fieldW >> fieldH >> check;
	if (check != fieldW * fieldH) {
		//ошибка
		return false;
	}
	tiles.clear();
	for (int i = 0; i < check; i++) {
		int x, y, type, typeN, capt = 0;
		file >> x >> y >> type >> typeN >> capt;
		if (x >= fieldW || y >= fieldH || type < 1 || type >3 || typeN < 0 || typeN > 4 || capt < 0 || capt > 2) {
			//ошибка
			return false;
		}
		tiles.push_back({ x, y, type, typeN, capt });
	}

	file >> hp1 >> money1 >> turn1 >> check;
	units1.clear();
	for (int i = 0; i < check; i++) {
		int x, y, type, level, hp, canMove, canAttack;
		file >> x >> y >> type >> level >> hp >> canMove >> canAttack;
		if (x >= fieldW || y >= fieldH || type < 1 || type >3 || level < 1 || level > 2 ) {
			//ошибка
			return false;
		}
		units1.push_back({ x, y, type, level, hp, canMove, canAttack });
	}

	file >> hp2 >> money2 >> turn2 >> check;
	units2.clear();
	for (int i = 0; i < check; i++) {
		int x, y, type, level, hp, canMove, canAttack;
		file >> x >> y >> type >> level >> hp >> canMove >> canAttack;
		if (x >= fieldW || y >= fieldH || type < 1 || type >3 || level < 1 || level > 2) {
			//ошибка
			return false;
		}
		units2.push_back({ x, y, type, level, hp, canMove, canAttack });
	}
	myBase->deleteUnits();
	otherBase->deleteUnits();
	loadInfoToField(field);
	loadInfoToBase(myBase, myBase->getPlayer());
	loadInfoToBase(otherBase, otherBase->getPlayer());

	return true;
}


void Memento::loadInfoToField(Field* field) {
	Memento* mem = const_cast<Memento*>(this);
	field->newField(mem);
}

void Memento::loadInfoToBase(Base* base, int num) {
	Memento* mem = const_cast<Memento*>(this);
	base->newBase(mem, num);
}

