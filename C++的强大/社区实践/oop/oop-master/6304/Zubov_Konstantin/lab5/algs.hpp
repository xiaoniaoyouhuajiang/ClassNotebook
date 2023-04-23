#ifndef algs_hpp
#define algs_hpp

#include "vector.hpp"
#include "shared.hpp"
#include "figure.hpp"
#include <ctime>
#include <algorithm>

using namespace last;

vector<shared_ptr<Shape>> create();
vector<shared_ptr<Shape>> create_p(vector<shared_ptr<Shape>>& mass, int k, int i);
bool search(const vector<shared_ptr<Shape>>& a, const vector<shared_ptr<Shape>>& b);
void print(const vector<shared_ptr<Shape>>& mass);
vector<shared_ptr<Shape>> intersection(const vector<shared_ptr<Shape> > &first, const vector<shared_ptr<Shape> > &second);
void length_sort(vector<shared_ptr<Shape> > &arr, int left, int right);
bool predikat1(Shape* first, Shape* second);
bool predikat2(Shape* first, Shape* second);



#endif //algs_hpp
