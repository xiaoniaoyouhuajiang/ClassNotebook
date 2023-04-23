#ifndef COLOR_H
#define COLOR_H
#include <iostream>

class Color
{
public:
    Color();
    Color(Color&);
    Color(int red, int green, int blue);
    void setColor(int red, int green, int blue);
    void setRed(int);
    void setGreen(int);
    void setBlue(int);
    Color& operator=(const Color& right)
    {
        this->red = right.red;
        this->green = right.green;
        this->blue = right.blue;
        return *this;
    }
    friend std::ostream& operator<< (std::ostream &out, Color&);
    std::ostream& print(std::ostream&);
private:
    int red;
    int green;
    int blue;
};

#endif // COLOR_H
