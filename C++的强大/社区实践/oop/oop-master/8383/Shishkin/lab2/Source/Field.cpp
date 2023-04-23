#include "Field.h"
#include <iostream>
#include <time.h>

using namespace std;

Field::Field() {
	size = 3;
	current1stPlayerUnits = 0;
	current2ndPlayerUnits = 0;
}

Field::Field(int a, int numOfUnitsOnEachSide) {
	size = a;
	current1stPlayerUnits = numOfUnitsOnEachSide;
	current2ndPlayerUnits = numOfUnitsOnEachSide;
}

Field::~Field() {
	//for (int i = 0; i < size; i++) {
	//	if (cell[i]) delete[] cell[i];
	//}
	delete cell;
}

Field::Field(const Field& f) {      //конструктор копирования
	this->current1stPlayerUnits = f.current1stPlayerUnits;
	this->current2ndPlayerUnits = f.current2ndPlayerUnits;
	this->size = f.size;
	this->mas();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cell[i][j] = f.cell[i][j];
		}
	}
}
 
Field::Field(Field&& f) {                    //конструктор перемещения
	this->current1stPlayerUnits = f.current1stPlayerUnits;
	this->current2ndPlayerUnits = f.current2ndPlayerUnits;
	this->size = f.size;
	this->mas();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cell[i][j] = f.cell[i][j];
		}
	}
	this->~Field();
}

void Field::mas() {
	cell = new Cell * [size];
	for (int i = 0; i < size; i++) {
		cell[i] = new Cell[size];
	}
}

void Field::print() {
	for (int i = 0; i < (size + 1) * 4 - 2; i++) cout << "_";
	cout << endl;

	for (int i = 0; i < size; i++) {
		cout << "|";
		for (int j = 0; j < size; j++) {
			if (cell[i][j].getUnit().GetValue() != "---")        //ЕСЛИ В КЛЕТКЕ ЕСТЬ ЮНИТ, ТО ПЕЧАТАЕМ ЕГО
				cout << " " << cell[i][j].getUnit().GetValue();

			else if (cell[i][j].getNeutral() != nullptr) {

				if (cell[i][j].getNeutral()->getNeutObjType() == "HealthR") {        //ЕСЛИ В КЛЕТКЕ ЕСТЬ НЕЙТРАЛЬНЫЙ ОБЪЕКТ ТИПА 'ПОПОЛНЕНИЕ ЗДОРОВЬЯ', ТО ПЕЧАТАЕМ ЕГО
					cout << " " << "+HP";
				}

				else if (cell[i][j].getNeutral()->getNeutObjType() == "ArmorR") {        //ЕСЛИ В КЛЕТКЕ ЕСТЬ НЕЙТРАЛЬНЫЙ ОБЪЕКТ ТИПА 'ПОПОЛНЕНИЕ БРОНИ', ТО ПЕЧАТАЕМ ЕГО
					cout << " " << "+AR";
				}

				else if (cell[i][j].getNeutral()->getNeutObjType() == "Killer") {        //ЕСЛИ В КЛЕТКЕ ЕСТЬ НЕЙТРАЛЬНЫЙ ОБЪЕКТ ТИПА 'УБИВАЛКА', ТО ПЕЧАТАЕМ ЕГО
					cout << " " << "/I\\";
				}

				else if (cell[i][j].getNeutral()->getNeutObjType() == "Freezer") {        //ЕСЛИ В КЛЕТКЕ ЕСТЬ НЕЙТРАЛЬНЫЙ ОБЪЕКТ ТИПА 'ЗАМОРОЗКА', ТО ПЕЧАТАЕМ ЕГО
					cout << " " << "***";
				}
			}
			


			else if (cell[i][j].getLandscape()->getLandscapeType() == "forest") {      //ЕСЛИ В КЛЕТКЕ ЕСТЬ ЛАНДШАФТ ТИПА 'ЛЕС', ТО ПЕЧАТАЕМ ЕГО
				cout << " " << "~~~";
			}

			else if (cell[i][j].getLandscape()->getLandscapeType() == "burningE") {      //ЕСЛИ В КЛЕТКЕ ЕСТЬ ЛАНДШАФТ ТИПА 'РАСКАЛЕННЫЕ ЗЕМЛИ', ТО ПЕЧАТАЕМ ЕГО
				cout << " " << "$$$";
			}

			else if (cell[i][j].getLandscape()->getLandscapeType() == "UnknownL") {      //ЕСЛИ В КЛЕТКЕ ЕСТЬ ЛАНДШАФТ ТИПА 'НЕИЗВЕСТНЫЕ ЗЕМЛИ', ТО ПЕЧАТАЕМ ЕГО
				cout << " " << "???";
			}

			else {                            //ЕСЛИ БАЗА
				cout << " " << cell[i][j].getUnit().GetValue();
			}
		}
		cout << "|" << endl;
	}

	for (int i = 0; i < (size + 1) * 4 - 2; i++) cout << "_";
	cout << endl << endl << endl << endl;
	cout << "Подсказки:\n";
	cout << "OD - Orcs Devourers - орки пожиратели; OR - Orcs Robbers - орки разбойники\n";
	cout << "MS - Mens Spearman - люди копьеносцы; MW - Mens Wizard - люди маги\n";
	cout << "EA - Elfs Archer - эльф лучник; EI - Elfs Invisible - эльф невидимка\n";
	cout << "Ландшафт: ~~~ - лес; $$$ - раскаленные земли; ??? - неизвестные земли\n";
	cout << "Нейтральные объекты: +HP - пополнение здоровья; +AR - пополнение брони; /I\\ - убивалка; *** - заморозка\n";
	cout << "Введите \"exit\" для выхода, \"add\" - для добавления персонажа, \"del\" - для удаления персонажа,\n \"base\" - для базы\n";
	cout << endl;
}

