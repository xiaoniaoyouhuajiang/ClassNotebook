#include "shape.h"


unsigned int Shape::counter = 0;

// для 5 лобораторной работы
std::default_random_engine rng(seed);


bool AreSame(double a, double b)
{
    return std::fabs(a - b) < std::numeric_limits<double>::epsilon();
}

void Shape::setColor(Color color)
{
    current_color = color;
}
Color Shape::getColor() const
{
    return current_color;
}
double Shape::getAngle() const
{
    return current_angle;
}
void Shape::setAngle(double angle)
{
    current_angle = fmod(angle, 2 * M_PI);
    Point old_coordinates = center_coordinates;
    center_coordinates.x = old_coordinates.x * cos(current_angle) - old_coordinates.y * sin(current_angle);
    center_coordinates.y = old_coordinates.x * sin(current_angle) + old_coordinates.y * cos(current_angle);
}

Point Shape::getPosition() const
{
    return center_coordinates;
}
void Shape::setPosition(Point p)
{
    center_coordinates = p;
}
unsigned int Shape::getId() const
{
    return id;
}

bool Shape::operator ==(Shape &other)
{
    return this->getArea() == other.getArea();
}

bool Shape::operator > (Shape &other)
{
    if(this->getId() > other.getId())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Shape::operator < (Shape &other)
{
    if(this->getId() < other.getId())
    {
        return true;
    }
    else
    {
        return false;
    }
}
std::ostream &operator<< (std::ostream &os, Shape &f)
{
    f.print(os);
    return os;
}

Shape *Shape::createRandomShape()
{
    static std::function<Shape*()> childCreators[] = {Arc::createRandomShape, Round::createRandomShape, Ellipse::createRandomShape};
    static const size_t childN = sizeof(childCreators) / sizeof(childCreators[0]);
    int s = std::uniform_int_distribution<int>(0, childN-1)(rng);
    return childCreators[s]();
}

void Arc::scale(double scale)
{
    radius *= scale;
}
double Arc::getArea()
{
    return 0;
}
double Arc::getPerimetr() const
{
    double n = fabs(startAngle - finishAngle);
    double l = (M_PI * radius / 180) * n;
    return l;
}
void Arc::print(std::ostream &os)
{
    os<<"[Arc]"<<std::endl;
    os<<"Id: "<<id<<std::endl;
    os<<"Center( x , y ): ( "<<center_coordinates.x<<" , "<<center_coordinates.y<<" )"<<std::endl;
    os<<"Start Angle: "<<startAngle<<std::endl;
    os<<"Finish Angle: "<<finishAngle<<std::endl;
    os<<"Radius: "<<radius<<std::endl;
    os<<std::endl;
}

bool Arc::isPointOnBorder(const Point &p) const
{
    // x = cos(t) y = sin(t)
    Point r = p;
    r.rotate(-current_angle);
    double dx = r.x - center_coordinates.x;
    double dy = r.y - center_coordinates.y;
    bool borderFlag = fabs(pow(dx, 2) + pow(dy, 2) - pow(radius, 2)) < eps;
    double pointAngle = atan2(dy, dx);
    bool startAngleFlag = pointAngle >= startAngle;
    bool finishAngleFlag = pointAngle <= finishAngle;
    return (borderFlag && startAngleFlag && finishAngleFlag);
}

bool Arc::match(const Arc &other) const
{
    bool bCenter = (center_coordinates == other.center_coordinates);
    bool bRadius = AreSame(radius, other.radius);

    double s1 = fmod(startAngle + current_angle, 2*M_PI);
    double f1 = fmod(finishAngle + current_angle, 2*M_PI);
    double s2 = fmod(other.startAngle + other.current_angle, 2*M_PI);
    double f2 = fmod(other.finishAngle + other.current_angle, 2*M_PI);

    bool bAngle = !((s2 > f1) || (f2 < s1));

    return (bCenter && bRadius && bAngle);
}

int Arc::intersect(Shape &s2) const
{
    int intersectCount = 0;
    double x, y;
    bool inside = false;

    // проверка на совпадающую фигуру
    Arc* arc = dynamic_cast<Arc*>(&s2);
    if (arc)
    {
        if (match(*arc))
            // фигуры совпадают
            return -1;
    }

    // проверка на 0 радиус
    if (AreSame(radius, 0))
        return (s2.isPointOnBorder(center_coordinates) ? 1 : 0);

    // идем по фигуре с шагом epsStep и считаем, сколько точек попало в область s2
    for(double t = startAngle; t < finishAngle; t+=epsStep)
    {
        x = radius * cos(t) + center_coordinates.x;
        y = radius * sin(t) + center_coordinates.y;

        Point p(x, y);

        if(s2.isPointOnBorder(p))
        {
            if (!inside)
            {
                inside = true;
                intersectCount++;
            }
        }
        else
        {
            if (inside)
                inside = false;
        }
    }

    // если начальная и конечная точки совпадают, уменьшаем число точек, поскольку мы дважды посчитали одну и ту же точку
    double xstart = radius * cos(startAngle) + center_coordinates.x;
    double ystart = radius * sin(startAngle) + center_coordinates.y;
    double xfinish = radius * cos(finishAngle) + center_coordinates.x;
    double yfinish = radius * sin(finishAngle) + center_coordinates.y;

    if (AreSame(xstart, xfinish) && AreSame(ystart, yfinish) && s2.isPointOnBorder(Point(xstart, ystart)))
        intersectCount--;

    return intersectCount;
}

Arc *Arc::createRandomShape() {
    return new Arc(
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // x
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // y
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // start Angle
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // finish Angle
        std::uniform_real_distribution<double>(0, magicborder)(rng), // radius
        std::uniform_real_distribution<double>(-M_PI, M_PI)(rng), // angle
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // scale
        Color(
                std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // r
                std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // g
                std::uniform_int_distribution<unsigned int>(0, magicborder)(rng) // b
        )
    );
}

double Round::getArea()
{
    double s = M_PI * pow(radius, 2);
    return s;
}
double Round::getPerimetr() const
{
    double l = 2 * M_PI * radius;
    return l;
}
void Round::print(std::ostream &os)
{
    os<<"[Round]"<<std::endl;
    os<<"Id: "<<id<<std::endl;
    os<<"Center( x , y ): ( "<<center_coordinates.x<<" , "<<center_coordinates.y<<" )"<<std::endl;
    os<<"Radius: "<<radius<<std::endl;
    os<<"Perimetr: "<<getPerimetr()<<std::endl;
    os<<"Area: "<<getArea()<<std::endl;
    os<<std::endl;
}

bool Round::isPointOnBorder(const Point &p) const
{
    Point r = p;
    r.rotate(-current_angle);
    double dx = (r.x - center_coordinates.x);
    double dy = (r.y - center_coordinates.y);
    bool borderFlag = fabs(pow(dx, 2) + pow(dy, 2) - pow(radius, 2)) < eps;
    return borderFlag;
}

Round *Round::createRandomShape() {
    return new Round(
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // x
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // y
        std::uniform_real_distribution<double>(0, magicborder)(rng), // radius
        std::uniform_real_distribution<double>(-M_PI, M_PI)(rng), // angle
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // scale
        Color(
                std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // r
                std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // g
                std::uniform_int_distribution<unsigned int>(0, magicborder)(rng) // b
        )
    );
}

double Ellipse::getPerimetr() const
{
    return 4 * ( M_PI * aHalfAxis * bHalfAxis + std::fabs( bHalfAxis - aHalfAxis ) ) / ( aHalfAxis + bHalfAxis );
}
double Ellipse::getArea()
{
    return M_PI * aHalfAxis * bHalfAxis;
}

int Ellipse::intersect(Shape &s2) const
{
    int intersectCount = 0;
    double x, y;
    bool inside = false;

    // проверка на совпадающую фигуру
    Ellipse* e = dynamic_cast<Ellipse*>(&s2);
    if (e)
    {
        if (match(*e))
            // фигуры совпадают
            return -1;
    }

    for(double t = -M_PI; t < M_PI; t+=epsStep)
    {
        x = aHalfAxis * cos(t) + center_coordinates.x;
        y = bHalfAxis * sin(t) + center_coordinates.y;

        Point p(x, y);

        if(s2.isPointOnBorder(p))
        {
            if (!inside)
            {
                inside = true;
                intersectCount++;
            }
        }
        else
        {
            if (inside)
                inside = false;
        }
    }

    // если начальная точка является точкой пересечения, мы посчитали ее два раза
    x = aHalfAxis * cos(-M_PI) + center_coordinates.x;
    y = bHalfAxis * sin(-M_PI) + center_coordinates.y;
    if (s2.isPointOnBorder(Point(x, y)))
        intersectCount--;


    return intersectCount;
}
void Ellipse::scale(double scale)
{
    aHalfAxis *= scale;
    bHalfAxis *= scale;
}
void Ellipse::print(std::ostream &os)
{
    os<<"[Ellipse]"<<std::endl;
    os<<"Id: "<<id<<std::endl;
    os<<"Center( x , y ): ( "<<center_coordinates.x<<" , "<<center_coordinates.y<<" )"<<std::endl;
    os<<"Maximum Half Axis: "<<bHalfAxis<<std::endl;
    os<<"Minimum Half Axis: "<<aHalfAxis<<std::endl;
    os<<"Perimetr: "<<getPerimetr()<<std::endl;
    os<<"Area: "<<getArea()<<std::endl;
    os<<std::endl;
}

bool Ellipse::isPointOnBorder(const Point &p) const
{
    Point r = p;
    r.rotate(current_angle);
    double dx = (r.x - center_coordinates.x) / aHalfAxis;
    double dy = (r.y - center_coordinates.y) / bHalfAxis;
    bool borderFlag = fabs(pow(dx, 2) + pow(dy, 2) - 1) < 1.5*eps;
    return borderFlag;
}

bool Ellipse::match(const Ellipse &e) const
{
    bool bCenter = (center_coordinates == e.center_coordinates);
    bool a_ = AreSame(aHalfAxis, e.aHalfAxis);
    bool b_ = AreSame(bHalfAxis, e.bHalfAxis);

    return (bCenter && a_ && b_);
}

Ellipse *Ellipse::createRandomShape() {
    return new Ellipse(
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // x
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // y
        std::uniform_real_distribution<double>(0, magicborder)(rng), // aAxis
        std::uniform_real_distribution<double>(0, magicborder)(rng), // bAxis
        std::uniform_real_distribution<double>(0, 2*M_PI)(rng), // angle
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // scale
        Color(
                std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // r
                std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // g
                std::uniform_int_distribution<unsigned int>(0, magicborder)(rng) // b
        )
    );
}

