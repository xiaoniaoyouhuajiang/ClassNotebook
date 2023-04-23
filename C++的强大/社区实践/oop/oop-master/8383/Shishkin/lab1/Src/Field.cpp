#include "Field.h"
#include <iostream>
#include <time.h>

using namespace std;

Field::Field() {
	size = 3;
	x0 = 2; y0 = 2;
}

Field::Field(int a) {
	size = a;
	x0 = y0 = size - 1;
}

Field::~Field() {
	for (int i = 0; i < size; i++) {
		delete[] cell[i];
	}
}

Field::Field(const Field& f) {      //конструктор копирования
	this->size = f.size;
	this->x0 = f.x0;
	this->y0 = f.y0;
	this->mas();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cell[i][j] = f.cell[i][j];
		}
	}
}
 
Field::Field(Field&& f) : size(f.size), cell(f.cell){                    //конструктор перемещения
	cell = nullptr;
}

void Field::mas() {
	cell = new Warrior * [size];
	for (int i = 0; i < size; i++) {
		cell[i] = new Warrior[size];
	}
}

void Field::print() {
	for (int i = 0; i < (size + 1) * 4 - 2; i++) cout << "_";
	cout << endl;

	for (int i = 0; i < size; i++) {
		cout << "|";
		for (int j = 0; j < size; j++) {
			cout << " " << cell[i][j].GetValue();
		}
		cout << "|" << endl;
	}

	for (int i = 0; i < (size + 1) * 4 - 2; i++) cout << "_";
	cout << endl << endl << endl << endl;
	cout << "Подсказки:\n";
	cout << "OD - Orcs Devourers - орки пожиратели; OR - Orcs Robbers - орки разбойники\n";
	cout << "MS - Mens Spearman - люди копьеносцы; MW - Mens Wizard - люди маги\n";
	cout << "EA - Elfs Archer - эльф лучник; EI - Elfs Invisible - эльф невидимка\n";
	cout << "Введите \"exit\" для выхода, \"add\" - для добавления персонажа, \"del\" - для удаления персонажа\n";
	cout << endl;
}

void Field::init(int numOfOrcs, int numOfElfs, int numOfMens) {
	mas();
	srand(time(0));

	Devourers dev;
	Robbers rob;

	Spearman sp;
	Wizard wiz;

	Archer ar;
	Invisible inv;

	int half = size / 2;
	string d = dev.GetValue();   // 0
	string r = rob.GetValue();   // 1
	string s = sp.GetValue();    // 2
	string w = wiz.GetValue();   // 3
	string a = ar.GetValue();    // 4
	string invi = inv.GetValue();   // 5

	int num = 0;
	for (int i = 0; i < numOfElfs; i++) {
		num = 4 + rand() % 2;

		if (i % 2 == 0) {
			if (num == 4) {
				ar.SetCounter(ar.GetCounter() + 1);
				char sym = ar.GetCounter() + '0';
				cell[i][0].SetValue(a + sym);
			}
			else if (num == 5) {
				inv.SetCounter(inv.GetCounter() + 1);
				char sym = inv.GetCounter() + '0';
				cell[i][0].SetValue(invi + sym);
			}
			cell[i][0].SetPlaceX(i);
			cell[i][0].SetPlaceY(0);
		}
		else {
			if (num == 4) {
				ar.SetCounter(ar.GetCounter() + 1);
				char sym = ar.GetCounter() + '0';
				cell[i][1].SetValue(a + sym);
			}
			else if (num == 5) {
				inv.SetCounter(inv.GetCounter() + 1);
				char sym = inv.GetCounter() + '0';
				cell[i][1].SetValue(invi + sym);
			}
			cell[i][1].SetPlaceX(i);
			cell[i][1].SetPlaceY(1);
		}

		num = rand() % 2;
		if (i % 2 == 0) {
			if (num == 0) {
				dev.SetCounter(dev.GetCounter() + 1);
				char sym = dev.GetCounter() + '0';
				cell[i][size - 1].SetValue(d + sym);
			}
			else if (num == 1) {
				rob.SetCounter(rob.GetCounter() + 1);
				char sym = rob.GetCounter() + '0';
				cell[i][size - 1].SetValue(r + sym);
			}
			cell[i][size - 1].SetPlaceX(i);
			cell[i][size - 1].SetPlaceY(size - 1);
		}
		else {
			if (num == 0) {
				dev.SetCounter(dev.GetCounter() + 1);
				char sym = dev.GetCounter() + '0';
				cell[i][size - 2].SetValue(d + sym);
			}
			else if (num == 1) {
				rob.SetCounter(rob.GetCounter() + 1);
				char sym = rob.GetCounter() + '0';
				cell[i][size - 2].SetValue(r + sym);
			}
			cell[i][size - 2].SetPlaceX(i);
			cell[i][size - 2].SetPlaceY(size - 2);
		}
	}

	for (int i = numOfElfs; i < numOfOrcs; i++) {
		num = 2 + rand() % 2;

		if (i % 2 == 0) {
			if (num == 2) {
				sp.SetCounter(sp.GetCounter() + 1);
				char sym = sp.GetCounter() + '0';
				cell[i][0].SetValue(s + sym);
			}
			else if (num == 3) {
				wiz.SetCounter(wiz.GetCounter() + 1);
				char sym = wiz.GetCounter() + '0';
				cell[i][0].SetValue(w + sym);
			}
			cell[i][0].SetPlaceX(i);
			cell[i][0].SetPlaceY(0);
		}
		else {
			if (num == 2) {
				sp.SetCounter(sp.GetCounter() + 1);
				char sym = sp.GetCounter() + '0';
				cell[i][1].SetValue(s + sym);
			}
			else if (num == 3) {
				wiz.SetCounter(wiz.GetCounter() + 1);
				char sym = wiz.GetCounter() + '0';
				cell[i][1].SetValue(w + sym);
			}
			cell[i][1].SetPlaceX(i);
			cell[i][1].SetPlaceY(1);
		}

		num = rand() % 2;

		if (i % 2 == 0) {
			if (num == 0) {
				dev.SetCounter(dev.GetCounter() + 1);
				char sym = dev.GetCounter() + '0';
				cell[i][size - 1].SetValue(d + sym);
			}
			else if (num == 1) {
				rob.SetCounter(rob.GetCounter() + 1);
				char sym = rob.GetCounter() + '0';
				cell[i][size - 1].SetValue(r + sym);
			}
			cell[i][size - 1].SetPlaceX(i);
			cell[i][size - 1].SetPlaceY(size - 1);
		}
		else {
			if (num == 0) {
				dev.SetCounter(dev.GetCounter() + 1);
				char sym = dev.GetCounter() + '0';
				cell[i][size - 2].SetValue(d + sym);
			}
			else if (num == 1) {
				rob.SetCounter(rob.GetCounter() + 1);
				char sym = rob.GetCounter() + '0';
				cell[i][size - 2].SetValue(r + sym);
			}
			cell[i][size - 2].SetPlaceX(i);
			cell[i][size - 2].SetPlaceY(size - 2);
		}
	}
	
}