void Field::init(int numOfOrcs, int numOfElfs, int numOfMens) {
	mas();
	srand(time(0));

	ArcherFactory arF;
	SpearmanFactory spF;
	InvisibleFactory inviF;
	WizardFactory wizF;
	DevourerFactory devF;
	RobberFactory robF;

	int num = 0;   //для рандомного выбора юнитов

	//----------------------------------------------
	//         СОЗДАНИЕ ЮНИТОВ
	//----------------------------------------------

	for (int i = 0; i < numOfElfs; i++) {
		num = 4 + rand() % 2;

		if (i % 2 == 0) {
			if (num == 4) {
				string str = ar.GetValue();
				char sym = ar.GetCounter() + '0';
				str += sym;
				ar.SetCounter(ar.GetCounter() + 1);
				Warrior w = arF.createUnit(i, 0, str);
				cell[i][0].addUnit(w);
			}
			else if (num == 5) {
				string str = inv.GetValue();
				char sym = inv.GetCounter() + '0';
				str += sym;
				inv.SetCounter(inv.GetCounter() + 1);
				Warrior w = inviF.createUnit(i, 0, str);
				cell[i][0].addUnit(w);
			}
		}
		else {
			if (num == 4) {
				string str = ar.GetValue();
				char sym = ar.GetCounter() + '0';
				str += sym;
				ar.SetCounter(ar.GetCounter() + 1);
				Warrior w = arF.createUnit(i, 1, str);
				cell[i][1].addUnit(w);
			}
			else if (num == 5) {
				string str = inv.GetValue();
				char sym = inv.GetCounter() + '0';
				str += sym;
				inv.SetCounter(inv.GetCounter() + 1);
				Warrior w = inviF.createUnit(i, 1, str);
				cell[i][1].addUnit(w);
			}
		}

		num = rand() % 2;
		if (i % 2 == 0) {
			if (num == 0) {
				string str = dev.GetValue();
				char sym = dev.GetCounter() + '0';
				str += sym;
				dev.SetCounter(dev.GetCounter() + 1);
				Warrior w = devF.createUnit(i, size - 1, str);
				cell[i][size - 1].addUnit(w);
			}
			else if (num == 1) {
				string str = rob.GetValue();
				char sym = rob.GetCounter() + '0';
				str += sym;
				rob.SetCounter(rob.GetCounter() + 1);
				Warrior w = robF.createUnit(i, size - 1, str);
				cell[i][size - 1].addUnit(w);
			}
		}
		else {
			if (num == 0) {
				string str = dev.GetValue();
				char sym = dev.GetCounter() + '0';
				str += sym;
				dev.SetCounter(dev.GetCounter() + 1);
				Warrior w = devF.createUnit(i, size - 2, str);
				cell[i][size - 2].addUnit(w);
			}
			else if (num == 1) {
				string str = rob.GetValue();
				char sym = rob.GetCounter() + '0';
				str += sym;
				rob.SetCounter(rob.GetCounter() + 1);
				Warrior w = robF.createUnit(i, size - 2, str);
				cell[i][size - 2].addUnit(w);
			}
		}
	}

	for (int i = numOfElfs; i < numOfOrcs; i++) {
		num = 2 + rand() % 2;

		if (i % 2 == 0) {
			if (num == 2) {
				string str = sp.GetValue();
				char sym = sp.GetCounter() + '0';
				str += sym;
				sp.SetCounter(sp.GetCounter() + 1);
				Warrior w = spF.createUnit(i, 0, str);
				cell[i][0].addUnit(w);
			}
			else if (num == 3) {
				string str = wiz.GetValue();
				char sym = wiz.GetCounter() + '0';
				str += sym;
				wiz.SetCounter(wiz.GetCounter() + 1);
				Warrior w = wizF.createUnit(i, 0, str);
				cell[i][0].addUnit(w);
			}
		}
		else {
			if (num == 2) {
				string str = sp.GetValue();
				char sym = sp.GetCounter() + '0';
				str += sym;
				sp.SetCounter(sp.GetCounter() + 1);
				Warrior w = spF.createUnit(i, 1, str);
				cell[i][1].addUnit(w);
			}
			else if (num == 3) {
				string str = wiz.GetValue();
				char sym = wiz.GetCounter() + '0';
				str += sym;
				wiz.SetCounter(wiz.GetCounter() + 1);
				Warrior w = wizF.createUnit(i, 1, str);
				cell[i][1].addUnit(w);
			}
		}

		num = rand() % 2;

		if (i % 2 == 0) {
			if (num == 0) {
				string str = dev.GetValue();
				char sym = dev.GetCounter() + '0';
				str += sym;
				dev.SetCounter(dev.GetCounter() + 1);
				Warrior w = devF.createUnit(i, size - 1, str);
				cell[i][size - 1].addUnit(w);
			}
			else if (num == 1) {
				string str = rob.GetValue();
				char sym = rob.GetCounter() + '0';
				str += sym;
				rob.SetCounter(rob.GetCounter() + 1);
				Warrior w = robF.createUnit(i, size - 1, str);
				cell[i][size - 1].addUnit(w);
			}
		}
		else {
			if (num == 0) {
				string str = dev.GetValue();
				char sym = dev.GetCounter() + '0';
				str += sym;
				dev.SetCounter(dev.GetCounter() + 1);
				Warrior w = devF.createUnit(i, size - 2, str);
				cell[i][size - 2].addUnit(w);
			}
			else if (num == 1) {
				string str = rob.GetValue();
				char sym = rob.GetCounter() + '0';
				str += sym;
				rob.SetCounter(rob.GetCounter() + 1);
				Warrior w = robF.createUnit(i, size - 2, str);
				cell[i][size - 2].addUnit(w);
			}
		}
	}

	//----------------------------------------------
	//         СОЗДАНИЕ ЛАНДШАФТА
	//----------------------------------------------

	Landscape* l = nullptr;

	for (int i = 0; i < size / 2 + 2; i++) {               //левый верхний угол
		for (int j = 0; j < size / 2; j++) {
			cell[i][j].setLandscape(l->create(Forest_ID));
		}
	}

	for (int i = 0; i < size / 2 + 2; i++) {              //правый верхний угол
		for (int j = size / 2; j < size; j++) {
			cell[i][j].setLandscape(l->create(BurningEarth_ID));
		}
	}

	for (int i = size / 2 + 2; i < size; i++) {					//нижняя половина
		for (int j = 0; j < size; j++) {
			cell[i][j].setLandscape(l->create(UnknownLand_ID));
		}
	}

	//----------------------------------------------
	//         СОЗДАНИЕ НЕЙТРАЛЬНЫХ ОБЪЕКТОВ
	//----------------------------------------------

	NeutralObject* NO = nullptr;

	cell[size / 4][size / 4].setNeutral(NO->create(Killer_ID));
	cell[size / 4][size - size / 4].setNeutral(NO->create(Armor_ID));
	cell[size - size / 4][size - size / 4].setNeutral(NO->create(Freezer_ID));
	cell[size - size / 4][size / 4].setNeutral(NO->create(Health_ID));

	for (int i = 0; i < size; i++) {
		//bool exist = false;
		for (int j = 0; j < size; j++) {
			if ((i == size / 4 && j == size / 4) || (i == size / 4 && j == size - size / 4) || (i == size - size / 4 && j == size - size / 4) || (i == size - size / 4 && j == size / 4)) {
				//exist = true;
				continue;
			}
			cell[i][j].setNeutral(NO->create(NO_ID));
		} 
	}
	
}

