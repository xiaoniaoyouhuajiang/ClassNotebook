#pragma once
#include "Field.h"

enum class MovingUnitResult
{
	IncorrectCoordinates,
	NoUnit,
	Colission,
	Ok
};

class MovingUnitChainInterface
{
public:
	virtual MovingUnitResult execute(Field& fld, int x_from, int y_from, int x_to, int y_to) = 0;
};


class MovingUnitCollisionCheck
{
public:
	MovingUnitResult execute(Field& fld, int x_from, int y_from, int x_to, int y_to);
};

class MovingUnitNoUnitCheck
{
	MovingUnitCollisionCheck next;
public:
	MovingUnitResult execute(Field& fld, int x_from, int y_from, int x_to, int y_to);
};

class MovingUnitCoordinatesCheck
{
	MovingUnitNoUnitCheck next;
public:
	MovingUnitResult execute(Field& fld, int x_from, int y_from, int x_to, int y_to);
};