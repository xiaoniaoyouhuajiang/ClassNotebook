// 10 вариант: Прямоугольник, Трапеция, Равнобедренная трапеция.

#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

class Point {
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    Point &operator = (Point const &newPoint) = default;
    
    friend ostream &operator << (ostream &out, Point const &point) {
        out << "(x = " << point.x << ",y = " << point.y << ")";
        return out;
    }
    
    double x, y;
};

class Color {
public:
    Color(unsigned int red, unsigned int green, unsigned int blue) : RED(red), GREEN(green), BLUE(blue) {}
    
    Color() {}
    
    Color green() {
        return Color(0, 255, 0);
    }
    
    Color black() {
        return Color(0, 0, 0);
    }
    
    Color white() {
        return Color(255, 255, 255);
    }
    
    friend ostream &operator << (ostream &out, Color const &c) {
        out << "(R = " << c.RED << ", G = " << c.GREEN << ", B = " << c.BLUE << ")";
        return out;
    }
    
    unsigned int getR() {
        return RED;
    }
    
    unsigned int getG() {
        return GREEN;
    }
    
    unsigned int getB() {
        return BLUE;
    }
    
private:
    unsigned int RED, GREEN, BLUE;
};

class Shape {
private:
    static int id;
public:
    Shape(Point point = Point(0, 0), Color col = Color(255, 255, 255), double ang = 0)
    : center(point), color(col), angle(ang) {
        id++;
        defaultSet();
    }
    
    virtual void mv(Point mvPoint) {center = mvPoint;}
    
    virtual void rotate(double a) {angle += a;}
    
    void rotatePoints() {
        rotatePoint(this->p1);
        rotatePoint(this->p2);
        rotatePoint(this->p3);
        rotatePoint(this->p4);
    }
    
    virtual void setColor(Color c) {
        color = c;
    }
    
    virtual Color getColor() {
        return color;
    }
    
    Point getCenter() {
        return center;
    }
    
    virtual void scale(double) = 0;
    
    friend ostream &operator << (ostream &out, Shape &shape) {
        shape.rotatePoints();
        cout << "IDENTIFIRE: " << shape._id << endl <<
        "COLOR: " << shape.color << endl <<
        "CENTER OFFSET: " << shape.center << endl <<
        "ANGLE: " << shape.angle << endl <<
        "p1:" << shape.p1 << ", p2:" << shape.p2 <<
        ", p3:" << shape.p3 << ", p4:" << shape.p4 << endl;
        return out;
    }
    
private:
    Color color;
    Point center;
    double angle;
    
    void rotatePoint(Point & point) {
        double rad = angle * M_PI / 180;
        
        double X = point.x;
        double Y = point.y;
        X -= center.x;
        Y -= center.y;
        
        double newX = X * cos(rad) - Y * sin(rad);
        double newY = X * sin(rad) + Y * cos(rad);
        
        point.x = newX + center.x;
        point.y = newY + center.y;
    }
    void defaultSet() {_id = id;}
protected:
    Point p1, p2, p3, p4;int _id;
};

int Shape::id = 0;

class Rectangle : public Shape {
public:
    Rectangle(double width, double height, double angle = 0, Color color = Color(255, 255, 255), Point point = Point(0.0, 0.0))
    : Shape(point, color, angle), width(width), height(height) {updatePoints();}
    
    void scale(double s) override {
        height *= s;
        width *= s;
        updatePoints();
    }
    
    friend ostream &operator<<(ostream &out, Rectangle &rectangle) {
        cout << dynamic_cast<Shape &>(rectangle) << "SHAPE: Rectangle" << endl <<
        "ID " << rectangle._id << endl <<
        "WIDTH: " << rectangle.width << endl <<
        "HEIGHT: " << rectangle.height << endl << endl;
        return out;
    }
    
private:
    double width, height;
    void updatePoints() {
        p1 = Point(-(width/2) + getCenter().x, -(height/2) + getCenter().y);
        p2 = Point(-(width/2) + getCenter().x, (height/2) + getCenter().y);
        p3 = Point((width/2) + getCenter().x, (height/2) + getCenter().y);
        p4 = Point((width/2) + getCenter().x, -(height/2) + getCenter().y);
    }
};