void Field::moving(string& character, int direction) {
	int coordx = 0;
	int coordy = 0;
	Warrior w;
	// 1 - up, 2 - right, 3 - left, 4 - down, 5 - stay
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (cell[i][j].getUnit().GetValue() == character) {
				coordx = i;
				coordy = j;
				break;
			}
		}
	}

	string warriorToAttack = "";

	Warrior tmp = cell[coordx][coordy].getUnit();
	switch (direction) {
	case 1:
		cell[coordx][coordy].addUnit(cell[coordx - 1][coordy].moveUnit(tmp));
		break;

	case 2:
		cell[coordx][coordy].addUnit(cell[coordx][coordy + 1].moveUnit(tmp));
		break;

	case 3:
		cell[coordx][coordy].addUnit(cell[coordx][coordy - 1].moveUnit(tmp));
		break;

	case 4:
		cell[coordx][coordy].addUnit(cell[coordx + 1][coordy].moveUnit(tmp));
		break;

	case 6:
		w = cell[coordx - 1][coordy].getUnit();
		warriorToAttack = w.GetValue();
		cell[coordx][coordy].getUnit().attack(w);
		cell[coordx - 1][coordy].addUnit(w);
		break;

	case 7:
		w = cell[coordx][coordy + 1].getUnit();
		warriorToAttack = w.GetValue();
		cell[coordx][coordy].getUnit().attack(w);
		cell[coordx][coordy + 1].addUnit(w);
		break;

	case 8:
		w = cell[coordx][coordy - 1].getUnit();
		warriorToAttack = w.GetValue();
		cell[coordx][coordy].getUnit().attack(w);
		cell[coordx][coordy - 1].addUnit(w);
		break;

	case 9:
		w = cell[coordx + 1][coordy].getUnit();
		warriorToAttack = w.GetValue();
		cell[coordx][coordy].getUnit().attack(w);
		cell[coordx + 1][coordy].addUnit(w);
		break;

	default:
		cout << "Юнит остается на месте\n";
		break;
	}

	if (w.GetValue() == "---") {
		if (warriorToAttack[0] == 'O') {
			cout << "Персонаж " << warriorToAttack << " умер\n";
			current2ndPlayerUnits--;
		}
		else if (warriorToAttack[0] == 'E' || warriorToAttack[0] == 'M') {
			cout << "Персонаж " << warriorToAttack << " умер\n";
			current1stPlayerUnits--;
		}
	}
}

