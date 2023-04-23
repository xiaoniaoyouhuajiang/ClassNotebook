#include "MovingUnitChain.h"

MovingUnitResult MovingUnitCoordinatesCheck::execute(Field& fld, int x_from, int y_from, int x_to, int y_to)
{
	if	(x_from < 0 || x_from >= fld.getX_SIZE() || y_from < 0 || y_from >= fld.getY_SIZE() ||
			     x_to < 0 || x_to >= fld.getX_SIZE() || y_to < 0 || y_to >= fld.getY_SIZE())
		return MovingUnitResult::IncorrectCoordinates;

	return next.execute(fld, x_from, y_from, x_to, y_to);
}

MovingUnitResult MovingUnitNoUnitCheck::execute(Field& fld, int x_from, int y_from, int x_to, int y_to)
{
	if (fld.getUNIT_FIELD()[x_from + fld.getX_SIZE() * y_from] == nullptr)
		return MovingUnitResult::NoUnit;

	return next.execute(fld, x_from, y_from, x_to, y_to);
}

MovingUnitResult MovingUnitCollisionCheck::execute(Field& fld, int x_from, int y_from, int x_to, int y_to)
{
	if (fld.getUNIT_FIELD()[x_to + fld.getX_SIZE() * y_to] != nullptr)
		return MovingUnitResult::Colission;

	return MovingUnitResult::Ok;

}
