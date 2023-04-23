#pragma once
#include "pch.h"

class Vector2D;
class GameUnits;
class LogEntry;
class UnitParent;


class ILogger{
public:
	virtual ~ILogger() = default;
	virtual void logEvent(LogEntry *entry) = 0;
};

class IUnits {
public:
	virtual ~IUnits() {}
	virtual void attack(Vector2D direction) = 0;
	virtual void move(Vector2D direction, Vector2D borders) = 0;
	virtual void updateLocation(Vector2D newBorders) = 0;
};

class IBlocks {
public:
	virtual ~IBlocks() {}
	virtual void onMove(GameUnits &units) = 0;
	virtual void onAttack() = 0;
	virtual void onConversion() = 0;
};

class INeutralObjects {
public:
	virtual ~INeutralObjects() {}
	virtual void onExecute(UnitParent *unit) = 0;
};

class IObserver {
public:
	virtual ~IObserver() {}
	virtual void update() = 0;
};


