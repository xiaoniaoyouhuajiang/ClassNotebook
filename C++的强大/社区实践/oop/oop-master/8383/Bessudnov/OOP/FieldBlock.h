#pragma once
#include "Interfaces.h"
#include <iostream>
class UnitParent;
class NeutralObject;
class GameBase;

enum BlockTypes {Grass, Boulder, Water, Bush, Base};

class FieldBlock : public IBlocks {
private:
	UnitParent *unit;
	NeutralObject *nObject;
	GameBase *base;
public:
	BlockTypes blockType;
	bool isWalkable;

	FieldBlock() : blockType(BlockTypes::Grass){
		unit = nullptr;
		nObject = nullptr;
	}

	FieldBlock(BlockTypes type);
	~FieldBlock();

	virtual void onMove(GameUnits &units);
	virtual void onAttack() {};
	virtual void onConversion() {};

	void setUnit(UnitParent *unit) {
		this->unit = unit;
	}

	UnitParent *getUnit() {
		return unit;
	}

	void setObject(NeutralObject *object) {
		this->nObject = object;
	}

	NeutralObject* getObject() {
		return nObject;
	}

	void setBase(GameBase *base) {
		this->base = base;
	}

	GameBase *getBase() {
		return base;
	}
};

class GrassBlock : public FieldBlock {
public:
	GrassBlock() {
		blockType = BlockTypes::Grass;
		isWalkable = true;
	}
};

class BoulderBlock : public FieldBlock {
public:
	BoulderBlock() {
		blockType = BlockTypes::Boulder;
		isWalkable = false;
	}
};

class WaterBlock : public FieldBlock {
public:
	WaterBlock() {
		blockType = BlockTypes::Water;
		isWalkable = true;
	}
};

class BushBlock : public FieldBlock {
public:
	BushBlock() {
		blockType = BlockTypes::Bush;
		isWalkable = true;
	}
};

class BaseBlock : public FieldBlock {
public:
	BaseBlock() {
		blockType = BlockTypes::Base;
		isWalkable = false;
	}
};