void Field::moving(string character, int direction) {
	int coordx;
	int coordy;
	// 1 - up, 2 - right, 3 - left, 4 - down, 5 - stay
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (cell[i][j].GetValue() == character) {
				//coordx = cell[i][j].GetPlaceX();
				//coordy = cell[i][j].GetPlaceY();
				coordx = i;
				coordy = j;
				break;
			}
		}
	}

	Warrior tmp;
	switch (direction) {
	case 1:
		cell[coordx - 1][coordy].SetValue(cell[coordx][coordy].GetValue());
		cell[coordx][coordy].SetValue("---");
		cell[coordx - 1][coordy].SetPlaceX(coordx-1);
		cell[coordx][coordy].SetPlaceX(coordx);
		cout << "x - " << coordx - 1 << ", y - " << coordy << endl;
		break;

	case 2:
		cell[coordx][coordy + 1].SetValue(cell[coordx][coordy].GetValue());
		cell[coordx][coordy].SetValue("---");
		cell[coordx][coordy + 1].SetPlaceY(coordy + 1);
		cell[coordx][coordy].SetPlaceY(coordy);
		break;

	case 3:
		cell[coordx][coordy - 1].SetValue(cell[coordx][coordy].GetValue());
		cell[coordx][coordy].SetValue("---");
		cell[coordx][coordy - 1].SetPlaceY(coordy - 1);
		cell[coordx][coordy].SetPlaceY(coordy);
		break;

	case 4:
		cell[coordx + 1][coordy].SetValue(cell[coordx][coordy].GetValue());
		cell[coordx][coordy].SetValue("---");
		cell[coordx + 1][coordy].SetPlaceX(coordx + 1);
		cell[coordx][coordy].SetPlaceX(coordx);
		break;
	}
}

string Field::check(string character) {
	int coordx = 0;
	int coordy = 0;
	// 1 - up, 2 - right, 3 - left, 4 - down, 5 - stay
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (cell[i][j].GetValue() == character) {
				//coordx = cell[i][j].GetPlaceX();
				//coordy = cell[i][j].GetPlaceY();
				coordx = i;
				coordy = j;
				break;
			}
		}
	}
	
	string opportunity = "5";
	string tmp = "---";

	cout << "Возможные варианты хода:\n";
	if (coordx != 0) {
		if (cell[coordx - 1][coordy].GetValue() == tmp) {
			opportunity += '1';
			cout << "1 - вверх\n";
		}
	}
	if (coordy != size - 1) {
		if (cell[coordx][coordy + 1].GetValue() == tmp) {
			opportunity += '2';
			cout << "2 - вправо\n";
		}
	}
	if (coordy != 0) {
		if (cell[coordx][coordy - 1].GetValue() == tmp) {
			opportunity += '3';
			cout << "3 - влево\n";
		}
	}
	if (coordx != size - 1) {
		if (cell[coordx + 1][coordy].GetValue() == tmp) {
			opportunity += '4';
			cout << "4 - вниз\n";
		}
	}

	cout << "5 - не двигаться\n";

	return opportunity;
}

void Field::add(string character) {
	int coordx = 0;
	int coordy = 0;

	cout << "Введите координаты (сначала x, затем y через enter):\n";
	cin >> coordx;
	if (cin.fail() || coordx > size - 1 || coordx < 0) return;
	cin >> coordy;
	if (cin.fail() || coordy > size - 1 || coordy < 0) return;
	if (cell[coordx][coordy].GetValue() != "---") return;

	/*Warrior w;
	//"OD" "OR" "MS" "MW" "EA" "EI"
	if (character == "OD") {
		w = Warrior::createWarrior(Devourers_ID);
	}
	else if (character == "OR") {

	}
	else if (character == "MS") {

	}
	else if (character == "MW") {

	}
	else if (character == "EA") {

	}
	else if (character == "EI") {

	}

	string ww = w.GetValue();
	w.SetCounter(w.GetCounter() + 1);
	char sym = w.GetCounter() + '0';
	cell[coordx][coordy].SetValue(ww + sym);*/
	
}

void Field::del(string character) {
	int coordx = 0;
	int coordy = 0;
	int check = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (cell[i][j].GetValue() == character) {
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

	cell[coordx][coordy].SetValue("---");
}
