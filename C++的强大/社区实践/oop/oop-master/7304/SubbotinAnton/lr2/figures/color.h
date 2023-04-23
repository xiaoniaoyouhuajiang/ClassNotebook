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
    friend void operator<<(ostream&, const Color&);

public:
    Color(int r, int g, int b) : red(r), green(g), blue(b){}
    ~Color(){}

    Color& operator=(const Color&);
};

#endif // COLOR_H
