#include "shape.h"

// Class Circle methods
// _________________________________________________

void Circle::PrintInfo()
{
    RGB color = GetColor();
    std::cout << "Circle info: \n"
              << "\tRadius: ["<< mRadius <<"]\n"
              << "\tCenter: ["<< mCenter.X << ", " << mCenter.Y << "]\n"
              << "\tColor: " << color << "\n";
}

void Circle::Replace(Coord vector) { mCenter += vector; }

void Circle::Rotate(double angle, const Coord& rotCenter) { mCenter.Rotate(angle, rotCenter); }

void Circle::Scale(double factor) { mRadius *= factor; }

// Class Circle sector methods
// _________________________________________________

void Sector::PrintInfo()
{
    RGB color = GetColor();

    std::cout << "Circle sector info: \n"
              << "\tRadius: ["<< mRadius <<"]\n"
              << "\tCenter: ["<< mCenter.X << ", " << mCenter.Y << "]\n"
              << "\tVertex: ["<< mVertex.X << ", " << mVertex.Y << "]\n"
              << "\tAngle: ["<< (mAngle/PI)*180 << " (grad)\n "
              << "\tColor: " << color << "\n";
}

void Sector::Replace(Coord vector) { mCenter += vector; mVertex += vector; }

void Sector::Rotate(double angle, const Coord& rotCenter) { mCenter.Rotate(angle, rotCenter);
                                                            mVertex.Rotate(angle, rotCenter); }
void Sector::Scale(double factor) { mRadius *= factor; }

// Class Trapezium methods
// _________________________________________________

void Trapezium::PrintInfo()
{
    RGB color = GetColor();
    std::cout << "Trapezium info: \n"
              << "\tA point: ["<< A.X << ", " << A.Y << "]\n"
              << "\tB point: ["<< B.X << ", " << B.Y << "]\n"
              << "\tC point: ["<< C.X << ", " << C.Y << "]\n"
              << "\tD point: ["<< D.X << ", " << D.Y << "]\n"
              << "\tColor: " << color << "\n";
    if(!mValid)
        std::cout << "[WARNING] This Trapezium - invalid constructed!\n";
}

void Trapezium::Replace(Coord vector) { A += vector; B += vector; C += vector; D += vector; }

void Trapezium::Rotate(double angle, const Coord& rotCenter) { A.Rotate(angle, rotCenter); B.Rotate(angle, rotCenter);
                                                               C.Rotate(angle, rotCenter); D.Rotate(angle, rotCenter); }

void Trapezium::Scale(double factor)
{
    Coord ABvec(B.X-A.X, B.Y-A.Y); ABvec *= factor/2; B += ABvec;
    Coord ACvec(C.X-A.X, C.Y-A.Y); ACvec *= factor/2; C += ACvec;
    Coord ADvec(D.X-A.X, D.Y-A.Y); ADvec *= factor/2; D += ADvec;
}
