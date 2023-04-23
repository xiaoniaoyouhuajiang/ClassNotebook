#include "lab2.h"

int Shape::counter = 0;

// для 5 лобораторной работы
std::default_random_engine rng(seed);

#define PI 3.14159265

void RotateShape(CS * _points, CS _center, double _angle, int _size)
{
    double tempX;
    double tempY;
    for (int i = 0; i < _size; i++)
    {
        tempX = (_points[i].x - _center.x) * cos(_angle * PI / 180) - (_points[i].y - _center.y) * sin(_angle * PI / 180) + _center.x;
        tempY = (_points[i].x - _center.x) * sin(_angle * PI / 180) + (_points[i].y - _center.y) * cos(_angle * PI / 180) + _center.y;
        _points[i].x = tempX;
        _points[i].y = tempY;
    }
}

void MoveShape(CS *_points, CS _center, double _x, double _y, int _size)
{
    for (int i = 0; i < _size; i++)
    {
        _points[i].x += _x - _center.x;
        _points[i].y += _y - _center.y;
    }
}

void NewTriangleCenter(CS * _points, CS & _center)
{
    _center.x = (_points[0].x + _points[1].x + _points[2].x) / 3;
    _center.y = (_points[0].y + _points[1].y + _points[2].y) / 3;
}

void ScaleShape(CS * _points, CS _center, double _scale, int _size)
{
    try {
        if (_scale == 0)
            throw "Scale is 0";
        for (int i = 0; i < _size; i++) {
            _points[i].x = _center.x + (_points[i].x - _center.x) * fabs(_scale);
            _points[i].y = _center.y + (_points[i].y - _center.y) * fabs(_scale);
        }
    }

    catch (char *str) {
            cout << str << endl;
        }
}

int ShapeTest(CS *_points, const CS *_shapePoints, int size, int i)
{
    int sum = 0;
    switch (size)
    {
    case 3:
    {
        double temp1 = (_shapePoints[0].x - _points[i].x) * (_shapePoints[1].y - _shapePoints[0].y) - (_shapePoints[1].x - _shapePoints[0].x) * (_shapePoints[0].y - _points[i].y);
        double temp2 = (_shapePoints[1].x - _points[i].x) * (_shapePoints[2].y - _shapePoints[1].y) - (_shapePoints[2].x - _shapePoints[1].x) * (_shapePoints[1].y - _points[i].y);
        double temp3 = (_shapePoints[2].x - _points[i].x) * (_shapePoints[0].y - _shapePoints[2].y) - (_shapePoints[0].x - _shapePoints[2].x) * (_shapePoints[2].y - _points[i].y);
        if ((temp1 > 0 && temp2 > 0 && temp3 > 0) || (temp1 < 0 && temp2 < 0 && temp3 < 0))
            return 1;
        else
            return 0;
    }
    break;
    case 4:
    {
        double temp1 = (_shapePoints[0].x - _points[i].x) * (_shapePoints[1].y - _shapePoints[0].y) - (_shapePoints[1].x - _shapePoints[0].x) * (_shapePoints[0].y - _points[i].y);
        double temp2 = (_shapePoints[1].x - _points[i].x) * (_shapePoints[2].y - _shapePoints[1].y) - (_shapePoints[2].x - _shapePoints[1].x) * (_shapePoints[1].y - _points[i].y);
        double temp3 = (_shapePoints[2].x - _points[i].x) * (_shapePoints[3].y - _shapePoints[2].y) - (_shapePoints[3].x - _shapePoints[2].x) * (_shapePoints[2].y - _points[i].y);
        double temp4 = (_shapePoints[3].x - _points[i].x) * (_shapePoints[0].y - _shapePoints[3].y) - (_shapePoints[0].x - _shapePoints[3].x) * (_shapePoints[3].y - _points[i].y);
        if ((temp1 > 0 && temp2 > 0 && temp3 > 0 && temp4 > 0) || (temp1 < 0 && temp2 < 0 && temp3 < 0 && temp4 < 0))
            return 1;
        else
            return 0;
        break;
    }
    default:
        return 0;
        break;
    }
}

