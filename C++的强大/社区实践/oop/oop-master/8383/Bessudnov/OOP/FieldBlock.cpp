#include "pch.h"
#include "FieldBlock.h"
#include "NeutralObject.h"
#include "UnitParent.h"


FieldBlock::FieldBlock(BlockTypes type) : blockType(type) {
	unit = nullptr;
	nObject = nullptr;
	if (type == BlockTypes::Boulder || type == BlockTypes::Base) {
		isWalkable = false;
	} else {
		isWalkable = true;
	}
}


FieldBlock::~FieldBlock() {
}

void FieldBlock::onMove(GameUnits &units) {
	if (unit && nObject) {
		*unit + nObject;
		nObject->erraseObject();
		nObject = nullptr;
	}
}
