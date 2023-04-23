#pragma once;
#include <string>
#include "shared_ptr.h"
#include "vector.h"
#include "shape.h"
#include "arc.h"
#include "circle.h"
#include "ellipse.h"

using namespace std;

shape* generateRandomshape()
{
	int rnd = rand() % 3, val1 = rand() % 40 + 10, val2 = rand() % 90 + 10, val3 = rand() % 360;
	HDC hdc = NULL;

	switch (rnd)
	{
	case 0:
		return new circle(val1, paint_area_info(500, 500, 250, 250, hdc, rgb_color(255, 0, 0)));
	case 1:
		return new ellipse(val1, val2, paint_area_info(500, 500, 750, 250, hdc, rgb_color(0, 255, 0)));
	case 2:
		return new arc(val1, 0, val3, paint_area_info(500, 500, 1250, 250, hdc, rgb_color(0, 0, 255)));
	default:
		return NULL;
	}
}

stepik::vector< stepik::shared_ptr<shape> > generateshapes(unsigned int n)
{
	stepik::vector< stepik::shared_ptr<shape> > shapes(n);

	for (unsigned int i = 0; i < n; i++)
	{
		shapes[i] = stepik::shared_ptr<shape>(generateRandomshape());
	}

	return shapes;
}

bool type_predikat(shape* first, shape* second){
	return (first->shape_type() == second->shape_type());
}

int same_search(const stepik::vector<stepik::shared_ptr<shape> > &first, const stepik::vector<stepik::shared_ptr<shape> > &second){
	for (unsigned int i = 0; i < min(first.size(), second.size()); i++)
	if (type_predikat(first[i].get(), second[i].get())) return i;

	return INT_MIN;
}

void perimeter_sort(stepik::vector<stepik::shared_ptr<shape> > &arr, int left, int right){
	int i = left, j = right;
	stepik::shared_ptr<shape> tmp;
	stepik::shared_ptr<shape> pivot = arr[(left + right) / 2];

	/* partition */
	while (i <= j) {
		while (arr[i]->perimetr() < pivot->perimetr())
			i++;
		while (arr[j]->perimetr() > pivot->perimetr())
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};

	/* recursion */
	if (left < j){
		perimeter_sort(arr, left, j);
	}
	if (i < right){
		perimeter_sort(arr, i, right);
	}
}

stepik::vector< stepik::shared_ptr<shape> > intersection(const stepik::vector<stepik::shared_ptr<shape> > &first, const stepik::vector<stepik::shared_ptr<shape> > &second){
	stepik::vector< stepik::shared_ptr<shape> > result;

	//Создание множества пересечений
	for (unsigned int i = 0; i < min(first.size(), second.size()); i++)
		if (type_predikat(first[i].get(), second[i].get())) result.push_back(first[i]);

	//Сортировка (qucksort)
	perimeter_sort(result, 0, result.size()-1);

	return result;
}
