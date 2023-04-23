//
//  main.cpp
//  Lab2_OOP
//
//  Created by Михаил Дементьев on 25/02/2019.
//  Copyright © 2019 Михаил Дементьев. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>
#include <exception>
#include <cmath>

using namespace std;

static const double Pi = M_PI;

struct PT
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

class Shape {
private:
    static int NextCustomerId;
protected:
    int angle;
    RGB color;
    PT centre;
    double scaleValue;
    unsigned long long int id;
public:
    Shape(double _x, double _y)
    {
        centre.x = _x;
        centre.y = _y;
        scaleValue = 1;
        angle = 0;
        color = { 0,0,0 };
        NextCustomerId++;
    }
    
    virtual ~Shape() {}
    
    virtual void MoveFigure(double other_x, double other_y) = 0;
    virtual void SetTurnAngle(int other_angle) = 0;
    virtual void Scaling(double k) = 0;
    
    void SetColor(int new_R, int new_G, int new_B) {
        color = { new_R, new_G, new_B };
    }
    
    void PrintShapeInfo(ostream& out) {
        out.precision(2);
        out << "Shape ID: " << NextCustomerId << endl;
        out << "Figure centre: (" << centre.x << ", " << centre.y << ")\n";
        out << "Angle of rotation = " << angle << endl;
        out << "Color (RGB): (" << color.R << ", " << color.G << ", " << color.B << ")\n";
        out << "Scale factor = " << scaleValue << endl;
        out << endl;
    }
    friend ostream& operator<<(ostream& out, Shape& sh)
    {
        sh.PrintShapeInfo(out);
        return out;
    }
};

int Shape:: NextCustomerId = 0;

class fivePointedStar : public Shape {
protected:
    PT X1, X2, X3, X4, X5;
public:
    fivePointedStar(double x1, double y1, double radius)
    : Shape(x1, y1) {
        
        double angle = 2 * Pi / 5;              //делится круг на 5 частей
        X1.x = x1 + radius * cos(angle * 0);
        X1.y = y1 + radius * sin(angle * 0);
        X2.x = x1 + radius * cos(angle * 1);
        X2.y = y1 + radius * sin(angle * 1);
        X3.x = x1 + radius * cos(angle * 2);
        X3.y = y1 + radius * sin(angle * 2);
        X4.x = x1 + radius * cos(angle * 3);
        X4.y = y1 + radius * sin(angle * 3);
        X5.x = x1 + radius * cos(angle * 4);
        X5.y = y1 + radius * sin(angle * 4);
        
        
    }
    
    void MoveFigure(double new_x, double new_y) {
        X1.x += new_x - centre.x;
        X1.y += new_y - centre.y;
        X2.x += new_x - centre.x;
        X2.y += new_y - centre.y;
        X3.x += new_x - centre.x;
        X3.y += new_y - centre.y;
        X4.x += new_x - centre.x;
        X4.y += new_y - centre.y;
        X5.x += new_x - centre.x;
        X5.y += new_y - centre.y;
        centre.x = new_x;
        centre.y = new_y;
        
    }
    
    void SetTurnAngle(int new_angle)
    {
        angle += new_angle;
        angle %= 360;
        double rad = angle * Pi / 180;
        
        vector<PT> points;
        points.push_back(X1); points.push_back(X2);
        points.push_back(X3); points.push_back(X4);
        points.push_back(X5);
        
        for (auto& pt : points) {
            PT tmp_dot = pt;
            pt.x = tmp_dot.x * cos(rad) - tmp_dot.y * sin(rad);
            pt.y = tmp_dot.y * cos(rad) + tmp_dot.y * sin(rad);
        }
        
        X1 = points[0];
        X3 = points[2];
        X2 = points[1];
        X4 = points[3];
        X5 = points[4];
    }
    
    void Scaling(double k) {
        scaleValue *= k;
        centre.x *= k;
        centre.y *= k;
        
        X2.x *= k;
        X2.y *= k;
        X3.x *= k;
        X3.y *= k;
        X4.x *= k;
        X4.y *= k;
        X5.x *= k;
        X5.y *= k;
    }
    
    friend ostream& operator<<(ostream& out, fivePointedStar& fpStar)
    {
        out << "five-pointed star" << endl;
        fpStar.PrintShapeInfo(out);
        out << "POINTS COORDINATES:\n";
        out << "POINT X1: (" << fpStar.X1.x << ", " << fpStar.X1.y << ")\n";
        out << "POINT X2: (" << fpStar.X2.x << ", " << fpStar.X2.y << ")\n";
        out << "POINT X3: (" << fpStar.X3.x << ", " << fpStar.X3.y << ")\n";
        out << "POINT X4: (" << fpStar.X4.x << ", " << fpStar.X4.y << ")\n";
        out << "POINT X5: (" << fpStar.X5.x << ", " << fpStar.X5.y << ")\n";
        out << "-----------------------------------------------";
        out << endl;
        return out;
    }
};

