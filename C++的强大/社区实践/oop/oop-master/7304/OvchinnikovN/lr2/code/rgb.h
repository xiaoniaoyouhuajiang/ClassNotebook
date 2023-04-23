#ifndef RGB_H
#define RGB_H

class rgb
{
protected:
    int red;
    int green;
    int blue;

public:
    rgb(){}
    rgb(int red, int green, int blue) : red(red), green(green), blue(blue){}
    void setColor(int red, int green, int blue);
    int getRed() const;
    int getGreen() const;
    int getBlue() const;
};

#endif // RGB_H