double Length(double _ax, double _ay, double _bx, double _by)
{
    return sqrt((_bx - _ax) * (_bx - _ax) + (_by - _ay) * (_by - _ay));
}


Shape::Shape(Color _color)
{
    this->currentColor = _color;
    id = counter++;
}


bool Shape::IsInsideOfAnother(const Shape & other)
{
    return false;
}

Quadrate::Quadrate(double _ax, double _ay, double _bx, double _by, double _cx, double _cy, double _dx, double _dy, Color _color):Shape(_color)
{
    IsItQuadrate(_ax, _ay, _bx, _by, _cx, _cy, _dx, _dy);
}

void Quadrate::IsItQuadrate(double _ax, double _ay, double _bx, double _by, double _cx, double _cy, double _dx, double _dy)
{
    this->points[0].x = _ax;
    this->points[0].y = _ay;
    this->points[1].x = _bx;
    this->points[1].y = _by;
    this->points[2].x = _cx;
    this->points[2].y = _cy;
    this->points[3].x = _dx;
    this->points[3].y = _dy;
    NewSizes();
    try {
        if (!((this->sides[0] == this->sides[1]) && (this->sides[1] == this->sides[2]) && (this->sides[2] == this->sides[3]) && (this->sides[3] == this->sides[0]) && (this->diagonals[0] == this->diagonals[1]) && (this->angles[0] == this->angles[1]) && (this->angles[1] == this->angles[2]) && (this->angles[2] == this->angles[3]) && (this->angles[0] == this->angles[3])))
            throw "It isn't quadrate";
        this->points[0].x = _ax;
        this->points[0].y = _ay;
        this->points[1].x = _bx;
        this->points[1].y = _by;
        this->points[2].x = _cx;
        this->points[2].y = _cy;
        this->points[3].x = _dx;
        this->points[3].y = _dy;
        NewQuadrateCenter();

    }
    catch (char *str) {
        cout << str << endl << "Write a new coordinate" << endl << "X1 | Y1 | X2 | Y2 | X3 | Y3 | X4 | Y4" << endl;
        cin >> _ax >> _ay >> _bx >> _by >> _cx >> _cy >> _dx >> _dy;
        IsItQuadrate(_ax, _ay, _bx, _by, _cx, _cy, _dx, _dy);
    }
}

void Quadrate::NewQuadrateCenter()
{
    center.x = (points[0].x + points[2].x) / 2;
    center.y = (points[0].y + points[2].y) / 2;
}

void Quadrate::NewSizes()
{
    for (int i = 0; i < 3; i++)
    {
        this->sides[i] = Length(this->points[i].x, this->points[i].y, this->points[i + 1].x, this->points[i + 1].y);
    }
    this->sides[3] = Length(this->points[3].x, this->points[3].y, this->points[0].x, this->points[0].y);
    this->diagonals[0] = Length(this->points[0].x, this->points[0].y, this->points[2].x, this->points[2].y);
    this->diagonals[1] = Length(this->points[1].x, this->points[1].y, this->points[3].x, this->points[3].y);
    this->angles[0] = Angle(this->points[0], this->points[3], this->points[1]);
    this->angles[1] = Angle(this->points[1], this->points[0], this->points[2]);
    this->angles[2] = Angle(this->points[2], this->points[1], this->points[3]);
    this->angles[3] = Angle(this->points[3], this->points[2], this->points[0]);
}

void Quadrate::Move(double _x, double _y)
{
    MoveShape(this->points, this->center, _x, _y, 4);
    NewQuadrateCenter();
    NewSizes();
}

void Quadrate::Rotate(double _angle)
{
    RotateShape(this->points, this->center, _angle, 4);
    NewSizes();
}

void Quadrate::Scale(double _scale)
{
    ScaleShape(this->points, this->center, _scale, 4);
    NewSizes();
}

