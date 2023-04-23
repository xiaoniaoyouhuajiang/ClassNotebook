#ifndef COLOR_H
#define COLOR_H

#include <iostream>

using namespace std;

class Color
{
private:
    int red;
    int green;
    int blue;

public:
    Color(int r, int g, int b) : red(r), green(g), blue(b){}
    ~Color(){}

    Color& operator = (const Color& element);
    friend void operator << (ostream& os, const Color& element);
};

#endif // COLOR_H