class Line {
public:
    Line(Point s, Point f): start(s), finish(f) {}
private:
    Point start;
    Point finish;
    
    
};

class Trapezium : public Shape {
public:
    Trapezium(double topLineWidth, double bottomLineWidth, double topLineOffset, double height, double angle = 0.0, Color color = Color(255, 255, 255), Point center = Point(0.0, 0.0))
    : Shape(center, color, angle), topLineWidth(topLineWidth), bottomLineWidth(bottomLineWidth), topLineOffset(topLineOffset), height(height) {upadatePoints();}
    
    void scale(double s) override {
        topLineWidth *= s;
        bottomLineWidth *= s;
        height *= s;
        topLineOffset *= s;
        upadatePoints();
    }
    
    friend ostream &operator << (ostream &out, Trapezium &trap) {
        cout << dynamic_cast<Shape &>(trap) << "SHAPE: Trapezium" << endl <<
        "TOP LINE WIDTH: " << trap.topLineWidth << endl <<
        "HEIGHT: " << trap.height << endl <<
        "BOTTOM LINE WIDTH: " << trap.bottomLineWidth << endl <<
        "TOP LINE OFFSET: " << trap.topLineOffset << endl;
        return out;
    }
    
private:
    double topLineWidth;
    double bottomLineWidth;
    double topLineOffset;
    double height;
    
    void upadatePoints() {
        p1 = Point(-(bottomLineWidth/2) + getCenter().x, -(height/2) + getCenter().y);
        p2 = Point(-(topLineWidth/2) + getCenter().x + topLineOffset, (height/2) + getCenter().y);
        p3 = Point((topLineWidth/2) + getCenter().x + topLineOffset, (height/2) + getCenter().y);
        p4 = Point((bottomLineWidth/2) + getCenter().x, -(height/2) + getCenter().y);
    }
};

class RightTrapezium : public Shape {
public:
    RightTrapezium(double height, double topLineWidth, double bottomLineWidth, double angle = 0.0, Color color = Color(255, 255, 255), Point center = Point(0.0, 0.0))
    : Shape(center, color, angle), height(height), topLineWidth(topLineWidth), bottomLineWidth(bottomLineWidth) {upadatePoints();}
    
    void scale(double s) override {
        topLineWidth *= s;
        bottomLineWidth *= s;
        height *= s;
        upadatePoints();
    }
    
    friend ostream &operator << (ostream &out, RightTrapezium &trap) {
        cout << dynamic_cast<Shape &>(trap) << "SHAPE: RightTrapezium" << endl <<
        "TOP LINE WIDTH: " << trap.topLineWidth << endl <<
        "BOTTOM LINE WIDTH: " << trap.bottomLineWidth << endl <<
        "HEIGHT: " << trap.height << endl;
        return out;
    }
    
private:
    double height;
    double topLineWidth;
    double bottomLineWidth;
    
    void upadatePoints() {
        p1 = Point(-(bottomLineWidth/2) + getCenter().x, -(height/2) + getCenter().y);
        p2 = Point(-(topLineWidth/2) + getCenter().x, (height/2) + getCenter().y);
        p3 = Point((topLineWidth/2) + getCenter().x, (height/2) + getCenter().y);
        p4 = Point((bottomLineWidth/2) + getCenter().x, -(height/2) + getCenter().y);
    }
};

int main() {
    Rectangle rect(100.0, 200.0);
    Trapezium trap(30.0, 100.0, 20.0, 40.0);
    RightTrapezium rtrap(10.0, 20.0, 60.0);
    
    cout << "BEFORE: \n\n";
    cout << rect << endl;
    cout << trap << endl;
    cout << rtrap <<endl;
    
    cout << "\nAFTER: \n\n" ;
    rect.rotate(90.0);
    rect.scale(3.5);
    rect.setColor(Color().green());
    
    trap.rotate(10.0);
    trap.mv(Point(10.0, -5.0));
    trap.scale(0.33);
    trap.setColor(Color(40.0, 5.0, 0.0));
    
    rtrap.rotate(-40.0);
    rtrap.mv(Point(12.0, -20.0));
    rtrap.setColor(Color().white());
    
    cout << rect << endl;
    cout << trap << endl;
    cout << rtrap <<endl;
    
    return 0;
}