ostream & Quadrate::put(ostream & out) const
{
    return out << "This is quadrate" << endl << "Point's coordinates: " << endl << "x1 | " << this->points[0].x << " y1 | " << this->points[0].y << endl << "x2 | " << this->points[1].x << " y2 | " << this->points[1].y << endl << "x3 | " << this->points[2].x << " y3 | " << this->points[2].y << endl << "x4 | " << this->points[3].x << " y4 | " << this->points[3].y << endl <<"Center: " << endl << this->center.x <<" " << this->center.y << endl << "Color: " << endl << "Red: " << (int)currentColor.r << " | Green: " << (int)currentColor.g << " | Blue: " << (int)currentColor.b << endl << "ID: " << this->id << endl << "---------------" << endl;
}

bool Quadrate::IsInsideOfAnother(const Shape &other)
{
    int sum = 0;
    for (int i = 0; i < 4; i++) {
        if (const IsoscelesTriangle* xyz = dynamic_cast<const IsoscelesTriangle*>(&other))
        {
            sum += ShapeTest(this->points, xyz->points, 3, i);
        }
        else if (const RightTriangle* xyz = dynamic_cast<const RightTriangle*>(&other))
        {
            sum += ShapeTest(this->points, xyz->points, 3, i);
        }
        else if (const Quadrate* xyz = dynamic_cast<const Quadrate*>(&other)) {
            sum += ShapeTest(this->points, xyz->points, 4, i);
        }
    }
    if (sum == 4)
        return true;
    else
        return false;
}

double Quadrate::Angle(CS p1, CS p2, CS p3)
{
    return acos(((p2.x - p1.x) * (p3.x - p1.x) + (p2.y - p1.y) * (p3.y - p1.y)) / (sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2))*sqrt(pow((p3.x - p1.x), 2) + pow((p3.y - p1.y), 2))));
}

Quadrate::~Quadrate()
{
}

IsoscelesTriangle::IsoscelesTriangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy, Color _color) : Shape(_color)
{
    this->AB = Length(_ax, _ay, _bx, _by);
    this->BC = Length(_bx, _by, _cx, _cy);
    this->AC = Length(_ax, _ay, _cx, _cy);
    IsItTriangle(_ax, _ay, _bx, _by, _cx, _cy);
}

IsoscelesTriangle::~IsoscelesTriangle()
{
}

void IsoscelesTriangle::IsItIsoscelesTriangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy)
{
    try {
        if (!(this->AB == this->BC || this->AB == this->AC || this->BC == this->AC)) {
            throw "It isn't isosceles triangle";
        }
        this->points[0].x = _ax;
        this->points[0].y = _ay;
        this->points[1].x = _bx;
        this->points[1].y = _by;
        this->points[2].x = _cx;
        this->points[2].y = _cy;
        NewTriangleCenter(this->points, this->center);
    }
    catch (char *str)
    {
        cout << "It isn't isosceles triangle" << endl << "enter new coordinates using the spacebar and press Enter" << endl << "X1 | Y1 | X2 | Y2 | X3 | Y3" << endl;
        cin >> _ax >> _ay >> _bx >> _by >> _cx >> _cy;
        this->AB = Length(_ax, _ay, _bx, _by);
        this->BC = Length(_bx, _by, _cx, _cy);
        this->AC = Length(_ax, _ay, _cx, _cy);
        IsItIsoscelesTriangle(_ax, _ay, _bx, _by, _cx, _cy);
    }
}

void IsoscelesTriangle::IsItTriangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy)
{
    try {
        if (!(this->AB + this->BC > this->AC || this->AC + this->BC > this->AB || this->AB + this->AC > this->BC))
        {
            throw "It isn't triangle";
        }
        IsItIsoscelesTriangle(_ax, _ay, _bx, _by, _cx, _cy);
    }
    catch (char *str) {
        cout << str << endl << "enter new coordinates using the spacebar and press Enter" << endl << "X1 | Y1 | X2 | Y2 | X3 | Y3" << endl;
        cin >> _ax >> _ay >> _bx >> _by >> _cx >> _cy;
        this->AB = Length(_ax, _ay, _bx, _by);
        this->BC = Length(_bx, _by, _cx, _cy);
        this->AC = Length(_ax, _ay, _cx, _cy);
        IsItTriangle(_ax, _ay, _bx, _by, _cx, _cy);
    }
}


