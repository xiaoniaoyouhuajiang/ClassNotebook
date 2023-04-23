#pragma once

#include "Shape.h"
#include "vector.h"
#include "shared_ptr.h"
using namespace stepik;

void output (const stepik::vector<shared_ptr<Shape>>& arr);

int compare(const shared_ptr<Shape> &a, const shared_ptr<Shape> &b);

void sequencing (vector<shared_ptr<Shape>>& arr, int n);

bool sum_prm (stepik::vector<shared_ptr<Shape>>& arr, int a1, int b1, int a2, int b2);
