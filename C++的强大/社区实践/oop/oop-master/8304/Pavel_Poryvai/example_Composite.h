#pragma once
#include<vector>
#include"cell_ancestors.h"
using namespace std;
//демонстрация Компоновщика
class CompositeUnit :public unit {
private:
	std::vector<unit*> c;
public:

	int get_total_unit() {
		return c.size();
	}
	void addUnit(unit* p) {
		c.push_back(p);
	}
	CompositeUnit() {};
	~CompositeUnit() {
		for (int i = 0; i < c.size(); ++i)
			delete c[i];
	}

};

CompositeUnit* createLegion()
{

	CompositeUnit* legion = new CompositeUnit;
	for (int i = 0; i < 100; i++)
		legion->addUnit(new unit);

	return legion;
}

