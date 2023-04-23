#pragma once
#include <variant>
#include <utility>
#include <memory>
#include <cstring>
#include <vector>
#include "Unit Attributes/Location.h"
#include "Cell.h"
#include "Landscapes/LandscapeProxy.h"
#include <algorithm>
#include "Base.h"
#include "Neutral objects/Forge.h"
#include "Neutral objects/HealingFountain.h"
#include "Neutral objects/TrainingCamp.h"
#include "Neutral objects/MaradeursCamp.h"
#include "FieldIterator.h"
#include "UnitFactory.h"

class Base;
class Iterator;

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

	~Field() = default;

	Field(const Field &field_to_copy);

	Field(int width, int height);

	Field(Field&& other) noexcept;

    void print() const;

	Field& operator=(const Field &proc_field);

	Iterator* begin() ;

	Iterator* end();

	bool moveUnit(int xPos, int yPos, int dX, int dY);

	bool addObj(Object* object, int yPos, int xPos);

	void removeObj(Location pos);

	f_size getSize() const;

	int getMax() const;

	void setLimit(int lim);

	int getQuantity() const;

	void setBase(Base* new_base);

	Base* getBase();

    std::shared_ptr<std::shared_ptr<cell[]>[]> getHead() const;

    void landscape_interaction(Object* obj, int x, int y);

    Iterator* getIterator();

    int currentQuantity = 0;

private:
	f_size size = { 0, 0 };

	std::shared_ptr<std::shared_ptr<cell[]>[]> field;

	int maxQuantity = 15;

	Base* base;

};


