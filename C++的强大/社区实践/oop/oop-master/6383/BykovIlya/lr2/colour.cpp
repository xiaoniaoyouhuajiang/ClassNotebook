#include "colour.h"

Colour::Colour() : red("000000"), green("000000"), blue("000000") {}
Colour::Colour(std::string red, std::string green, std::string blue) : red(red), green(green), blue(blue) {}
Colour::Colour(const Colour & other) : red(other.red), green(other.green), blue(other.blue) {}
Colour::Colour(Colour && other) { if (this != &other) swap(other); }
Colour & Colour::operator = (const Colour & other) { if (this != &other) Colour(other).swap(*this); return *this; }
Colour & Colour::operator = (Colour && other){ if (this != &other) swap(other); return *this; }
Colour::~Colour() {}
std::string & Colour::get_red()	{ return red; }
std::string & Colour::get_green() { return green; }
std::string & Colour::get_blue() { return blue; }
std::string Colour::get_red() const { return red; }
std::string Colour::get_green() const { return green; }
std::string Colour::get_blue() const { return blue; }
void Colour::set_red(const std::string & red) { this->red = red; }
void Colour::set_green(const std::string & green) { this->green = green; }
void Colour::set_blue(const std::string & blue) { this->blue = blue; }

void Colour::swap(Colour & a)
{
	std::swap(red, a.red);
	std::swap(green, a.green);
	std::swap(blue, a.blue);
}

std::ostream & operator << (std::ostream & out_, const Colour & c)
{
	c.out(out_);
}
void Colour::out(std::ostream & out_) const
{
	out_ << "[ RGB: " << red << green << blue << " ]"; 
}
