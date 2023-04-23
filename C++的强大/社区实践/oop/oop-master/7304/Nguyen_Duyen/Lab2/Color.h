#pragma once
#include <iostream>
#include <string>
using namespace std;
class Color
{
public:
	unsigned char red, green, blue;
	Color();
	Color(unsigned char, unsigned char, unsigned char);
	Color& operator = (const Color&);
	friend ostream& operator<< (ostream&, const Color&);
	~Color();

};

