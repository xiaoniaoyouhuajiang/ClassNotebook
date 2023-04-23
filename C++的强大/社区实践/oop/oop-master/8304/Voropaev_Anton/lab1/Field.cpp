#include <iostream>
#include "Field.h"
#include "Unit.h"


Field::~Field() {
	for (int i = 0; i < size.width * size.height; ++i)
		delete head[i];

	delete[] head;
}


Field::Field(const Field& field) {
    if (this != &field) {

        this->maxQuantity = field.maxQuantity;

        this->currentQuantity = field.currentQuantity;

        this->size = field.size;

        delete[] head;

        this->head = new Unit *[field.size.width * field.size.height];
        for (int i = 0; i < this->size.width * this->size.height; ++i) {
            head[i] = nullptr;

            for (int j = 0; j < field.size.width * field.size.height; ++j) {
                if (!field.head[j])
                    continue;
                else
                    this->head[j] = field.head[j]->clone();
            }
        }
    }
}


Field::Field(int width, int height) {
    if ((width <= 0) || (height <= 0)){
        std::cout << "Empty/Negative size field cannot be created\n";
        return;
    }

	this->head = new Unit*[width * height];
	this->size.width = width;
	this->size.height = height;

	for (int i = 0; i < this->size.width * this->size.height; ++i) {
		head[i] = nullptr;
	}

}


Field::Field(Field&& other) noexcept {

    this->currentQuantity = other.currentQuantity;
    this->size = other.size;
    this->maxQuantity = other.maxQuantity;

	this->head = other.head;
	other.head = nullptr;

}


Field& Field::operator=(const Field &field) {

	if (this != &field) {

		this->maxQuantity = field.maxQuantity;

		this->currentQuantity = field.currentQuantity;

		this->size = field.size;

		delete[] head;

		this->head = new Unit* [field.size.width * field.size.height];

		for (int i = 0; i < field.size.width * field.size.height; ++i)
            this->head[i] = field.head[i]->clone();

	}
	return *this;
}


bool Field::moveUnit(int xPos, int yPos, int dX, int dY) {
    if (((dX > (this->getSize().width - 1) - xPos) || (dY > (this->getSize().height - 1) - yPos))
        || ((xPos + dX < 0) || (yPos + dY < 0))) {
        std::cout << "Cant step out of field's borders\n";
        return false;
    }

    if (head[yPos * size.width + xPos] == nullptr ||
        head[(yPos + dY) * size.width + xPos + dX] != nullptr) {
        std::cout << "Can't move non-existent object / Can't move to a taken position\n";
        return false;
    }

    head[(yPos + dY) * size.width + xPos + dX] = head[yPos * size.width + xPos];
    head[yPos * size.width + xPos] = nullptr;
    return true;
}


void Field::addObj(Unit* object, int xPos, int yPos) {
    if(object == nullptr) {
        std::cout << "If you want to delete an object use removeObject instead\n";
        return;
    }
	if (currentQuantity + 1 <= maxQuantity) {
        if (head[size.width * yPos + xPos] == nullptr) {
            head[size.width * yPos + xPos] = object;
            ++currentQuantity;
            ((Unit *) object)->setPosition(xPos, yPos);
        }
        else {
            std::cout << "This position is already taken by another unit\n";
            return;
        }
    }
	else {
	    std::cout << "Field contains maximum quantity of objects\n";
	}

}


void Field::removeObj(Location pos) {
    if(head[(pos.getPosition().second - 1) * this->size.width + pos.getPosition().first] == nullptr){
        std::cout << "Invalid position of unit\n";
        return;
    }
	head[(pos.getPosition().second - 1) * this->size.width + pos.getPosition().first] = nullptr;
	--currentQuantity;
}


f_size Field::getSize() const {
	return this->size;
}


int Field::getMax() const {
	return this->maxQuantity;
}


void Field::setLimit(int lim) {
    if(lim < 0) {
        std::cout << "Field cannot contain negative quantity of objects\n";
    }
	this->maxQuantity = lim;
}


int Field::getQuantity() const {
	return this->currentQuantity;
}

Unit **Field::GetHead() const {
    return this->head;
}


Iterator* Field::getIterator() const {
    return (new Iterator(*this));
}