ostream & IsoscelesTriangle::put(ostream & out) const
{
    return out << "This is isosceles triangle" << endl << "Point's coordinates: " << endl << "x1 | " << this->points[0].x << " y1 | " << this->points[0].y << endl << "x2 | " << this->points[1].x << " y2 | " << this->points[1].y << endl << "x3 | " << this->points[2].x << " y3 | " << this->points[2].y << endl << "Center:"<< endl << this->center.x << " " << this->center.y << endl << "Color: " << endl << "Red: " << (int)currentColor.r << " | Green: "<< (int)currentColor.g << " | Blue: "<<(int)currentColor.b << endl << "ID: " << this->id <<  endl << "---------------" << endl;
}

bool IsoscelesTriangle::IsInsideOfAnother(const Shape & other)
{
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        if (const IsoscelesTriangle* xyz = dynamic_cast<const IsoscelesTriangle*>(&other))
        {
            sum += ShapeTest(this->points, xyz->points, 3, i);
        }
        else if (const RightTriangle* xyz = dynamic_cast<const RightTriangle*>(&other))
        {
            sum += ShapeTest(this->points, xyz->points, 3, i);
        }
        else if (const Quadrate* xyz = dynamic_cast<const Quadrate*>(&other)) {
            sum += ShapeTest(this->points, xyz->points, 4, i);
        }
    }
    if (sum == 3)
        return true;
    else
        return false;
}


void IsoscelesTriangle::Move(double _x, double _y)
{
    MoveShape(this->points, this->center, _x, _y, 3);
    NewTriangleCenter(this->points, this->center);
}


void IsoscelesTriangle::Rotate(double _angle)
{
    RotateShape(this->points, this->center, _angle, 3);
}

void IsoscelesTriangle::Scale(double _scale)
{
    ScaleShape(this->points, this->center, _scale, 3);
}

RightTriangle::RightTriangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy, Color _color):Shape(_color)
{

    this->AB = Length(_ax, _ay, _bx, _by);
    this->BC = Length(_bx, _by, _cx, _cy);
    this->AC = Length(_ax, _ay, _cx, _cy);
    IsItTriangle(_ax, _ay, _bx, _by, _cx, _cy);
}

RightTriangle::~RightTriangle()
{
}

void RightTriangle::IsItRightTriangle (double _ax, double _ay, double _bx, double _by, double _cx, double _cy)
{
    double alpha = ((acos ((pow(this->AB, 2) + pow(this->BC, 2) - pow(this->AC, 2)) / (2 * this->AB * this->BC)))*180)/PI;
    double beta = ((acos((pow(this->BC, 2) + pow(this->AC, 2) - pow(this->AB, 2)) / (2 * this->BC * this->AC)))*180)/PI;
    double gamma =(( acos((pow(this->AB, 2) + pow(this->AC, 2) - pow(this->BC, 2)) / (2 * this->AB * this->AC)))*180)/PI;
    try {
        if (!(fabs(alpha - 90) < 1e-5 || fabs(beta - 90) < 1e-5 || fabs(gamma - 90) < 1e-5)) {
            throw "It isn't right triangle";
        }
        this->points[0].x = _ax;
        this->points[0].y = _ay;
        this->points[1].x = _bx;
        this->points[1].y = _by;
        this->points[2].x = _cx;
        this->points[2].y = _cy;
        NewTriangleCenter(this->points, this->center);
    }
    catch(char *str)
    {
        cout << str << endl << "enter new coordinates using the spacebar and press Enter" << endl << "X1 | Y1 | X2 | Y2 | X3 | Y3" << endl;
        cin >> _ax >> _ay >> _bx >> _by >> _cx >> _cy;
        this->AB = Length(_ax, _ay, _bx, _by);
        this->BC = Length(_bx, _by, _cx, _cy);
        this->AC = Length(_ax, _ay, _cx, _cy);
        IsItRightTriangle(_ax, _ay, _bx, _by, _cx, _cy);
    }
}

