#include <iostream>
#include "Figures.hpp"

int main()
{
	Shape *ptr;
	Circle c{3};
	Pentagon p{};
	RegPentagon rP{};
	c.setPos({10,5,3});
	c.setColor({253,50,100});
	p.setPos({6,6,6});
	p.setColor({255,255,255});
	p.setDotsRadius({1,1,2,3,4});
	p.setDotsAngle({0,72,144,216,288});
	rP.setPos({6,6,6});
	rP.setColor({55,55,55});
	rP.setDotsRadius(1);
	ptr = &c;
	std::cout << *ptr << std::endl;
	ptr = &p;
	std::cout << *ptr << std::endl;
	std::cout << rP << std::endl;
	std::cout << "After scaling both pentagons in two times: " << std::endl;
	p.scale(2);
	std::cout << *ptr << std::endl;
	rP.scale(2);
	std::cout << rP << std::endl;
	return 0;
}
