#pragma once
#ifndef additional_func_h
#define additional_func_h

#define _USE_MATH_DEFINES

#include "my_shared_ptr.h"
#include "my_vector.h"
#include "shape.h"

using namespace stepik;

struct neighbours
{
	size_t first;
	size_t second;
};

struct dual_un
{
	size_t num;
	double val;
};
bool ident_vect(vector<size_t> a, vector<neighbours> b);
bool ident_vect(vector<size_t> a, vector<dual_un> b);
vector<shared_ptr<Shape>> test_create(size_t amount);
vector<shared_ptr<Shape>> create_arr(size_t amount);
vector<neighbours> neigh_search(vector<shared_ptr<Shape>> &arr);
vector<dual_un> dual_diap_union(size_t fst_dp_beg, size_t fst_dp_end, size_t sec_dp_beg, size_t sec_dp_end, vector<shared_ptr<Shape>> &arr);

#endif // !additional_func_hpp

