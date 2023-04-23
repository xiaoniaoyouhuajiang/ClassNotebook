#pragma once
#include "RightTriangle.h"
#include "Square.h"
#include "IsoscelesTriangle.h"
#include "SharedPtrStepik.h"
#include "vectorStepik.h"
bool pred_one(const stepik::shared_ptr<Shape> &test)
{
	return test->area() >= 3200.0;
}


bool pred_two(const stepik::shared_ptr<Shape> &test, const Point &testp)
{
	return test->insidePoint(testp);
}
