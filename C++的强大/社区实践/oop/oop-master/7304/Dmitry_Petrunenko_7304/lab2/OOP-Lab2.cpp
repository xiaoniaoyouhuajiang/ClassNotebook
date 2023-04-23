#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;
# define PI 3.14159265358979323846

struct point
{
    double x;
    double y;
};

struct Colour
{
    unsigned short Red;
    unsigned short Green;
    unsigned short Blue;
    Colour(unsigned short r, unsigned short g,
        unsigned short b)
    {
        Red = r;
        Green = g;
        Blue = b;
    }
};


class Shape{
public:
    Shape(int Size) : colour(0, 0, 0), angle(0), points(points ? new point[Size] : nullptr), numPoint(Size)
        { ID++; }
    virtual void scaling(double k) = 0; //масштабирование
    virtual void info(std::ostream& out) = 0; // информация о классе
    virtual ~Shape() { delete [] points; }
    void set_colour(Colour new_colour)
        {
            colour = new_colour;
        } //установка цвета
        Colour get_colour() const
        {
            return colour;
        } //получение цвета
    void moving (double new_x, double new_y){
        for(int i=0;i<numPoint;i++){
            points[i].x += new_x;
            points[i].y += new_y;
        }
    } //перемещение
    void turn (int deg){
        angle += deg;
        angle %= 360;
        double radian = angle * PI / 180;
        for(int i=0;i<numPoint;i++){
            double tmp_x = points[i].x*cos(radian) - points[i].y*sin(radian);
            double tmp_y = points[i].y*cos(radian) + points[i].x*sin(radian);
            points[i].x = tmp_x;
            points[i].y = tmp_y;
         }
    } //поворот

protected:
    void scalingPoint(double& k)
        {
            k = fabs(k);
            for (int i=0;i<numPoint;i++)
            {
                points[i].x *= k;
                points[i].y *= k;
            }
        }
    friend ostream& operator<<(ostream& out, Shape& shape)
        {
            shape.info(out);
            return out;
        }
    Colour colour;
    int angle;
    int numPoint;
    point* points;
    static int ID;
};

class Parallelogram : public Shape
{
    int thisId;
    protected:
    double a;
    double b;
    double alpha;

public:
    Parallelogram(point centerPoint, double a, double b, double alpha) :
        Shape(4), a(a), b(b), alpha(alpha), thisId(ID)
    {
        double rad = alpha * PI / 180;
        double h = a * sin(rad);

        points[0] = { centerPoint.x - b / 2 - h / (2 * tan(rad)), centerPoint.y - h / 2 };
        points[1] = { centerPoint.x - b / 2 + h / (2 * tan(rad)), centerPoint.y + h / 2 };
        points[2] = { centerPoint.x + b / 2 + h / (2 * tan(rad)), points[1].y };
        points[3] = { centerPoint.x + b / 2 - h / (2 * tan(rad)), points[0].y };
    }
    void scaling(double k)
    {
        scalingPoint(k);
        a *= k;
        b *= k;
    }
    void info(std::ostream& out)
    {
        out << "Parallelogram:\n";
        out << "List of points:\n";
        for (int i=0;i<numPoint;i++)
        {
            out << "(" << points[i].x << "," << points[i].y << ") ";
        }
        out << "\nColor: (" << colour.Red << "," << colour.Green << "," << colour.Blue << ")\n";
        out << "A: " << a << " B: " << b << "\n";
        out << "ID = "<< thisId <<"\n";
    }
};


class Rectangle : public Parallelogram{
    int thisId;
public:
    Rectangle(point centerPoint, double a, double b) :
        Parallelogram(centerPoint, a, b, 90), thisId(ID) {}
    void info(std::ostream& out)
    {
        out << "Rectangle:\n";
        out << "List of points:\n";
        for (int i=0;i<numPoint;i++)
        {
            out << "(" << points[i].x << "," << points[i].y << ") ";
        }
        out << "\nColor: (" << colour.Red << "," << colour.Green << "," << colour.Blue << ")\n";
        out << "A: " << a << " B: " << b << "\n";
        out << "ID = "<< thisId<<"\n";
    }
};


class Regular_Hexagon : public Shape
{
    int thisId;
    protected:
    double radius;
    double alpha;

public:
    Regular_Hexagon(point centerPoint, double r) :
        Shape(6), radius(r), alpha(60), thisId(ID)
    {
        double rad;
        for(int i=0;i<numPoint;i++){
            rad = (alpha*i)* PI / 180;
            points[i] = { centerPoint.x + radius*cos(rad) , centerPoint.y + radius*sin(rad) };
        }
    }
    void scaling(double k)
    {
        scalingPoint(k);
        radius *= k;
    }
    void info(std::ostream& out)
    {
        out << "Regular Hexagon:\n";
        out << "List of points:\n";
        for (int i=0;i<numPoint;i++)
        {
            out << "(" <<points[i].x << "," << points[i].y << ") ";
        }
        out << "\nColor: (" << colour.Red << "," << colour.Green << "," << colour.Blue << ")\n";
        out << "Radius: " << radius << "\n";
        out << "ID = "<< thisId <<"\n";
    }
};

int Shape::ID = 0;

int main()
{
        point dotcentrePar;
            dotcentrePar.x = 0;
            dotcentrePar.y = 5;
            Parallelogram s(dotcentrePar, 8, 6, 30);
            cout << s;
                Rectangle as(dotcentrePar, 8, 6);
                cout << as;
             Regular_Hexagon RR(dotcentrePar, 2);
             cout << RR;
    return 0;
}