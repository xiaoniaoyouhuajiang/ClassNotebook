#pragma once

#include <ostream>
#include <string>
using namespace std;

class Dot { 
public:
	Dot(double x, double y) : x(x), y(y) {}
	Dot() : x(0), y(0) {}
	double x1() const;
	void set_x(double x);
	double y1() const;
	void set_y(double y);
	friend std::ostream& operator<<(std::ostream& s, const Dot& dot);
private:
	double x;
	double y;
};

class Shape {
public:
	virtual void move(double x_new, double y_new) = 0;  
	virtual void rotation(double angle) = 0; 
	virtual void scaling(double k) = 0; 
	virtual int perimetr() = 0;
	virtual void print () const = 0;
	Dot* dots1() const;
	void set_dots(Dot* dots);
	void set_color(std::string color_sh);
	string get_color() const;
	void set_perimetr(int per);
	int get_perimetr() const;
protected:
	static int currentId;
	int id;
	std::string color;
	int prm;
private:
	Dot* dots_ = nullptr;
};
