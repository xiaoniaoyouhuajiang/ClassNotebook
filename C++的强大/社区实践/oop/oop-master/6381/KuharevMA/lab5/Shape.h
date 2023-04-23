#include <string>
#include <cmath>
#include <iostream>

using namespace std;

namespace custom
{
    class Shape
    {
    public:
        virtual ~Shape();
        virtual void MoveFigure(int, int) = 0; //пермещение
        virtual void TurnFigure(int) = 0; //поворот
        virtual void ScaleFigure(double) = 0; //масштаб
        virtual string GetColorFigure() = 0; //получить цвет
        virtual void SetColorFigure(string) = 0; //задать цвет
        friend ostream&operator<<(ostream&, const Shape&); //поток вывода

        int X = 0, Y = 0;//центр фигуры
        int Angle = 0; //угол поворота
    protected:
        static  int ID;
        double Scale = 1; // изначальный масштаб
        string Color = "Белый";//цвет фигуры
    };

    class Pentagon : public Shape
    {
    public:
        int  Side;
        int Id;
        Pentagon(int, int, int, double, int, string);
        Pentagon(int);
        void MoveFigure(int, int); //пермещение
        void TurnFigure(int); //поворот
        void ScaleFigure(double); //масштаб
        string GetColorFigure(); //получить цвет
        void SetColorFigure(string); //задать цвет
        int GetSide();
        void SetSide(int);
        friend ostream& operator<<(ostream&a, const Pentagon&b)
        {
            a << "ID фигуры: id=" << b.Id << "\n";
            a << "Центр фигуры: x=" << b.X << "; y=" << b.Y << "\n";
            a << "Цвет: " << b.Color << "\n";
            a << "Угол поворота фигуры: fi=" << b.Angle << "\n";
            a << "Масштаб: delta=" << b.Scale << "\n";
            a << "Длины сторон с учетом мастаба: Сторона пятиугольника=" << b.Side*b.Scale << "\n";
            return a;
        }
        ~Pentagon();
    };

    class Segment : public Shape
    {
    private:
        double Length;
        int Id;
    public:
        Segment(int, int, int, double, int, string);
        Segment(int Length);
        void MoveFigure(int, int); //пермещение
        void TurnFigure(int); //поворот
        void ScaleFigure(double); //масштаб
        string GetColorFigure(); //получить цвет
        void SetColorFigure(string); //задать цвет
        void SetLength(int);
        int GetLength();
        friend ostream&operator<<(ostream&a, const Segment&b) {
            a << "ID фигуры: id=" << b.Id << "\n";
            a << "Центр фигуры: x=" << b.X << "; y=" << b.Y << "\n";
            a << "Цвет: " << b.Color << "\n";
            a << "Угол поворота фигуры: fi=" << b.Angle << "\n";
            a << "Масштаб: delta=" << b.Scale << "\n";
            a << "Длина с учетом мастаба: Горизонтальная сторона=" << b.Length*b.Scale << "\n";
            return a;
        }
        ~Segment();
    };

    class Ellipse : public custom::Shape
    {
    public:
        int SmallAxle, BigAxle;
        int Id;
        Ellipse(int, int, int, int, double, int, string);
        Ellipse(int, int);
        void MoveFigure(int, int); //перемещение
        void TurnFigure(int); //поворот
        void ScaleFigure(double); //масштаб
        string GetColorFigure(); //получить цвет
        void SetColorFigure(string); //задать цвет
        int GetSAxle();
        int GetBAxle();
        void SetAxles(int, int);
        friend ostream&operator<<(ostream& a, const Ellipse& b) {

            a << "ID фигуры: id=" << b.Id << "\n";
            a << "Центр фигуры: x=" << b.X << "; y=" << b.Y << "\n";
            a << "Цвет: " << b.Color << "\n";
            a << "Угол поворота фигуры: fi=" << b.Angle << "\n";
            a << "Масштаб: delta=" << b.Scale << "\n";
            a << "Высота эллипса с учётом масштабирования=" << b.BigAxle*b.Scale << "  Ширина эллипса=" << b.SmallAxle*b.Scale << "\n";
            return a;
        }
        ~Ellipse();
    };
}


