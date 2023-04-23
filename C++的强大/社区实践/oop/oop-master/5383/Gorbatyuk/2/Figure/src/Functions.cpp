#include "stdafx.h"
#include "Functions.h"

#define PI 3.14159265  

void RotateShape(CS * _points, CS _center, double _angle, int _size)
{
	double tempX;
	double tempY;
	for (int i = 0; i < _size; i++)
	{
		tempX = (_points[i].x - _center.x) * cos(_angle * PI / 180) - (_points[i].y - _center.y) * sin(_angle * PI / 180) + _center.x;
		tempY = (_points[i].x - _center.x) * sin(_angle * PI / 180) + (_points[i].y - _center.y) * cos(_angle * PI / 180) + _center.y;
		_points[i].x = tempX;
		_points[i].y = tempY;
	}
}

void MoveShape(CS *_points, CS _center, double _x, double _y, int _size) 
{
	for (int i = 0; i < _size; i++)
	{
		_points[i].x += _x - _center.x;
		_points[i].y += _y - _center.y;
	}
}

void NewTriangleCenter(CS * _points, CS & _center)
{
	_center.x = (_points[0].x + _points[1].x + _points[2].x) / 3;
	_center.y = (_points[0].y + _points[1].y + _points[2].y) / 3;
}

void ScaleShape(CS * _points, CS _center, double _scale, int _size)
{
	try {
		if (_scale == 0)
			throw "Scale is 0";
		for (int i = 0; i < _size; i++) {
			_points[i].x = _center.x + (_points[i].x - _center.x) * abs(_scale);
			_points[i].y = _center.y + (_points[i].y - _center.y) * abs(_scale);
		}
	}

	catch (char *str) {
			cout << str << endl;
		}
}

int ShapeTest(CS *_points, const CS *_shapePoints, int size, int i)
{
	int sum = 0;
	switch (size)
	{
	case 3:
	{
		double temp1 = (_shapePoints[0].x - _points[i].x) * (_shapePoints[1].y - _shapePoints[0].y) - (_shapePoints[1].x - _shapePoints[0].x) * (_shapePoints[0].y - _points[i].y);
		double temp2 = (_shapePoints[1].x - _points[i].x) * (_shapePoints[2].y - _shapePoints[1].y) - (_shapePoints[2].x - _shapePoints[1].x) * (_shapePoints[1].y - _points[i].y);
		double temp3 = (_shapePoints[2].x - _points[i].x) * (_shapePoints[0].y - _shapePoints[2].y) - (_shapePoints[0].x - _shapePoints[2].x) * (_shapePoints[2].y - _points[i].y);
		if ((temp1 > 0 && temp2 > 0 && temp3 > 0) || (temp1 < 0 && temp2 < 0 && temp3 < 0))
			return 1;
		else
			return 0;
	}
	break;
	case 4:
	{
		double temp1 = (_shapePoints[0].x - _points[i].x) * (_shapePoints[1].y - _shapePoints[0].y) - (_shapePoints[1].x - _shapePoints[0].x) * (_shapePoints[0].y - _points[i].y);
		double temp2 = (_shapePoints[1].x - _points[i].x) * (_shapePoints[2].y - _shapePoints[1].y) - (_shapePoints[2].x - _shapePoints[1].x) * (_shapePoints[1].y - _points[i].y);
		double temp3 = (_shapePoints[2].x - _points[i].x) * (_shapePoints[3].y - _shapePoints[2].y) - (_shapePoints[3].x - _shapePoints[2].x) * (_shapePoints[2].y - _points[i].y);
		double temp4 = (_shapePoints[3].x - _points[i].x) * (_shapePoints[0].y - _shapePoints[3].y) - (_shapePoints[0].x - _shapePoints[3].x) * (_shapePoints[3].y - _points[i].y);
		if ((temp1 > 0 && temp2 > 0 && temp3 > 0 && temp4 > 0) || (temp1 < 0 && temp2 < 0 && temp3 < 0 && temp4 < 0))
			return 1;
		else
			return 0;
		break;
	}
	default:
		return 0;
		break;
	}
}

double Length(double _ax, double _ay, double _bx, double _by)
{
	return sqrt((_bx - _ax) * (_bx - _ax) + (_by - _ay) * (_by - _ay));
}