string Field::check(string& character) {
	int coordx = 0;
	int coordy = 0;
	// 1 - up, 2 - right, 3 - left, 4 - down, 5 - stay, 6 - attack upper, 7 - attack right, 8 - attack left, 9 - attack down
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (cell[i][j].getUnit().GetValue() == character) {
				coordx = i;
				coordy = j;
				break;
			}
		}
	}
	
	string opportunity = "5";
	string tmp = "---";
	if (cell[coordx][coordy].getUnit().GetAbilityToWalk() == 0) {
		cout << "Возможные варианты хода:\n";
		if (coordx != 0) {
			if (cell[coordx - 1][coordy].getUnit().GetValue() == tmp) {
				opportunity += '1';
				cout << "1 - вверх\n";
			}
			else {
				opportunity += '6';
				cout << "6 - атака юнита сверху\n";
			}
		}
		if (coordy != size - 1) {
			if (cell[coordx][coordy + 1].getUnit().GetValue() == tmp) {
				opportunity += '2';
				cout << "2 - вправо\n";
			}
			else {
				opportunity += '7';
				cout << "7 - атака юнита справа\n";
			}
		}
		if (coordy != 0) {
			if (cell[coordx][coordy - 1].getUnit().GetValue() == tmp) {
				opportunity += '3';
				cout << "3 - влево\n";
			}
			else {
				opportunity += '8';
				cout << "8 - атака юнита слева\n";
			}
		}
		if (coordx != size - 1) {
			if (cell[coordx + 1][coordy].getUnit().GetValue() == tmp) {
				opportunity += '4';
				cout << "4 - вниз\n";
			}
			else {
				opportunity += '9';
				cout << "9 - атака юнита снизу\n";
			}
		}

		cout << "5 - не двигаться\n";
	}

	else {
		Warrior w = cell[coordx][coordy].getUnit();
		w.SetAbilityToWalk(w.GetAbilityToWalk() - 1);
		cell[coordx][coordy].addUnit(w);
		cout << "Юнит не может ходить, так что единственный вариант: \n5 - не двигаться\n";
	}

	return opportunity;
}

