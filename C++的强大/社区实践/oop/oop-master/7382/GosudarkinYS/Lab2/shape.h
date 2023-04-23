#ifndef SHAPE_H
#define SHAPE_H

#pragma once

#include "math.h"

enum shape_t {NONE, CIRCLE, TRAPEZIUM, SECTOR};

// BASIC CLASS
class Shape
{
public:
    Shape()
        : mColor(255, 255, 255) {}

    RGB GetColor() const { return mColor; }
    void SetColor(const RGB& color) { mColor = color; }
    shape_t GetType() { return mType; }

    virtual void Replace(Coord vector) = 0;
    virtual void Rotate(double angle, const Coord& rotCenter) = 0;  // angle in rad
    virtual void Scale(double factor) = 0;
    virtual void PrintInfo() = 0;

    virtual ~Shape() {}

private:
    shape_t mType;
    RGB mColor;
};

// TRAPEZIUM CLASS
class Trapezium : public Shape
{
public:
    Trapezium() : Shape()
        , A(-1, 2)
        , B(1, 2)
        , C(2, -1)
        , D(-2, -1) 
	, mType(TRAPEZIUM) {}
    Trapezium(Coord a, Coord b, Coord c, Coord d) : Shape()
        , A(a)
        , B(b)
        , C(c)
        , D(d)
	, mType(TRAPEZIUM)
    {
        if( fabs(fabs(B.X-A.X)/fabs(C.X-D.X) - fabs(B.Y-A.Y)/fabs(C.Y-D.Y)) <= 0.000001
         || fabs(fabs(A.X-D.X)/fabs(B.X-C.X) - fabs(A.Y-D.Y)/fabs(B.Y-C.Y)) <= 0.000001 )
            mValid = true;
        else
            mValid = false;

    }

    void Replace(Coord vector) override;
    void Rotate(double angle, const Coord& rotCenter) override;
    void Scale(double factor) override;
    void PrintInfo() override;

protected:
    shape_t mType;
    Coord A, B;
    Coord C, D;
    bool mValid;
};

// CIRCLE CLASS
class Circle : public Shape
{
public:
    Circle() : Shape()
        , mCenter(0,0)
        , mRadius(1) 
        , mType(CIRCLE) {}
    Circle(Coord p, double rad) : Shape()
        , mCenter(p)
        , mRadius(rad) 
	, mType(CIRCLE) {}

    void Replace(Coord vector) override;
    void Rotate(double angle, const Coord& rotCenter) override;
    void Scale(double factor) override;
    void PrintInfo() override;

protected:
    shape_t mType;
    Coord mCenter;
    double mRadius;
};

// CIRCLE SECTOR CLASS
class Sector : public Circle
{
public:
    Sector(Coord a, Coord b, double angle) : Circle(a, Coord::Lenght(mVertex,mCenter))
	, mVertex(b)
        , mType(SECTOR)
        , mAngle(angle) {} 

    void Replace(Coord vector) override;
    void Rotate(double angle, const Coord& rotCenter) override;
    void Scale(double factor) override;
    void PrintInfo() override;

private:
    shape_t mType;
    Coord mVertex;
    double mAngle;
};

#endif // SHAPE_H
