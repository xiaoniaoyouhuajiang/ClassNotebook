#ifndef SIXVERTICALS_STAR_H
#define SIXVERTICALS_STAR_H
#include <iostream>
#include <cmath>
#include "shape.h"
#include "fiveverticals_star.h"
using namespace std;

class Sixverticals_Star : public Fiveverticals_Star
{
public:
    Sixverticals_Star(double x, double y, double *x_arr, double *y_arr, int verticals = 6) : Fiveverticals_Star (x, y, x_arr, y_arr, 6) {}
    bool operator ==(Sixverticals_Star s1)
    {
        if(s1.Xcentre == Xcentre && s1.Ycentre == Ycentre)
        {
            for(int i = 0; i < 6; i++)
            { if(x_arr[i] != s1.x_arr[i] || y_arr[i] != s1.y_arr[i])
                    return false;

            }
            return true;
        }
        else
            return false;
    }
};
#endif // SIXVERTICALS_STAR_H
