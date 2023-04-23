#pragma once
#include <string>
#include <iostream>

class Colour		// цвет фигуры
{
public:
	// конструктор с параметрами
	Colour();
	explicit Colour(std::string red, std::string green, std::string blue);
	// конструктор копирования
	Colour(const Colour & other);
	// конструктор перемещения
	Colour(Colour && other);
	// оператор присваивания
	Colour & operator = (const Colour & other);
	// оператор присваивания перемещения
	Colour & operator = (Colour && other);
	// деструктор
	~Colour();
	std::string & get_red();
	std::string & get_green();
	std::string & get_blue(); 
	std::string get_red() const;
	std::string get_green() const;
	std::string get_blue() const;
	void set_red(const std::string & red);
	void set_green(const std::string & green);
	void set_blue(const std::string & blue);
	void swap(Colour & a);
	friend std::ostream & operator << (std::ostream & out_, const Colour & c);
//	private:*/
	std::string red;
	std::string green;
	std::string blue;		// цвет задается в формате RGB
	void out(std::ostream & out_) const;
};