Warrior Field::add(string& character, int coordx, int coordy) {
	Warrior w;
	if (coordx == -30) {
		cout << "Введите координаты (сначала x, затем y через enter):\n";
		cin >> coordx;
		if (cin.fail() || coordx > size - 1 || coordx < 0) return w;
		cin >> coordy;
		if (cin.fail() || coordy > size - 1 || coordy < 0) return w;
		if (cell[coordx][coordy].getUnit().GetValue() != "---") {
			cout << "Сюда нельзя поставить юнит!" << endl;
			return w;
		}
	}

	if (((character[0] == 'E' || character[0] == 'M') && current1stPlayerUnits > 10) || (character[0] == 'O' && current2ndPlayerUnits > 10)) {
		cout << "Юнитов слишком много!" << endl;
		return w;
	}

	if (cell[coordx][coordy].getUnit().GetValue() != "---") {
		cout << "Сюда нельзя поставить юнит" << endl;
		return w;
	}

	//"OD" "OR" "MS" "MW" "EA" "EI"

	ArcherFactory arF;
	SpearmanFactory spF;
	InvisibleFactory inviF;
	WizardFactory wizF;
	DevourerFactory devF;
	RobberFactory robF;

	if (character == "OD") {
		current2ndPlayerUnits++;
		char sym = dev.GetCounter() + '0';
		dev.SetCounter(dev.GetCounter() + 1);
		w = devF.createUnit(coordx, coordy, character + sym);
	}
	else if (character == "OR") {
		current2ndPlayerUnits++;
		char sym = rob.GetCounter() + '0';
		rob.SetCounter(rob.GetCounter() + 1);
		w = robF.createUnit(coordx, coordy, character + sym);
	}
	else if (character == "MS") {
		current1stPlayerUnits++;
		char sym = sp.GetCounter() + '0';
		sp.SetCounter(sp.GetCounter() + 1);
		w = spF.createUnit(coordx, coordy, character + sym);
	}
	else if (character == "MW") {
		current1stPlayerUnits++;
		char sym = wiz.GetCounter() + '0';
		wiz.SetCounter(wiz.GetCounter() + 1);
		w = wizF.createUnit(coordx, coordy, character + sym);
	}
	else if (character == "EA") {
		current1stPlayerUnits++;
		char sym = ar.GetCounter() + '0';
		ar.SetCounter(ar.GetCounter() + 1);
		w = arF.createUnit(coordx, coordy, character + sym);
	}
	else if (character == "EI") {
		current1stPlayerUnits++;
		char sym = inv.GetCounter() + '0';
		inv.SetCounter(inv.GetCounter() + 1);
		w = inviF.createUnit(coordx, coordy, character + sym);
	}

	cell[coordx][coordy].addUnit(w);
	return w;
}

