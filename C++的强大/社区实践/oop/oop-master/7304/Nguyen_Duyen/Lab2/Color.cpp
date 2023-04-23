#include "Color.h"

Color::Color(){}

Color::Color(unsigned char r, unsigned char g, unsigned char b) {
	this->red = r % 256;
	this->green = g % 256;
	this->blue = b % 256;
}

Color & Color::operator=(const Color &c){
	red = c.red;
	green = c.green;
	blue = c.blue;
	return *this;
}

ostream& operator<< (ostream& stream, const Color& color) {
	return stream << "Color(" << static_cast<unsigned>(color.red) << "," << static_cast<unsigned>(color.green) << "," << static_cast<unsigned>(color.blue) << ")";
}
Color::~Color(){}
