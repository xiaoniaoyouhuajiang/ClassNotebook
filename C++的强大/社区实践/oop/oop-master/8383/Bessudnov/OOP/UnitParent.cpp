#include "pch.h"
#include "UnitParent.h"
#include "NeutralObject.h"
#include "GameField.h"
#include "GameBases.h"
#include "GameUnits.h"
#include "Logger.h"
#include <iostream>


UnitParent::UnitParent(const UnitParent &unit) {
	this->unitProps = unit.unitProps;
}

UnitParent & UnitParent::operator=(const UnitParent &unit) {
	if (this == &unit) return *this;

	this->unitProps = unit.unitProps;

	return *this;
}

UnitParent::~UnitParent() {
}

void UnitParent::updateLocation(Vector2D newBorders) {
	GameUtilities::clamp(unitProps.location.x, newBorders.x, 0);
	GameUtilities::clamp(unitProps.location.y, newBorders.y, 0);
}

void UnitParent::move(Vector2D direction, Vector2D borders) {
	unitProps.location.x += direction.x;
	unitProps.location.y += direction.y;

	GameUtilities::clamp(unitProps.location.x, borders.x, 0);
	GameUtilities::clamp(unitProps.location.y, borders.y, 0);

	GameUnitAdapter adapter(this);
	adapter.logUnitMove();
}


void UnitParent::setNewUnitLocation(Vector2D unitOffset, Vector2D borders) {
	unitProps.location.x += unitOffset.x;
	unitProps.location.y += unitOffset.y;

	GameUtilities::clamp(unitProps.location.x, borders.x, 0);
	GameUtilities::clamp(unitProps.location.y, borders.y, 0);
}

void BeeUnit::attack(Vector2D direction) {
	Vector2D currentAttackPostion;
	currentAttackPostion = unitProps.location;
	for (int i = 0; i < unitProps.moves.parameterValueCurrent; i++) {
		currentAttackPostion += direction;
		GameUtilities::clamp(currentAttackPostion, gameField->fieldProps.dimensions, Vector2D(0, 0));
		UnitParent *attackedUnit;
		attackedUnit = gameField->getBlockAtLocation(currentAttackPostion)->getUnit();

		if (attackedUnit) {
			attackedUnit->recieveDamage(unitProps.damage.parameterValueCurrent);
		}
	}
}

void FlyUnit::attack(Vector2D direction) {
	Vector2D currentAttackPostion;
	currentAttackPostion = unitProps.location;
	for (int i = 0; i < unitProps.moves.parameterValueCurrent; i++) {
		currentAttackPostion += direction;
		GameUtilities::clamp(currentAttackPostion, gameField->fieldProps.dimensions, Vector2D(0, 0));
		UnitParent *attackedUnit;
		attackedUnit = gameField->getBlockAtLocation(currentAttackPostion)->getUnit();

		if (attackedUnit) {
			attackedUnit->recieveDamage(unitProps.damage.parameterValueCurrent);
		}
	}
}

void CollectorUnit::attack(Vector2D direction) {
	Vector2D currentAttackPostion;
	currentAttackPostion = unitProps.location;
	for (int i = 0; i < unitProps.moves.parameterValueCurrent; i++) {
		currentAttackPostion += direction;
		GameUtilities::clamp(currentAttackPostion, gameField->fieldProps.dimensions, Vector2D(0, 0));
		UnitParent *attackedUnit;
		attackedUnit = gameField->getBlockAtLocation(currentAttackPostion)->getUnit();

		if (attackedUnit) {
			attackedUnit->recieveDamage(unitProps.damage.parameterValueCurrent);
		}
	}
}

void SprinklerUnit::attack(Vector2D direction) {
	Vector2D currentAttackPostion;
	currentAttackPostion = unitProps.location;
	for (int i = 0; i < unitProps.moves.parameterValueCurrent; i++) {
		currentAttackPostion += direction;
		GameUtilities::clamp(currentAttackPostion, gameField->fieldProps.dimensions, Vector2D(0, 0));
		UnitParent *attackedUnit;
		attackedUnit = gameField->getBlockAtLocation(currentAttackPostion)->getUnit();

		if (attackedUnit) {
			attackedUnit->recieveDamage(unitProps.damage.parameterValueCurrent);
		}
	}
}

void CoalUnit::attack(Vector2D direction) {
	Vector2D currentAttackPostion;
	currentAttackPostion = unitProps.location;
	for (int i = 0; i < unitProps.moves.parameterValueCurrent; i++) {
		currentAttackPostion += direction;
		GameUtilities::clamp(currentAttackPostion, gameField->fieldProps.dimensions, Vector2D(0, 0));
		UnitParent *attackedUnit;
		attackedUnit = gameField->getBlockAtLocation(currentAttackPostion)->getUnit();

		if (attackedUnit) {
			attackedUnit->recieveDamage(unitProps.damage.parameterValueCurrent);
		}
	}
}

void FlowerUnit::attack(Vector2D direction) {
	Vector2D currentAttackPostion;
	currentAttackPostion = unitProps.location;
	for (int i = 0; i < unitProps.moves.parameterValueCurrent; i++) {
		currentAttackPostion += direction;
		GameUtilities::clamp(currentAttackPostion, gameField->fieldProps.dimensions, Vector2D(0, 0));
		UnitParent *attackedUnit;
		attackedUnit = gameField->getBlockAtLocation(currentAttackPostion)->getUnit();

		if (attackedUnit) {
			attackedUnit->recieveDamage(unitProps.damage.parameterValueCurrent);
		}
	}
}

void operator+(UnitParent &unit, NeutralObject *object) {
	object->onExecute(&unit);
}

void GroundUnits::recieveDamage(int damage) {
	unitProps.sugar.increasePar(-damage);
	GameUnitAdapter adapter(this);
	adapter.logUnitRecieveDamage(damage);


	if (unitProps.sugar.parameterValueCurrent == 0) {
		adapter.logUnitDestroyed();
		units->ereaseUnit(this);
		baseOwner->removeUnit(this);
		adapter.logEvent(new LogEntry("Unit destroyed"));
	}

}

void GroundUnits::sacrafice() {
	baseOwner->dew.increaseVal(unitProps.dew.parameterValueCurrent);
	recieveDamage(unitProps.sugar.parameterValueCurrent);
}

void SmallUnits::recieveDamage(int damage) {
	unitProps.sugar.increasePar(-damage);
	GameUnitAdapter adapter(this);
	adapter.logUnitRecieveDamage(damage);


	if (unitProps.sugar.parameterValueCurrent == 0) {
		adapter.logUnitDestroyed();
		units->ereaseUnit(this);
		baseOwner->removeUnit(this);
		adapter.logEvent(new LogEntry("Unit destroyed"));
	}

}

void SmallUnits::sacrafice() {
	baseOwner->dew.increaseVal(unitProps.dew.parameterValueCurrent);
	recieveDamage(unitProps.sugar.parameterValueCurrent);
}

void FlyingUnits::recieveDamage(int damage) {
	unitProps.sugar.increasePar(-damage);
	GameUnitAdapter adapter(this);
	adapter.logUnitRecieveDamage(damage);


	if (unitProps.sugar.parameterValueCurrent == 0) {
		adapter.logUnitDestroyed();
		units->ereaseUnit(this);
		baseOwner->removeUnit(this);
		adapter.logEvent(new LogEntry("Unit destroyed"));
	}

}

void FlyingUnits::sacrafice() {
	baseOwner->dew.increaseVal(unitProps.dew.parameterValueCurrent);
	recieveDamage(unitProps.sugar.parameterValueCurrent);
}