void Field::del(string& character) {
	int coordx = 0;
	int coordy = 0;
	int check = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (cell[i][j].getUnit().GetValue() == character) {
				coordx = i;
				coordy = j;
				check = 1;
				break;
			}
		}
	}

	if (check == 0) {
		cout << "Такого персонажа на поле нет!\n";
		system("pause");
		return;
	}

	if (character[0] == 'M' || character[0] == 'E') current1stPlayerUnits--;
	else if (character[0] == 'O') current2ndPlayerUnits--;

	string tmp = "---";
	changeCell(tmp, coordx, coordy);
}

void Field::changeCell(string& valuee, int x, int y) {
	Warrior w;
	w.SetValue(valuee);
	w.SetPlaceX(x);
	w.SetPlaceY(y);
	cell[x][y].addUnit(w);
	//cell[x][y].getUnit().SetValue(valuee);
	//cell[x][y].SetPlaceX(x);
	//cell[x][y].SetPlaceY(y);
}

bool Field::isCellFree(int x, int y) {
	if (x > size - 1 || x < 0 || y > size - 1 || y < 0) return false;
	if (cell[x][y].getUnit().GetValue() != "---") return false;
	return true;
}

string Field::getValueInCell(int x, int y) {
	if (x > size - 1 || x < 0 || y > size - 1 || y < 0) return "";
	return cell[x][y].getUnit().GetValue();
}

Cell** Field::getCell() {
	return cell;
}

int Field::howManyMoves(string character) {
	int coordx = 0;
	int coordy = 0;
	int check = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (cell[i][j].getUnit().GetValue() == character) {
				coordx = i;
				coordy = j;
				check = 1;
				break;
			}
		}

		if (check == 1) break;
	}

	if (check == 0) {
		cout << "Такого персонажа на поле нет!\n";
		return -1;
	}

	Proxy* p = new Proxy(cell[coordx][coordy].getLandscape());
	if (p->canWalk2timesPerTurn(cell[coordx][coordy].getUnit())) {
		return 1;
	}
	else return 0;
}

void Field::landscapeEffect() {
	Proxy* p;
	for (int i = size / 2 + 2; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (cell[i][j].getUnit().GetValue() != "---") {
				p = new Proxy(cell[i][j].getLandscape());
				if (p->effectOfLndscp(cell[i][j].getUnit()) == "yes") {
					Warrior w = cell[i][j].getUnit();
					w.SetArmor(0);
					cell[i][j].addUnit(w);
				}
			}
		}
	}
}

void Field::neutObjEffect() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (cell[i][j].getUnit().GetValue() != "---") {
				if (cell[i][j].getNeutral()) {
					Warrior w = cell[i][j].getUnit();
					//*(cell[i][j].getNeutral()) += &(cell[i][j].getUnit());
					*(cell[i][j].getNeutral()) += &w;
					cell[i][j].addUnit(w);
					cell[i][j].delNeutral();
				}
			}
		}
	}
}
