#include "stdafx.h"
#define _USE_MATH_DEFINES
#include "additional_func.h"
#include <time.h>

bool CompReal(double a, double b)
{
	return a < b;
}

bool ident_vect(vector<size_t> a, vector<neighbours> b)
{
	size_t j = 0;
	for (size_t i = 0; i < a.size(); i+=2, j++)
	{
		if (a[i] != b[j].first)
			return false;
		if (a[i + 1] != b[j].second)
			return false;
	}
	return true;
}

bool ident_vect(vector<size_t> a, vector<dual_un> b)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		if (a[i] != b[i].num)
			return false;
	}
	return true;
}

vector<shared_ptr<Shape>> test_create(size_t amount)
{
	vector<shared_ptr<Shape>> arr(amount);
	for (size_t i = 0; i < amount; i++)
	{
		if (i % 2 == 0)
			arr[i] = shared_ptr<Shape>(new Ellipse(i+2, 0, i + 5, i + 7, i + 15));
		else
			arr[i] = shared_ptr<Shape>(new Trap(i + 1, 1 + i, i + 10, i + 10, i + 10, i + 10));
	}
	return arr;
}

vector<shared_ptr<Shape>> create_arr(size_t amount)
{
	vector<shared_ptr<Shape>> arr(amount);
	srand(time(nullptr));
	for (size_t i = 0; i < amount; i++)
	{
		if (rand() % 2 == 0)
			arr[i] = shared_ptr<Shape>(new Ellipse(rand() % 10, rand() % 10, rand() % 3 + 1, rand() % 10, 15));
		else
			arr[i] = shared_ptr<Shape>(new Trap(rand() % 10, rand() % 10, rand() % 8, rand() % 3, rand() % 8, rand() % 5));
	}
	return arr;
}

vector<neighbours> neigh_search(vector<shared_ptr<Shape>> &arr)
{
	vector<neighbours> result;
	neighbours temp;
	for (size_t i = 0; i < arr.size() - 1; i++)
	{
		if ((*arr[i]).getCenx() == (*arr[i + 1]).getCenx())
		{
			temp.first = i;
			temp.second = i + 1;
			result.push_back(temp);
		}
	}
	return result;
}

vector<dual_un> dual_diap_union(size_t fst_dp_beg, size_t fst_dp_end, size_t sec_dp_beg, size_t sec_dp_end, vector<shared_ptr<Shape>> &arr)
{
	vector <dual_un> result;
	dual_un temp;
	if (!(fst_dp_beg < 0 || fst_dp_beg > arr.size() || fst_dp_end < 0 || fst_dp_end > arr.size() || fst_dp_end - fst_dp_beg <= 0))
	{
		for (size_t i = fst_dp_beg; i < fst_dp_end; i++)
		{
			temp.num = i;
			temp.val = (*arr[i]).getCenx() * (*arr[i]).getCeny();
			result.push_back(temp);
		}
	}
	if (!(sec_dp_beg < 0 || sec_dp_beg > arr.size() || sec_dp_end < 0 || sec_dp_end > arr.size() || sec_dp_end - sec_dp_beg <= 0))
	{
		for (size_t i = sec_dp_beg; i < sec_dp_end; i++)
		{
			temp.num = i;
			temp.val = (*arr[i]).getCenx() * (*arr[i]).getCeny();
			result.push_back(temp);
		}
		std::sort(result.begin(), result.end(), [](const dual_un &a, const dual_un &b)
		{
			return CompReal(a.val, b.val);
		});
	}
	return result;
}