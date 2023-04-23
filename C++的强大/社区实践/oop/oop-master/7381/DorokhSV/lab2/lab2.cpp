#include <iostream>

class Shape {
    protected:
        double _x;
        double _y;
        double _angle;
        int _r;
        int _g;
        int _b;
        int _ID;
        static int nextID;
    public:

    Shape(double x = 0, double y = 0, double angle = 0) : _x(x), _y(y), _angle(angle), _ID(++nextID) {
        _r = _g = _b = 0;
    }

    virtual ~Shape() {}

    void move(double new_x, double new_y) {
        _x = new_x;
        _y = new_y;
    }

    void setColor(int r, int g, int b) {
        _r = r;
        _g = g;
        _b = b;
    }
    void getColor(int &r, int &g, int&b) {
        r = _r;
        g = _g;
        b = _b;
    }

    virtual void rotate(double angle) = 0;
    virtual void scale(int zoom) = 0;

    friend std::ostream & operator<<(std::ostream &out, const Shape &figure) {
		out << "Coordinates of the center: (" << figure._x << ", " << figure._y << ")" << std::endl;
        out << "Angle: " << figure._angle << std::endl;
        out << "ID <" << figure._ID << ">" << std::endl;
        out << "Color: red-" << figure._r << " green-" << figure._g << " blue-" << figure._b << std::endl;
		return out;
	}
};
int Shape::nextID = 0;

class Circle : public Shape {
    protected:
        double _radius;
    public:

        Circle(double x = 0, double y = 0, double angle = 0, double radius = 0) : Shape(x, y, angle), _radius(radius) {}

        ~Circle() {}

        void scale(int zoom) override {
             _radius *= zoom;
        }

        void rotate(double angle) override {
            _angle += angle;
        }

        friend std::ostream & operator<< (std::ostream &out, Circle &figure) {
            out << "\tCIRCLE" << std::endl;
            out << (Shape&) figure << std::endl;
            out << "Radius: " << figure._radius;
		    return out;
	    }

};

class CircleSeg : public Circle {
    protected:
        double _firstSegAngle;
        double _secondSegAngle;
    public:
        CircleSeg(double firstAng, double secondAng, double radius = 0, double x = 0, double y = 0, double angle = 0) 
        : Circle( x, y, angle, radius), _firstSegAngle(firstAng), _secondSegAngle(secondAng) {}
        ~CircleSeg() {}

        friend std::ostream & operator << (std::ostream &out, const CircleSeg &figure) {
            out << "\tSEGMENT" << std::endl;
            out << (Circle&) figure << std::endl;
            out << "Segment angle: " << figure._firstSegAngle - figure._secondSegAngle << std::endl; 
            return out;
	    }
};

class Trapeze : public Shape {
    protected:
        double _topSide;
        double _bottomSide;
        double _height;
        double _x_tsm;
        double _y_tsm;
        double _x_bsm;
        double _y_bsm;
    
    public:
    
    Trapeze(double top, double bottom, double x_tsm, double y_tsm, double x_bsm, double y_bsm, double x = 0, double y = 0, double angle = 0)
     : Shape(x, y, angle),
     _topSide(top), _bottomSide(bottom),
     _x_tsm(x_tsm), _y_tsm(y_tsm),
     _x_bsm(x_bsm), _y_bsm(y_bsm) {
         _height = _y_tsm - _y_bsm;
         _y = _height / 2;
         _x = (_topSide + _bottomSide) / 4;
     }

     ~Trapeze() {}

     void scale(int zoom) override {
             _topSide *= zoom;
             _bottomSide *= zoom;
             _height *= zoom;
             _x_tsm *= zoom;
             _y_tsm *= zoom;
             _x_bsm *= zoom;
             _y_bsm *= zoom;
    }

    void rotate(double angle) override {
            _angle += angle;
    }

    friend std::ostream & operator << (std::ostream &out, const Trapeze &figure) {
        out << "\tTRAPEZE" << std::endl;
        out << (Shape&) figure << std::endl;
        out << "Side length: top-" << figure._topSide << " bottom-" << figure._bottomSide << std::endl; 
        out << "Height: " << figure._height << std::endl;
        return out;
	}


};

int main() {
    Circle A(5,5,20,15);
    CircleSeg B(48, 20, 13);
    Trapeze C(13, 27, 15, 7, 9, 3);
	std::cout << A << std::endl;
    std::cout << B << std::endl;
    std::cout << C << std::endl;
    A.rotate(35);
    A.scale(3);
    A.setColor(255, 128, 0);
    B.rotate(77);
    B.scale(5);
    B.setColor(15,15,15);
    B.move(2,4);
    C.rotate(3);
    C.scale(7);
    C.setColor(33,5,7);
    std::cout << A << std::endl;
    std::cout << B << std::endl;
    std::cout << C << std::endl;
}