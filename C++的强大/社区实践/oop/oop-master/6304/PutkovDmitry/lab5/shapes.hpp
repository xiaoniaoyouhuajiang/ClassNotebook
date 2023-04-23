
#include <iostream>
#include <cmath>
#include <memory>
#include <algorithm>
#include <string>

#define PI 3.14159265

using namespace std;

class Shape {
public:
    Shape(string newColor = "white") :
            color(newColor) {}

    virtual string getColor() { return color; }

    virtual void setColor(string newColor) {
        this->color = newColor;
    }

    virtual void getLocation() {
        cout << "There is no location of the subject" << endl;

    }

    virtual void setLocation(float k = 1) {
        cout << "This function was not overrided" << endl;
    };

    virtual void turnFigure(float grad = 0) {
        cout << "This function was not overrided" << endl;
    };

    virtual float getSize() {
        cout << "This function was not overrided" << endl;
        return 0;
    };

    virtual float getSquare() {
        cout << "This function was not overrided" << endl;
        return 0;
    }

protected:
    string color;

    float getSide(float x, float y) {
        return sqrt(x * x + y * y);
    }

};

class Triangle : public Shape {
public:
    Triangle(float x1 = 0, float y1 = 0,
             float x2 = 0, float y2 = 0,
             float x3 = 0, float y3 = 0,
             string newColor = "white") :
            x1(x1), y1(y1), x2(x2),
            y2(y2), x3(x3), y3(y3),
            color(newColor) {}


    void getLocation() override {
        cout << "The first point's coordinate: " << this->x1 << ", " << this->y1 << endl;
        cout << "The second point's coordinate: " << this->x2 << ", " << this->y2 << endl;
        cout << "The third point's coordinate: " << this->x3 << ", " << this->y3 << endl;
    }

    void setLocation(float k = 1) override {
        this->x2 *= k;
        this->x3 *= k;

        this->y2 *= k;
        this->y3 *= k;
    }

    void turnFigure(float grad = 0) override {
        this->x1 = this->x1 * sin(grad * PI / 180) + this->y1 * cos(grad * PI / 180);
        this->x2 = this->x2 * sin(grad * PI / 180) + this->y2 * cos(grad * PI / 180);
        this->x3 = this->x3 * sin(grad * PI / 180) + this->y3 * cos(grad * PI / 180);

        this->y1 = this->y1 * cos(grad * PI / 180) - this->y1 * sin(grad * PI / 180);
        this->y2 = this->y2 * cos(grad * PI / 180) - this->y2 * sin(grad * PI / 180);
        this->y3 = this->y3 * cos(grad * PI / 180) - this->y3 * sin(grad * PI / 180);
    }


    float getSquare() override {
        float a = getSide(abs(this->x2 - this->x1),
                          abs(this->y2 - this->y1));
        float b = getSide(abs(this->x3 - this->x2),
                          abs(this->y3 - this->y2));
        float c = getSide(abs(this->x3 - this->x1),
                          abs(this->y3 - this->y1));
        float p = getPerimeter(a, b, c);
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

private:
    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;
    string color;

    float getPerimeter(float a, float b, float c) {
        return a + b + c;
    }

};

class Rectangle : public Shape {
public:
    Rectangle(float x1 = 0, float y1 = 0,
              float x2 = 0, float y2 = 0,
              float x3 = 0, float y3 = 0,
              float x4 = 0, float y4 = 0,
              string newColor = "white") :
            x1(x1), y1(y1), x2(x2),
            y2(y2), x3(x3), y3(y3),
            x4(x4), y4(y4),
            color(newColor) {}

    void getLocation() override {
        cout << "The first point's coordinate: " << this->x1 << ", " << this->y1 << endl;
        cout << "The second point's coordinate: " << this->x2 << ", " << this->y2 << endl;
        cout << "The third point's coordinate: " << this->x3 << ", " << this->y3 << endl;
        cout << "The fourth point's coordinate: " << this->x4 << ", " << this->y4 << endl;
    }


    void turnFigure(float grad = 0) override {
        this->x1 = this->x1 * sin(grad * PI / 180) + this->y1 * cos(grad * PI / 180);
        this->x2 = this->x2 * sin(grad * PI / 180) + this->y2 * cos(grad * PI / 180);
        this->x3 = this->x3 * sin(grad * PI / 180) + this->y3 * cos(grad * PI / 180);
        this->x4 = this->x4 * sin(grad * PI / 180) + this->y4 * cos(grad * PI / 180);

        this->y1 = this->y1 * cos(grad * PI / 180) - this->y1 * sin(grad * PI / 180);
        this->y2 = this->y2 * cos(grad * PI / 180) - this->y2 * sin(grad * PI / 180);
        this->y3 = this->y3 * cos(grad * PI / 180) - this->y3 * sin(grad * PI / 180);
        this->y4 = this->y4 * cos(grad * PI / 180) - this->y4 * sin(grad * PI / 180);
    }

    void setLocation(float k = 1) override {
        this->x2 *= k;
        this->x3 *= k;
        this->x4 *= k;

        this->y2 *= k;
        this->y3 *= k;
        this->y4 *= k;
    }

    float getSquare() override {
        float a = getSide(abs(this->x2 - this->x1),
                          abs(this->y2 - this->y1));
        float b = getSide(abs(this->x3 - this->x2),
                          abs(this->y3 - this->y2));
        return a * b;
    }

private:
    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;
    float x4;
    float y4;
    string color;
};