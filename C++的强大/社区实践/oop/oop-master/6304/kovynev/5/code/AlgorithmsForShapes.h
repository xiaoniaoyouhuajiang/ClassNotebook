#pragma once
#include "Shape.h"
#include "Vector.h"
#include "Shared_ptr.h"
#include <typeinfo>
using namespace stepik;

struct Region
{
	int start;
	int finish;
};

stepik::vector<shared_ptr<Shape>> generateFigures(int);

int compareFiguresByName(const void* , const void*);

bool isSimiliarRegion(Region, Region, const stepik::vector<shared_ptr<Shape>>&);

void sortFirstNElements(stepik::vector<shared_ptr<Shape>>&, int);

void printVector(const stepik::vector<shared_ptr<Shape>>&);

void print2Vectors(const stepik::vector<shared_ptr<Shape>>&, const stepik::vector<shared_ptr<Shape>>&);
