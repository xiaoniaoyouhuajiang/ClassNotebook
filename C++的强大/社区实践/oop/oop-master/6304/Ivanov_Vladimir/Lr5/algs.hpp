#ifndef algs_hpp
#define algs_hpp

#include "vector.hpp"
#include "shared.hpp"
#include "figure.hpp"

using namespace last;

vector<shared_ptr<Shape>> create();
bool allsquareless(const vector<shared_ptr<Shape>>& mass, int k);
void copyBad(vector<shared_ptr<Shape>>& mass, int k);
void print(const vector<shared_ptr<Shape>>& mass);

#endif //algs_hpp