void RightTriangle::IsItTriangle(double _ax, double _ay, double _bx, double _by, double _cx, double _cy)
{
    try {
        if (!(this->AB + this->BC > this->AC || this->AC + this->BC > this->AB || this->AB + this->AC > this->BC))
        {
            throw "It isn't triangle";
        }
        IsItRightTriangle(_ax, _ay, _bx, _by, _cx, _cy);
    }
    catch (char *str) {
        cout << str << endl << "enter new coordinates using the spacebar and press Enter" << endl << "X1 | Y1 | X2 | Y2 | X3 | Y3" << endl;
        cin >> _ax >> _ay >> _bx >> _by >> _cx >> _cy;
        this->AB = Length(_ax, _ay, _bx, _by);
        this->BC = Length(_bx, _by, _cx, _cy);
        this->AC = Length(_ax, _ay, _cx, _cy);
        IsItTriangle(_ax, _ay, _bx, _by, _cx, _cy);
    }
}

ostream & RightTriangle::put(ostream & out) const
{
    return out << "This is isosceles triangle" << endl << "Point's coordinates: " << endl << "x1 | " << this->points[0].x << " y1 | " << this->points[0].y << endl << "x2 | " << this->points[1].x << " y2 | " << this->points[1].y << endl << "x3 | " << this->points[2].x << " y3 | " << this->points[2].y << endl << "Center:" << endl << this->center.x << " " << this->center.y << endl  << "Color: " << endl << "Red: " << (int)currentColor.r << " | Green: " << (int)currentColor.g << " | Blue: " << (int)currentColor.b << endl << "ID: " << this->id << endl << "---------------" << endl;
}

bool RightTriangle::IsInsideOfAnother(const Shape & other)
{
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        if (const IsoscelesTriangle* xyz = dynamic_cast<const IsoscelesTriangle*>(&other))
        {
            sum += ShapeTest(this->points, xyz->points, 3, i);
        }
        else if (const RightTriangle* xyz = dynamic_cast<const RightTriangle*>(&other))
        {
            sum += ShapeTest(this->points, xyz->points, 3, i);
        }
        else if (const Quadrate* xyz = dynamic_cast<const Quadrate*>(&other)) {
            sum += ShapeTest(this->points, xyz->points, 4, i);
        }
    }
    if (sum == 3)
        return true;
    else
        return false;
}


void RightTriangle::Move(double _x, double _y)
{
    MoveShape(this->points, this->center, _x, _y, 3);
    NewTriangleCenter(this->points, this->center);
}


void RightTriangle::Rotate(double _angle)
{
    RotateShape(this->points, this->center, _angle, 3);
}

void RightTriangle::Scale(double _scale)
{
    ScaleShape(this->points, this->center, _scale, 3);
}

ostream & operator<<(ostream &out, Shape & a)
{
    return a.put(out);
}

Shape *Shape::createRandomShape()
{
    static std::function<Shape*()> childCreators[] = {Quadrate::createRandomShape, IsoscelesTriangle::createRandomShape, RightTriangle::createRandomShape};
    static const size_t childN = sizeof(childCreators) / sizeof(childCreators[0]);
    int s = std::uniform_int_distribution<int>(0, childN-1)(rng);
    return childCreators[s]();
}

Quadrate *Quadrate::createRandomShape() {
    return new Quadrate(
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // ax
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // ay
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // bx
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // by
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // cx
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // cy
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // dx
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // dy
        Color(
                std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // r
                std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // g
                std::uniform_int_distribution<unsigned int>(0, magicborder)(rng) // b
        )
    );
}

IsoscelesTriangle *IsoscelesTriangle::createRandomShape() {
    return new IsoscelesTriangle(
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // ax
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // ay
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // bx
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // by
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // cx
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // cy
        Color(
                std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // r
                std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // g
                std::uniform_int_distribution<unsigned int>(0, magicborder)(rng) // b
        )
    );
}

RightTriangle *RightTriangle::createRandomShape() {
    return new RightTriangle(
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // ax
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // ay
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // bx
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // by
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // cx
        std::uniform_real_distribution<double>(-magicborder, magicborder)(rng), // cy
        Color(
                std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // r
                std::uniform_int_distribution<unsigned int>(0, magicborder)(rng), // g
                std::uniform_int_distribution<unsigned int>(0, magicborder)(rng) // b
        )
    );
}
