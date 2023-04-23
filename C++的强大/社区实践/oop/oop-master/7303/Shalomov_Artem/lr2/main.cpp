#include <iostream>
#include <cmath>
#include "parallelogram.h"
#include "hexagon.h"
using namespace std;

int main()
{
    Shape *b = new Rectangle(0,0,2,3), *c = new Parallelogram(0,0,10,10,30),*s = new Hexagon(0,0,10);
    s->setColor({0,0xff,10});
	b->setRotation(45);
	*c << cout;   
 	cout << *c << *b << *s;
    delete s;
    delete c;
    delete b;
    return 0;
}
