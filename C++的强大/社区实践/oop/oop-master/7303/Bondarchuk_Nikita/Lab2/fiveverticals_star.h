#ifndef FIVEVERTICALS_STAR_H
#define FIVEVERTICALS_STAR_H
#include <iostream>
#include <cmath>
#include "shape.h"
using namespace std;
class Fiveverticals_Star : public Shape
{
protected:
    int verticals;
    double *x_arr;
    double *y_arr;

public:
    Fiveverticals_Star(double x, double y, double *x_arr, double *y_arr, int verticals = 5) : Shape(x, y)
    {

        this->verticals = verticals;
        this->x_arr = new double[verticals];
        this->y_arr = new double[verticals];
        if (x_arr && y_arr)
            for (int i = 0; i < verticals; i++)
            {
                this->x_arr[i] = x_arr[i];
                this->y_arr[i] = y_arr[i];
            }
    }
    ~Fiveverticals_Star()
    {
        delete[] x_arr;
        delete[] y_arr;
    }
    void MoveCentre(double x, double y)
    {
        double dx = x - Xcentre;
        double dy = y - Ycentre;
        Xcentre = x;
        Ycentre = y;
        for (int i = 0; i < verticals; i++)
        {
            x_arr[i] = x_arr[i] + dx;
            y_arr[i] = y_arr[i] + dy;
        }
    }
    double rotate(double radian)
    {
        for (int i = 0; i < verticals; i++)
        {
            double x_tmp = Xcentre + (Xcentre - x_arr[i]) * cos(radian) - (Ycentre - y_arr[i]) * sin(radian);
            double y_tmp = Ycentre + (Ycentre - y_arr[i]) * cos(radian) + (Xcentre - x_arr[i]) * sin(radian);
            x_arr[i] = x_tmp;
            y_arr[i] = y_tmp;
        }
        return radian;
    }
    bool scale(double i)
    {
        if (i == 0.0)
            return false;

        for (int p = 0; p < verticals; p++)
        {
            double x_tmp = Xcentre + (x_arr[p] - Xcentre) * i;
            double y_tmp = Ycentre + (y_arr[p] - Ycentre) * i;
            x_arr[p] = x_tmp;
            y_arr[p] = y_tmp;
        }

        return true;
    }

    bool operator ==(Fiveverticals_Star s1)
    {
        if(s1.Xcentre == Xcentre && s1.Ycentre == Ycentre)
        {
            for(int i = 0; i < 5; i++)
            { if(x_arr[i] != s1.x_arr[i] || y_arr[i] != s1.y_arr[i])
                    return false;

            }
            return true;
        }
        else
            return false;
    }

    friend ostream& operator<<(ostream& out, const Fiveverticals_Star &s)
    {
        string str;
        for (int i = 0; i < s.verticals; i++)
        {
            str = str + "(" + to_string(s.x_arr[i]) + ", " + to_string(s.y_arr[i]) + ") ";
        }
        return out << s.verticals << " verticals_star" << "   id:" << id << endl << "Center: " << s.Xcentre << ", " << s.Ycentre << endl
                   << str << endl;
    }

};
#endif // FIVEVERTICALS_STAR_H
