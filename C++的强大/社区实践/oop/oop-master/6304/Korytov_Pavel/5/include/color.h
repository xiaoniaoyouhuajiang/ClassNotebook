#ifndef COLOR_H
#define COLOR_H
#include <iostream>

using  namespace std;
class Color{
public:
	Color() : r(255), g(255), b(255) {}
	~Color() = default;
	Color(int rs, int gs, int bs);
    Color (const Color& c) : Color(c.r, c.g, c.b) {}
    Color& operator= (const Color & c);
    void Rand();
    void Enter();
	friend ostream& operator<<(ostream& os, Color& col);
    void SetR(int rs) { r = rs; }
    void SetG(int gs) { g = gs; }
    void SetB(int bs) { b = bs; }
    int R() const {return r; }
    int G() const {return g; }
    int B() const {return b; }

private:
    int r, g, b;
};


bool operator==(const Color & a, const Color & b);
const Color Black(255, 255, 255);
const Color White(0, 0, 0);
const Color Red(255, 0, 0);
const Color Green(0, 255, 0);
const Color Blue(0, 0, 255);

#endif