#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <iostream>
using namespace std;

struct point {

    double x;
    double y;
};

enum colors { RED, GREEN, BLUE, YELLOW, NO_COLOR };

class Shape {

    protected:

        vector <point> coordinates;
        point center;
        double angle;
        long int id;
        colors color;

    public:

        Shape(point _center) {

            static long int count = 0;
            id     = count++;
            color  = NO_COLOR;
            angle  = 0;
            center = _center;
        };

        virtual void scale(double multiplier) = 0;

        virtual double getArea() = 0;

        void move(point newCenter) {

            center = newCenter;
            makeCoordinates();
        }

        void rotate(double _angle) {

            double _x, _y;

            for (int i = 0; i < coordinates.size(); ++i) {

                _x = coordinates[i].x;
                _y = coordinates[i].y;

                coordinates[i].x = (_x - center.x) * cos(_angle) - (_y - center.y) * sin(_angle) + center.x;
                coordinates[i].y = (_x - center.x) * sin(_angle) + (_y - center.y) * cos(_angle) + center.y;
            }

            angle = _angle;
        }

        colors getColor() {

            return color;
        }

        void setColor(colors _color) {

            color = _color;
        }

        bool operator== (Shape& shp) {
            return getArea() - shp.getArea() < 0.000001;
        }

        bool operator!= (Shape& shp) {
            return !(this->operator ==(shp));
        }

        bool operator< (Shape& shp) {
            return getArea() - shp.getArea() < 0;
        }

        bool operator> (Shape& shp) {
            return !(this->operator <(shp));
        }

        virtual ~Shape() {};

        friend ostream& operator<< (ostream& outputStream, const Shape& shape) {

            outputStream << "Id: " << shape.id << endl;
            outputStream << "Coordinates of extreme points: ";

            for (int i = 0; i < shape.coordinates.size(); ++i) {

                outputStream << "(" << shape.coordinates[i].x << ", " << shape.coordinates[i].y << ") ";
            }

            outputStream << endl << "Color: ";

            switch (shape.color) {

                case RED:
                    outputStream << "red"    << endl;
                    break;

                case GREEN:
                    outputStream << "green"  << endl;
                    break;

                case BLUE:
                    outputStream << "blue"   << endl;
                    break;

                case YELLOW:
                    outputStream << "yellow" << endl;
                    break;

                case NO_COLOR:
                default:
                    outputStream << "color is not defined" << endl;
                    break;
            }

            return outputStream;
        }

    private:

        virtual void makeCoordinates() = 0;
};

#endif // SHAPE_H
