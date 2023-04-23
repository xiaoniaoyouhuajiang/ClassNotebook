#include <iostream>
#include "Field.h"


Field::Field() {};

Field::Field(int max, int _h, int  _w)
{

	this->h = _h;
	this->w = _w;
	this->qmax = max;
	cur = 0;

	field = new Unit * *[h];

	for (int i = 0; i < h; i++) {

		field[i] = new Unit * [w];

		for (int j = 0; j < w; j++)

			field[i][j] = nullptr;


	}std::cout << "Field created\n";
};

Field::Field(const Field& f) {//конструктор копирования

	this->qmax = f.qmax;
	this->h = f.h;
	this->w = f.w;
	this->cur = 0;
	this->field = new Unit * *[h];

	for (int i = 0; i < h; i++) {

		this->field[i] = new Unit * [w];

		for (int k = 0; k < w; k++) {

			this->field[i][k] = f.field[i][k];


		}
	}std::cout << "Copy completed\n";
};

Field::Field(Field&& f) //конструктор перемещения

{
	field = f.field;
	this->qmax = f.qmax;
	this->h = f.h;
	this->w = f.w;
	this->cur = 0;
	f.field = nullptr;

};

Field& Field::operator= (const Field& f) {

	this->qmax = f.qmax;
	this->h = f.h;
	this->w = f.w;
	this->cur = 0;

	if (this->field != nullptr)

		delete[] this->field;

	this->field = new Unit * *[h];

	for (int i = 0; i < h; i++) {

		this->field[i] = new Unit * [w];

		for (int k = 0; k < w; k++) {

			this->field[i][k] = f.field[i][k];
		}
	}
	return *this;

}

Field& Field::operator= (const Field&& f) {

	this->qmax = f.qmax;
	this->h = f.h;
	this->w = f.w;
	this->cur = 0;

	if (this->field != nullptr)

		delete[] this->field;

	field = f.field;

	return *this;
};

void Field::AddObj(Unit* a, int x, int y) {


	if ((cur < qmax) && (0 < x < h) && (0 < y < h) && field[x][y] == nullptr) {

		field[x][y] = a;
		cur++;
		std::cout << "\nUnit added\n";

	}
	else
		std::cout << "Incorrect arguments";
};

void Field::RemObj(Unit *a, int x, int y) {

	if ((0 < x < h) && (0 < y < h) && field[x][y] == a) {

		field[x][y] = nullptr;
		cur--;
		std::cout << "\nUnit removed\n";
	}
	else
		std::cout << "Incorrect arguments";

};

void Field::Moving(Unit* a, int posx, int posy, int dx, int dy) {


	if ((dx > a->getSpeed()) && (posx + dx > h) && (posy + dy > w))

		std::cout << "Incorrect arguments";

	else {

		field[posx][posy] = nullptr;

		field[posx + dx][posy + dy] = a;

		std::cout << "\nUnit moved\n";


	}

};

Field* Field::CopyField(Field* a) {

	for (int i = 0; i < h; i++) {

		for (int k = 0; k < w; k++) {

			a->SetUnit(field[i][k], i, k);

		}
	}return a;

};


void Field::SetUnit(Unit* a, int b, int c) {

	field[b][c] = a;

};


void Field::PrintField() {

	for (int i = 0; i < h; i++) {

		std::cout << '\n';

		for (int k = 0; k < w; k++) {

			if (field[i][k] == nullptr)

				std::cout << "0 ";
			else
				std::cout << field[i][k]->getid() << ' ';
		}
	};

};

Iterator* Field::getIterator() const {
	return (new Iterator(*this));
}

Field::~Field() {

	delete[] field;
	std::cout << "\nField deleted\n";

};
