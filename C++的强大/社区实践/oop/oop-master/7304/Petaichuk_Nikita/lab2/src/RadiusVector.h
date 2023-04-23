#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

using namespace std;

//Класс радиуса-вектора на плоскости
class RadiusVector
{
public:
    explicit RadiusVector(double x = 0, double y = 0);
    RadiusVector(const RadiusVector &other);
    RadiusVector& operator=(const RadiusVector& other);

    void setX(double x);
    void setY(double y);

    double getX() const;
    double getY() const;
    double length() const;

    RadiusVector& operator+=(const RadiusVector &other);
    RadiusVector& operator-=(const RadiusVector &other);
    RadiusVector& operator*=(double coeff);

    friend ostream& operator<<(ostream &os, const RadiusVector &vector);

private:
    double x_coord;
    double y_coord;
};

//Арифметические операции над радиус-векторами на плоскости
RadiusVector operator+(const RadiusVector &first, const RadiusVector &second);

RadiusVector operator-(const RadiusVector &first, const RadiusVector &second);

RadiusVector operator*(const RadiusVector &vector, double coeff);

RadiusVector operator*(double coeff, const RadiusVector &vector); 
