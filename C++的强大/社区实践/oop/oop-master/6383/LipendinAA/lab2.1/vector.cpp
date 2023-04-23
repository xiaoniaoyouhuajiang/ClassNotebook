#define _SCL_SECURE_NO_WARNINGS
#include <iostream>
#include "vector.h"

using namespace stepik;

int main() 
{
	vector<int> p(10);
	p.print();
	p.resize(5);
	p.print();
	system("pause");
	return 0;
}