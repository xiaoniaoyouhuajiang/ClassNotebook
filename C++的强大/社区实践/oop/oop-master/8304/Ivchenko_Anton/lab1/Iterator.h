#pragma once
#include "Field.h"
#include "Unit.h"

class Iterator
{
public:
	Iterator(Field& field) : gameField(field) {

		this->i = 0;
		this->j = 0;
		this->width = field.w;
		this->height = field.h;
	};

	bool hasNext() const {
		return i < gameField.h && j < gameField.w;

	};

	void first() {
		j = 0;
		i = 0;
	};

	friend const Iterator& operator--(Iterator& it) {
		if (it.j + 1 < it.width) {
			++it.j;
		}
		else {
			++it.i;
			it.j = 0;
		}

		return it;
	};

	friend const Iterator& operator++(Iterator& it) {
		if (it.j - 1 >= 0) {
			--it.j;
		}
		else {
			--it.i;
			it.j = it.width - 1;
		}

		return it;
	};
	Unit** operator*() const {
		return gameField.field[i * this->width + j];
	};


private:
	size_t i;
	size_t j;
	size_t width;
	size_t height;
	Field &gameField;
};
