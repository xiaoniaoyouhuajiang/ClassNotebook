#include "stdafx.h"
#include "GameMap.h"

GameMap::GameMap(int x, int y)
{

	if (x > 0 && y > 0) {
		MaxObjectNumber = x * y;
		ObjectNumber = 0;
		x_size = x;
		y_size = y;
	}
	else {
		MaxObjectNumber = 0;
		ObjectNumber = 0;
		x_size = 0;
		y_size = 0;
	}
}

GameMap::GameMap(const GameMap& copy) {

	MaxObjectNumber = copy.MaxObjectNumber;
	ObjectNumber = copy.ObjectNumber;
	x_size = copy.x_size;
	y_size = copy.y_size;
	Obj = copy.Obj;
}

GameMap::~GameMap()
{

}

GameMap& GameMap::operator=(const GameMap& copy) {

	MaxObjectNumber = copy.MaxObjectNumber;
	ObjectNumber = copy.ObjectNumber;
	x_size = copy.x_size;
	y_size = copy.y_size;
	Obj = copy.Obj;

	return *this;

}

bool GameMap::addObject(BaseUnit& obj) {

	if (obj.getX() >= 0 && obj.getY() >= 0) {

		if (Obj.Find(obj.getX(), obj.getY()) == nullptr && ObjectNumber < MaxObjectNumber) {

			Obj.Push(obj);

			ObjectNumber++;

			return true;
		}

		return false;

	}
	else {

		/*Бросить ошибку "Мимо игрового поля"*/
		return false;

	}

}
bool GameMap::removeObject(BaseUnit& obj) {

	if (Obj.Remove(obj.getX(), obj.getY())) {
		ObjectNumber--;
		return true;
	}
	return false;
}

std::shared_ptr<BaseUnit> GameMap::Check(int x, int y) {

	return Obj.Find(x, y);
}

bool GameMap::moveObject(std::shared_ptr<BaseUnit> obj, int x, int y) {

	if (x >= 0 && y >= 0 && x < x_size && y < y_size) {
		if (Check(x, y) == nullptr) {
			obj->Move(x, y);
			return true;
		}
		else {
			return false;
		}
	}
	else {
		/*Бросить ошибку*/
		return false;
	}
}


GameMap::iterator GameMap::begin()
{
	return iterator(Obj.begin());
}


MyList GameMap::getObjects() {
	return Obj;
}

/*
##################################
Функции итератора
##################################
*/

template<typename ValueType>
OwnIterator<ValueType>::OwnIterator(ValueType* p) : p(p)
{

}

template<typename ValueType>
bool OwnIterator<ValueType>::operator!=(OwnIterator const& other) const
{
	return p != other.p;
}

template<typename ValueType>
bool OwnIterator<ValueType>::operator==(OwnIterator const& other) const
{
	return p == other.p;
}

template<typename ValueType>
typename OwnIterator<ValueType>::reference OwnIterator<ValueType>::operator*() const{
	return *p;
}

template<typename ValueType>
OwnIterator<ValueType>& OwnIterator<ValueType>::operator++()
{
	++p;
	return this;
}