#pragma once
#include "stdafx.h"
#include "my_list.h"
#include "GameObjects.h"
#include "BaseLandscape.h"
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
	GameMap(const GameMap&& copy);

	~GameMap();

	bool addObject(BaseUnit& obj);
	bool removeObject(BaseUnit& obj);

	std::shared_ptr<BaseUnit> Check(int x, int y);

	bool moveObject(std::shared_ptr<BaseUnit> obj, int x, int y);

	GameMap& operator=(const GameMap& copy);

	typedef OwnIterator<MyList> iterator;

	iterator begin();

	MyList getObjects();

	void setUserBase(MapStructure& base_);
	void setEnemyBase(MapStructure& base_);

	std::shared_ptr<MapStructure> UserBase() {
		return base;
	}
	std::shared_ptr<MapStructure> EnemyBase() {
		return base;
	}

	void unitStatistic() {
		Obj.PrintAll();
	}

	BaseLandscape* checkLand(int x, int y) {
		return landescape->checkLand(x, y);
	}

	void printLand() {
		landescape->PrintLAndscape();
	}

	void printNObj() {
		nObj->printAll();
	}

	void createNObj(int x, int y, int type) {
		NeutralFactory NF;
		switch (type)
		{
		case 1:
			nObj->addNObj(NF.createMedicallStation(x, y));
			break;
		case 2:
			nObj->addNObj(NF.createStable(x, y));
			break;
		case 3:
			nObj->addNObj(NF.createForge(x, y));
			break;
		case 4:
			nObj->addNObj(NF.createWizardsTower(x, y));
			break;
		default:
			break;
		}
	}

	bool endGame() {
		return base->Alive() && enemy->Alive();
	}
private:

	int ObjectNumber;
	int MaxObjectNumber;

	int y_size;
	int x_size;

	std::shared_ptr<MapStructure> base;
	std::shared_ptr<MapStructure> enemy;

	LandscapeComposite* landescape;
	NeutralContainer* nObj;
	MyList Obj;
};
