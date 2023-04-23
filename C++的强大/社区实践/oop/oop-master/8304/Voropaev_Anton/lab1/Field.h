#pragma once
#include <variant>
#include <utility>
#include <memory>
#include "Unit.h"
#include "FieldIterator.h"
#include <cstring>

typedef struct fieldSize {
	int width, height;

	fieldSize(int width, int height) {
		this->width = width;
		this->height = height;
	}

	fieldSize(const fieldSize &f) {
		this->width = f.width;
		this->height = f.height;
	}

	fieldSize() = default;

}f_size;


class Field
{
public:

	Field() = default;

	~Field();

	Field(const Field &f);

	Field(int width, int height);

	Field(Field&& other) noexcept;

	Field& operator=(const Field &field);

	bool moveUnit(int xPos, int yPos, int dX, int dY);

	void addObj(Unit* object, int xPos, int yPos);

	void removeObj(Location pos);

	f_size getSize() const;

	int getMax() const;

	void setLimit(int lim);

	int getQuantity() const;

	Unit** GetHead() const;

    Iterator* getIterator() const;


private:
	f_size size = { 0, 0 };

	Unit** head = nullptr;

	int maxQuantity = 15;

	int currentQuantity = 0;

};


