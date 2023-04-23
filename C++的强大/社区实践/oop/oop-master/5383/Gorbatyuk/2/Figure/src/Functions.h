#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "IsoscelesTriangle.h"
#include "Shape.h"
#include "RightTriangle.h"
#include "Quadrate.h"
#include "Functions.h"
void RotateShape(CS *_points, CS _center, double _angle, int _size);
void MoveShape(CS *_points, CS _center, double _x, double _y, int _size);
void NewTriangleCenter(CS * _points, CS & _center);
void ScaleShape(CS * _points, CS _center, double _scale, int _size);
int ShapeTest(CS *_points, const CS *_shapePoints, int size, int i);
double Length(double _ax, double _ay, double _bx, double _by);
#endif
