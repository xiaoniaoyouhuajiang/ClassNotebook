#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>

#include <algorithm>


using namespace std;

class point
{
public:
    double x;
    double y;
    void print ()
    {
        cout << "(" << x << ", " << y << ") ";
    }
};

class shape
{
    virtual void printLocal () = 0;
    virtual void zoomLocal (double multiplicator) = 0;
    virtual void rotateLocal (double degree) = 0;
    virtual void moveLocal (double x, double y) = 0;

protected:
    point center;
    double rotateValue;
    vector<point> dotArray;
    unsigned int color;

public:
    virtual ~shape() {}

    shape (double _x, double _y)
    {
        center.x = _x;
        center.y = _y;
        rotateValue = 0;
        color = 0x000000;
    }

    void changePosition (double _x, double _y)
    {
        moveLocal(_x, _y);
        for (auto& current: dotArray)
        {
            current.x = current.x + center.x + _x;
            current.y = current.y + center.y + _y;
        }

        this->center.x = _x;
        this->center.y = _y;
    }

    void setRotateValue (double _degree)
    {
        rotateValue = rotateValue + _degree;
        rotateValue = std::fmod(rotateValue, 2*M_PI);

        if (rotateValue==0)
            return;


        rotateLocal(rotateValue);

        for (auto& current: dotArray)
        {
            double temp = current.x;
            current.x = center.x + (current.x - center.x)*cos(rotateValue) - (current.y - center.y)*sin(rotateValue);
            current.y = center.y + (temp - center.x)*sin(rotateValue) - (current.y - center.y)*cos(rotateValue);

        }
    }

    unsigned int getColor ()
    {
        return color;
    }

    void setColor (unsigned int colorValue)
    {
        color = colorValue;
    }

    void zoom(double multiplicator)
    {
        zoomLocal(multiplicator);
        for(auto& current : dotArray)
        {
            current.x = center.x + (current.x - center.x) * multiplicator;
            current.y = center.y + (current.y - center.y) * multiplicator;
        }
    }

    void printGeneral ()
    {
        cout << "Center coords: ";
        center.print();
        cout << "Angle: " << rotateValue << " rad" << endl;
        if (color <= 15)
            cout <<  "Color: 0x00000";
        if ((color > 15) && (color <= 255))
            cout <<  "Color: 0x0000";
        if ((color > 255) && (color <= 4095))
            cout <<  "Color: 0x000";
        if ((color > 4095) && (color <= 65535))
            cout <<  "Color: 0x00";
        if ((color > 65535) && (color <= 1048575))
            cout <<  "Color: 0x0";
        if ((color > 1048575) && (color <= 16777215))
            cout <<  "Color: 0x";
        if (color > 16777215)
            cout << "color out of range: ";
        cout << hex << color << endl;

        cout << "Main points:" << endl;
        for (auto & current: dotArray)
            current.print();
    }

    void printBoth ()
    {
        printGeneral();
        cout << endl;
        printLocal();
        cout << "------------------------" << endl;
    }

};

class eclipse: public shape
{
    void printLocal() override
    {
        cout << "Focuses: ";
        focus1.print();
        focus2.print();
        cout << endl;
    }

    void zoomLocal(double _multiplicator) override
    {
        focus1.x = center.x + (focus1.x - center.x) * _multiplicator;
        focus1.y = center.y + (focus1.y - center.y) * _multiplicator;

        focus2.x = center.x + (focus2.x - center.x) * _multiplicator;
        focus2.y = center.y + (focus2.y - center.y) * _multiplicator;
        focusDelay = focusDelay * _multiplicator;
    }