class hexagonalStar : public Shape {
protected:
    PT X1, X2, X3, X4, X5, X6;
public:
    hexagonalStar(double x1, double y1, double h) : Shape(x1, y1),
    length(h) {
        double angle = 2 * Pi / 6;              //делится круг на 5 частей
        X1.x = x1 + h * cos(angle * 0);
        X1.y = y1 + h * sin(angle * 0);
        X2.x = x1 + h * cos(angle * 1);
        X2.y = y1 + h * sin(angle * 1);
        X3.x = x1 + h * cos(angle * 2);
        X3.y = y1 + h * sin(angle * 2);
        X4.x = x1 + h * cos(angle * 3);
        X4.y = y1 + h * sin(angle * 3);
        X5.x = x1 + h * cos(angle * 4);
        X5.y = y1 + h * sin(angle * 4);
        X5.x = x1 + h * cos(angle * 5);
        X5.y = y1 + h * sin(angle * 5);
    }
    
    void Scaling(double factor){
        scaleValue *= 2;
        length *= factor;
        centre.x *= factor;
        centre.y *= factor;
        
        X2.x *= factor;
        X2.y *= factor;
        X3.x *= factor;
        X3.y *= factor;
        X4.x *= factor;
        X4.y *= factor;
        X5.x *= factor;
        X5.y *= factor;
    }
    
    void MoveFigure(double newX, double newY) {
        X1.x += newX - centre.x;
        X1.y += newY - centre.y;
        X2.x += newX - centre.x;
        X2.y += newY - centre.y;
        X3.x += newX - centre.x;
        X3.y += newY - centre.y;
        X4.x += newX - centre.x;
        X4.y += newY - centre.y;
        X5.x += newX - centre.x;
        X5.y += newY - centre.y;
        X6.x += newX - centre.x;
        X6.y += newY - centre.y;
        centre.x = newX;
        centre.y = newY;
    }
    
    void SetTurnAngle(int rotation_angle) {
        angle += rotation_angle;
        angle %= 360;
        double rad = angle * Pi / 180;
        
        vector<PT> points;
        points.push_back(X1); points.push_back(X2);
        points.push_back(X3); points.push_back(X4);
        points.push_back(X5); points.push_back(X6);
        
        for (auto& pt : points) {
            PT tmp_dot = pt;
            pt.x = tmp_dot.x * cos(rad) - tmp_dot.y * sin(rad);
            pt.y = tmp_dot.y * cos(rad) + tmp_dot.y * sin(rad);
        }
        
        X1 = points[0];
        X3 = points[2];
        X2 = points[1];
        X4 = points[3];
        X5 = points[4];
        X6 = points[5];
    }
    
    friend ostream &operator<<(ostream &out, hexagonalStar &hexagram) {
        out << "hexagonalStar" << endl;
        hexagram.PrintShapeInfo(out);
        out << "INFO ABOUT SIZE:\n";
        out << "Distance between opposite vertices: " << hexagram.length << endl;
        out << "POINTS COORDINATES:\n";
        out << "POINT X1: (" << hexagram.X1.x << ", " << hexagram.X1.y << ")\n";
        out << "POINT X2: (" << hexagram.X2.x << ", " << hexagram.X2.y << ")\n";
        out << "POINT X3: (" << hexagram.X3.x << ", " << hexagram.X3.y << ")\n";
        out << "POINT X4: (" << hexagram.X4.x << ", " << hexagram.X4.y << ")\n";
        out << "POINT X5: (" << hexagram.X5.x << ", " << hexagram.X5.y << ")\n";
        out << "-----------------------------------------------";
        out << endl;
        return out;
    }
    
private:
    double length;
};

class Circle : public Shape {
public:
    Circle(double x1, double y1, double radius) : Shape(x1, y1),
    radius(radius) {}
    
    void Scaling(double factor){
        scaleValue*=factor;
        radius *= factor;
    }
    
    void MoveFigure(double newX, double newY) {
        centre.x = newX;
        centre.y = newY;
    }
    
    void SetTurnAngle(int rotation_angle) {}
    
    friend ostream &operator<<(ostream &out, Circle &circle) {
        out << "Circle" << endl;
        circle.PrintShapeInfo(out);
        out << "INFO ABOUT SIZE:\n";
        out << "Сircle radius: " << circle.radius << endl;
        out << "-----------------------------------------------";
        out << endl;
        return out;
    }
    
private:
    double radius;
};


int main() {
    
    fivePointedStar pent(20, 30, 11);
    cout << pent;
    pent.MoveFigure(0, 0);
    pent.SetTurnAngle(30);
    pent.Scaling(2);
    cout << pent;
    
    hexagonalStar hex(20, 20, 10);
    cout << hex;
    hex.Scaling(2);
    hex.MoveFigure(0, 0);
    cout << hex;
    
    Circle circl(0, 10, 5);
    cout << circl;
    circl.SetColor(256, 256, 256);
    circl.Scaling(2);
    cout << circl;
    
    return 0;
}

