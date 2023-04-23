#include "lab2.h"
//#include <functional>

size_t Shape::counter = 0;
std::default_random_engine rng(seed);


std::ostream& operator<< (std::ostream& os, Shape& p)
{
    p.print(os);
    return os;
}
void Shape::setColor(Color newcolor)
{
    color = newcolor;
}

const bool Shape::operator ==(const Shape &other) const
{
    if (this->id == other.id)
    {
        return true;
    }
    else return false;
}
Color Shape :: getColor() const
{
    return color;
}

void Ellipse::print(std::ostream& os)
{
    os << "[Ellipse] ";
    os << "Id: " << id;
    os << "; Center = " << center;
    os << "; a = " << a;
    os << "; b = " << b;
    os << "; fi = " << fi;
    os << "; Color = " << getColor();
    os << std::endl;
}
void Ellipse ::  move(int dx, int dy) {
    center.x+=dx;
    center.y+=dy;
}
void Ellipse :: rotate(int angle) {
    fi+=angle;
}
void Ellipse :: scale(int k)
{
    a=a*k;
    b=b*k;
}

void SectorOfEllipse::print(std::ostream& os)
{
    os << "[SectorOfEllipse] ";
    os << "Id: " << id;
    os << "; Center = " << center;
    os << "; a = " << a;
    os << "; b = " << b;
    os << "; fi = " << fi;
    os << "; f1 = " << f1;
    os << "; f2 = " << f2;
    os << "; Color = " << getColor();
    os << std::endl;
}

Point Ellipse::getCenter() const
{
    return center;
}
unsigned int Ellipse::getAAxis()
{
    return a;
}
unsigned int Ellipse::getBAxis()
{
    return b;
}
unsigned int Ellipse::getAngle()
{
    return fi;
}

void SectorOfEllipse::split (Ellipse* ellipse, SectorOfEllipse* s1, SectorOfEllipse* s2, SectorOfEllipse* s3) {

    if(ellipse)
    {
        Color ellipseColor = ellipse->getColor();
        Color colorS1(ellipseColor.red,0,0);
        Color colorS2(0,ellipseColor.green,0);
        Color colorS3(0,0,ellipseColor.blue);

        Point ellipseCenter = ellipse->getCenter();
        unsigned int a = ellipse->getAAxis();
        unsigned int b = ellipse->getBAxis();
        unsigned int angle = ellipse->getAngle();

        *s1 = SectorOfEllipse(colorS1, ellipseCenter, a, b, angle, 0, 120);
        *s2 = SectorOfEllipse(colorS2, ellipseCenter, a, b, angle, 120, 240);
        *s3 = SectorOfEllipse(colorS3, ellipseCenter, a, b, angle, 240, 360);
        delete ellipse;
    }
}

bool SectorOfEllipse::operator ==(const SectorOfEllipse &other) const
{
    return(a == other.a &&
           b == other.b &&
           getColor() == other.getColor() &&
           getCenter() == other.getCenter() &&
           fi == other.fi &&
           f1 == other.f1 &&
           f2 == other.f2);
}


bool checkParallelogram(Point a, Point b, Point c, Point d){
    if( ((b.x-a.x)==(c.x-d.x)) & ((c.y-b.y)==(d.y-a.y)) ) return true;
    else return false;
}
void Parallelogram::print(std::ostream& os)
{
    os << "[Parallelogram] ";
    os << "Id: " << id;
    os << "; Point a = " << a;
    os << "; Point b = " << b;
    os << "; Point c = " << c;
    os << "; Point d = " << d;
    os << "; Color = " << getColor();
    os << std::endl;
}
void Parallelogram ::  move(int dx, int dy) {
    a.x+=dx;
    a.y+=dy;
    b.x+=dx;
    b.y+=dy;
    c.x+=dx;
    c.y+=dy;
    d.x+=dx;
    d.y+=dy;
}
void Parallelogram :: rotate(int angle) {
    angle=angle;
}
void Parallelogram :: scale(int k)
{
    a.x*=k;
    a.y*=k;
    b.x*=k;
    b.y*=k;
    c.x*=k;
    c.y*=k;
    d.x*=k;
    d.y*=k;
}

Shape *Shape::createRandomShape()
{
    static std::function<Shape*()> childCreators[] = {Parallelogram::createRandomShape, SectorOfEllipse::createRandomShape, Ellipse::createRandomShape};
    static const size_t childN = sizeof(childCreators) / sizeof(childCreators[0]);
    int s = std::uniform_int_distribution<int>(0, childN-1)(rng);
    return childCreators[s]();
}

Ellipse *Ellipse::createRandomShape() {
    return new Ellipse(
            Color(
                    std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // r
                    std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // g
                    std::uniform_int_distribution<unsigned int>(0, magicborder)(rng) // b
            ),
            Point(
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng), // x
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng) // y
            ),
            std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // a
            std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // b
            std::uniform_int_distribution<unsigned int>(0, 360)(rng) // angle
    );
}

SectorOfEllipse *SectorOfEllipse::createRandomShape() {
    return new SectorOfEllipse(
            Color(
                    std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // r
                    std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // g
                    std::uniform_int_distribution<unsigned int>(0, magicborder)(rng) // b
            ),
            Point(
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng), // x
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng) // y
            ),
            std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // a
            std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // b
            std::uniform_int_distribution<unsigned int>(0, 360)(rng), // angle
            std::uniform_int_distribution<unsigned int>(0, 360)(rng), // startAngle
            std::uniform_int_distribution<unsigned int>(0, 360)(rng) // finishAngle
    );
}

Parallelogram *Parallelogram::createRandomShape() {
    return new Parallelogram(
            Color(
                    std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // r
                    std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // g
                    std::uniform_int_distribution<unsigned int>(0, magicborder)(rng) // b
            ),
            Point(
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng), // x
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng) // y
            ),
            Point(
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng), // x
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng) // y
            ),
            Point(
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng), // x
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng) // y
            ),
            Point(
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng), // x
                    std::uniform_int_distribution<int>(-magicborder, magicborder)(rng) // y
            )
    );
}