    void rotateLocal(double degree) override
    {
        if (degree==0)
            return;
        double temp = focus1.x;
        focus1.x = center.x + (focus1.x - center.x)*cos(degree) - (focus1.y - center.y)*sin(degree);
        focus1.y = center.y + (temp - center.x)*sin(degree) - (focus1.y - center.y)*cos(degree);

        temp = focus2.x;
        focus2.x = center.x + (focus2.x - center.x)*cos(degree) - (focus2.y - center.y)*sin(degree);
        focus2.y = center.y + (temp - center.x)*sin(degree) - (focus2.y - center.y)*cos(degree);

    }

    void moveLocal(double _x, double _y) override
    {
        focus1.x = focus1.x + center.x + _x;
        focus1.y = focus1.y + center.y + _y;

        focus2.x = focus2.x + center.x + _x;
        focus2.y = focus2.y + center.y + _y;
    }
    point focus1;
    point focus2;
    double focusDelay;

public:
    eclipse (double _x, double _y, double _fx, double _radius): shape(_x, _y), focusDelay(_radius)
    {
        rotateValue = 0;
        color = 0x000000;

        focus1.x = _fx + _x;
        focus1.y = _y;
        focus2.x = -(_fx) + _x;
        focus2.y = _y;

        point temp;

        //Left
        temp.x = _x + _fx - focusDelay;
        temp.y = _y;
        dotArray.push_back(temp);

        //Right
        temp.x = _x - _fx + focusDelay;
        temp.y = _y;
        dotArray.push_back(temp);

        //Upper
        temp.x = _x;
        double hardpoint = pow((focusDelay / 2)*(focusDelay / 2) - _fx*_fx, 1/2);
        temp.y = _y + hardpoint;
        dotArray.push_back(temp);

        //Lower
        temp.x = _x;
        temp.y = _y - hardpoint;
        dotArray.push_back(temp);
    }

};

class NOtrap: public shape
{
    void printLocal () override
    {
        cout << "Height: " << height << "; " << "Upper base: " << base2 << "; " << "Lower base: " << base1 << endl;
    }

    void zoomLocal(double multiplicator) override
    {
        height = height * multiplicator;
        base1 = base1 * multiplicator;
        base2 = base2 * multiplicator;
    }

    void rotateLocal (double degree) override {degree++; degree--;}
    void moveLocal(double x, double y) override {x++; x--; y++; y--;}

protected:
    double height;
    double base1; //Lower
    double base2; //Upper

public:
    NOtrap (double _x,double _y, double _height, double _base1, double _base2): shape(_x, _y), height(_height), base1(_base1), base2(_base2)
    {
        point temp;

        //Upper center
        temp.x = _x;
        temp.y = _y + _height/2;
        dotArray.push_back(temp);

        //Upper Left
        temp.x = _x - base2/2;
        temp.y = _y + _height/2;
        dotArray.push_back(temp);

        //Upper Right
        temp.x = _x + base2/2;
        temp.y = _y + _height/2;
        dotArray.push_back(temp);

        //Lower center
        temp.x = _x;
        temp.y = _y - _height/2;
        dotArray.push_back(temp);

        //Lower Left
        temp.x = _x - base1/2;
        temp.y = _y - _height/2;
        dotArray.push_back(temp);

        //Lower Right
        temp.x = _x + base1/2;
        temp.y = _y - _height/2;
        dotArray.push_back(temp);
    }

};

class trap: public NOtrap
{
    void printLocal() override
    {
        cout << "Height: " << height << "; " << "Upper base: " << base2 << "; " << "Lower base: " << base1 << "; " << "Offset: " << upperOffset << endl;
    }

    void zoomLocal(double multiplicator) override
    {
        height = height * multiplicator;
        base1 = base1 * multiplicator;
        base2 = base2 * multiplicator;
        upperOffset = upperOffset * multiplicator;
    }
    double upperOffset;

public:
    trap (double _x,double _y, double _height, double _base1, double _base2, double _offset): NOtrap(_x, _y, _height, _base1, _base2), upperOffset(_offset)
    {
        for (int i = 0; i<3; i++)
            dotArray[i].x = dotArray[i].x + _offset;
    }
};
