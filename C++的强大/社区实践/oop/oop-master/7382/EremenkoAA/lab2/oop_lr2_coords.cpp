#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>
#include <exception>

using namespace std;

struct Point
{
    double x;
    double y;
};

struct RGB
{
    int R;
    int G;
    int B;
};

class Shape
{
  protected:
    static int i;
    vector<Point> points;
    int angle;
    RGB color;
    Point center;
    double scale;

  public:
    Shape()
    {
        color = {0, 0, 0};
        scale = 1;
        angle = 0;
        i++;
    }

    // Перемещение фигуры
    void MoveFigure(Point new_center)
    {
        double dx = new_center.x - center.x;
        double dy = new_center.y - center.y;
        for (int i = 0; i < points.size(); i++)
        {
            points[i].x = points[i].x + dx;
            points[i].y = points[i].y + dy;
            cout << points[i].x << "     " << points[i].y << endl;
        }
        center = new_center;
    }

    // Поворот на угол
    void RotationAngle(int new_angle)
    {
        angle = new_angle;
        new_angle %= 360;
        double an = new_angle * M_PI / 180;
        double _x, _y;
        for (unsigned int i = 0; i < points.size(); ++i)
        {
            _x = points[i].x;
            _y = points[i].y;
            points[i].x = (_x - center.x) * cos(an) - (_y - center.y) * sin(an) + center.x;
            points[i].y = (_x - center.x) * sin(an) + (_y - center.y) * cos(an) + center.y;
        }
    }
    virtual void Scaling(double k) = 0;

    // Раскраска
    void Coloring(int new_R, int new_G, int new_B)
    {
        color.R = new_R;
        color.G = new_G;
        color.B = new_B;
    }

    // Вывод информации
    void ShapeInfo(ostream &out)
    {
        out.precision(2);
        out << "ID = " << i << endl;
        out << "Figure centre: (" << center.x << ", " << center.y << ")\n";
        out << "Angle of rotation = " << angle << endl;
        out << "Color (RGB): (" << color.R << ", " << color.G << ", " << color.B << ")\n";
        out << "Scale factor = " << scale << endl;
        out << endl;
    }
    friend ostream &operator<<(ostream &out, Shape &sh)
    {
        sh.ShapeInfo(out);
        return out;
    }
    virtual ~Shape() {}
};

// Клссс прямоугольника
class Rectangle : public Shape
{
  private:
    Point low_l, up_r;

  public:
    Rectangle(Point low_l, Point up_r)
        : low_l(low_l), up_r(up_r)
    {
        makecoord();
    }

    void makecoord()
    {
        center = {(low_l.x + up_r.x) / 2, (low_l.y + up_r.y) / 2};
        points.push_back(low_l);
        points.push_back({low_l.x, up_r.y});
        points.push_back(up_r);
        points.push_back({up_r.x, low_l.y});
    }

    void Scaling(double k)
    {
        low_l.x *= k;
        low_l.y *= k;
        up_r.x *= k;
        up_r.y *= k;
        scale *= k;
        points.clear();
        makecoord();
    }
    ~Rectangle() {}
};

// Класс трапеции
class Trapezoid : public Shape
{
  protected:
    Point low_l, up_l, up_r, low_r;

  public:
    Trapezoid(Point low_l, Point up_l, Point up_r, Point low_r)
        : low_l(low_l), up_l(up_l), up_r(up_r), low_r(low_r)
    {
        makecoords();
    }

    void makecoords()
    {
        double c = sqrt((up_l.x - low_l.x) * (up_l.x - low_l.x) + (up_l.y - low_l.y) * (up_l.y - low_l.y));
        double d = sqrt((up_r.x - low_r.x) * (up_r.x - low_r.x) + (up_r.y - low_r.y) * (up_r.y - low_r.y));
        center.x = (low_r.x - low_l.x) / 2 + ((2 * (up_r.x - up_l.x) + (low_r.x - low_l.x)) * (pow(c, 2) - pow(d, 2))) / (6 * (pow(low_r.x - low_l.x, 2) - pow(up_r.x - up_l.x, 2))) + low_l.x;
        center.y = (sqrt(pow(up_l.x - up_l.x, 2) + pow(up_l.y - low_l.y, 2))) * ((low_r.x - low_l.x) + 2 * (up_r.x - up_l.x)) / (3 * ((up_r.x - up_l.x) + (low_r.x - low_l.x))) + low_l.y;
        points.clear();
        points.push_back(low_l);
        points.push_back(up_l);
        points.push_back(up_r);
        points.push_back(low_r);
    }

    void Scaling(double k)
    {
        low_l.x *= k;
        low_l.y *= k;
        up_l.x *= k;
        up_l.y *= k;
        up_r.x *= k;
        up_r.y *= k;
        low_r.x *= k;
        low_r.y *= k;
        scale *= k;
        points.clear();
        makecoords();
    }

    ~Trapezoid() {}
};

// Класс равнобедренной трапеции
class ITrapezoid : public Trapezoid
{
  public:
    ITrapezoid(Point low_l, Point up_l, Point up_r) : Trapezoid(low_l, up_l, up_r, {((up_l.x - low_l.x) + up_r.x), low_l.y}){};
    ~ITrapezoid() {}
};

int Shape::i = 0;

int main()
{
    Shape *sh;
    //Тестирование

    /*   Rectangle p({2, 2}, {6, 4});
    sh = &p;
    cout << p;
    sh->Scaling(2);
    cout << p;
    sh->Coloring(1, 1, 1);
    sh->RotationAngle(90);
    cout << p;
    sh->Scaling(2);
    cout << p;
    sh->MoveFigure({1, 1});
    cout << p;
*/
    /* Trapezoid t({2, 2}, {5, 5}, {7, 5}, {11, 2});
   sh = &t;
   cout << t;
   sh->Coloring(1, 1, 1);
   cout<< t;
   sh->MoveFigure({1, 1});
   cout << t;
   sh->Scaling(2);
   cout << t;
   sh->RotationAngle(180);
   cout<<t;
   */
    /*  ITrapezoid q({1, 1}, {3, 3}, {5, 3});
    sh = &q;
    cout << q;
    sh->Scaling(2);
    cout << q;
    sh->RotationAngle(180);
    cout << q;
    sh->Coloring(1, 1, 1);
    cout << q;
    //sh->MoveFigure({0, 3});
    cout << q;
*/
    return 0;
}