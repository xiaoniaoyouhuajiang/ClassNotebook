#pragma once
#include "stdafx.h"
#include "my_list.h"
#include "GameObjects.h"


/*
##################################
Делаем свой итератор
##################################
*/

template<typename ValueType>
class OwnIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
	friend class OwnContainer;
private:
public:
	OwnIterator(ValueType* p);
	bool operator!=(OwnIterator const& other) const;
	bool operator==(OwnIterator const& other) const;
	typename OwnIterator<ValueType>::reference operator*() const;
	OwnIterator<ValueType>& operator++();
private:
	ValueType* p;
};

/*
##################################
Делаем игровое поле
##################################
*/

class GameMap
{
public:
	GameMap(int x, int y);
	GameMap(const GameMap& copy);

	~GameMap();

	bool addObject(BaseUnit& obj);
	bool removeObject(BaseUnit& obj);

	std::shared_ptr<BaseUnit> Check(int x, int y);

	bool moveObject(std::shared_ptr<BaseUnit> obj, int x, int y);

	GameMap& operator=(const GameMap& copy);

	typedef OwnIterator<MyList> iterator;

	iterator begin();

	MyList getObjects();

private:

	int ObjectNumber;
	int MaxObjectNumber;

	int y_size;
	int x_size;

	MyList Obj;
};
