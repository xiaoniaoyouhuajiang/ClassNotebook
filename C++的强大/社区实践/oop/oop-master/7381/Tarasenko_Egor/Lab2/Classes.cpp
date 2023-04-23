#include <iostream>
#include <string>

class Color {
protected:
    int r, g, b;
public:
    Color() : r(0), g(0), b(0) { }
    void SetColor(unsigned int r_, unsigned int g_, unsigned int b_) {
		if (r_ > 255) r_ = 255;
		if (g_ > 255) g_ = 255;
		if (b_ > 255) b_ = 255;
		r = r_;
		g = g_;
		b = b_;
	}
	std::string GetColor() {
	    std::string color;
	    color += (std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b) + ";\n");
	    return color;
	}
};

class Points {
protected:
    int curr_x, curr_y;
    int count_of_points;
    int* x_arr = new int [10];
	int* y_arr = new int [10];
public:
    Points() : curr_x(0), curr_y(0), count_of_points(0) { }
    Points(int x_, int y_, const int count) {
        curr_x = x_;                // current_point;
		curr_y = y_;
		count_of_points = count;    // a number of shape vertexes;
		
		//x_arr = new int [count];       // arraies with vertex cordinates;
		//y_arr = new int [count];
    }
    ~Points() {
        if (count_of_points > 0) {
            delete [] x_arr;
            delete [] y_arr;
        }
    }
    
    void SetPoint(int x_, int y_) {
		curr_x = x_;
		curr_y = y_;
	}
	void SetScale(float scale) {
		if (scale > 0.0)
			for (int i = 0; i < count_of_points; i++) {
				x_arr[i] = (int)(x_arr[i] * scale);
				y_arr[i] = (int)(y_arr[i] * scale);
			}
	}
};

class Shape : public Color, public Points {
protected:
	int angle;

	// initialization;
	char type;
	int number;

public:
	virtual void SetID(int n) = 0;
	std::string GetID() {
		std::string str;
		str += type;
		str += std::to_string(number);
		return str;
	}
	friend std::ostream& operator << (std::ostream& out, const Shape& c) {
		return out << "ID:" << c.type << c.number << std::endl;
	}

	void SetAngle(int ang) {
		angle = ang;
	}

	Shape() {
		angle = 0;
	}
};

class Square : public Shape {
public:
	Square() {
	    Points(0, 0, 4);
		x_arr[0] = 0;
		y_arr[0] = 1;
		x_arr[1] = 1;
		y_arr[1] = 1;
		x_arr[2] = 0;
		y_arr[2] = 0;
		x_arr[3] = 1;
		y_arr[3] = 0;
	}
	Square(int x_left_up, int y_left_up, int size) {
	    Points(0, 0, 4);
	    std::cout << "" << std::endl;
		x_arr[0] = x_left_up;		    // left_up;
		y_arr[0] = y_left_up;
		x_arr[1] = x_left_up + size;	// right_up;
		y_arr[1] = y_left_up;
		x_arr[2] = x_left_up;		    // left_down;
		y_arr[2] = y_left_up - size;
		x_arr[3] = x_left_up + size;	// right_down;
		y_arr[3] = y_left_up - size;
	}
	void SetID(int n) {
		type = 's';
		number = n;
	}
	friend std::ostream& operator << (std::ostream& out, const Square& c) {
		return out << "ID:" << c.type << c.number << std::endl << "Points: (" <<
			c.x_arr[0] << ", " << c.y_arr[0] << "); (" << c.x_arr[1] << ", " << c.y_arr[1] << "); (" <<
			c.x_arr[2] << ", " << c.y_arr[2] << "); (" << c.x_arr[3] << ", " << c.y_arr[3] << ")" << std::endl;
	}
};

class Allipse : public Shape {
private:
	int a_range, b_range;
public:
	Allipse() : a_range(1), b_range(1) {
	    Points(0, 0, 1);
		x_arr[0] = 0;
		y_arr[0] = 0;
	}
	Allipse(int x_, int y_, int a, int b) : a_range(a), b_range(b) {
	    Points(0, 0, 1);
		x_arr[0] = x_;
		y_arr[0] = y_;
	}
	void SetID(int n) {
		type = 'a';
		number = n;
	}
	friend std::ostream& operator << (std::ostream& out, const Allipse& c) {
		return out << "ID:" << c.type << c.number << std::endl << "Center: (" << c.x_arr[0] << ", " << c.y_arr[0] <<
			"); HorizontalRadius: " << c.a_range << "; VerticalRadius: " << c.b_range << std::endl;
	}
};

class Rhombus : public Shape {
public:
	Rhombus() {
	    Points(0, 0, 4);
		x_arr[0] = 0;
		y_arr[0] = 1;
		x_arr[1] = -1;
		y_arr[1] = 0;
		x_arr[2] = 1;
		y_arr[2] = 0;
		x_arr[3] = 0;
		y_arr[3] = -1;
	}
	Rhombus(int x_upper, int y_upper, int x_left, int y_left) {
	    Points(0, 0, 4);
		x_arr[0] = x_upper;				            // up;
		y_arr[0] = y_upper;
		x_arr[1] = x_left;				            // left;
		y_arr[1] = y_left;
		x_arr[2] = x_left + 2 * (x_upper - x_left);	// right;
		y_arr[2] = y_left;
		x_arr[3] = x_upper;				            // down;
		y_arr[3] = y_upper - 2 * (y_upper - y_left);
	}
	void SetID(int n) {
		type = 'r';
		number = n;
	}
	friend std::ostream& operator << (std::ostream& out, const Rhombus& c) {
		return out << "ID:" << c.type << c.number << std::endl << "Points: (" <<
			c.x_arr[0] << ", " << c.y_arr[0] << "); (" << c.x_arr[1] << ", " << c.y_arr[1] << "); (" <<
			c.x_arr[2] << ", " << c.y_arr[2] << "); (" << c.x_arr[3] << ", " << c.y_arr[3] << ")" << std::endl;
	}
};

void Test(int count_of_squares, int count_of_allipses, int count_of_rhombuses) {
    static int num_sq = 1, num_all = 1, num_rh = 1;
    
    for(int i = 0; i < count_of_squares; i++){
        Square sq(0, 10, 10);
        sq.SetID(num_sq++);
        std::cout << sq;
    }
    for(int i = 0; i < count_of_allipses; i++){
        Allipse all(0, 0, 10, 3);
        all.SetID(num_all++);
        std::cout << all;
    }
    for(int i = 0; i < count_of_rhombuses; i++){
        Rhombus rh(0, 10, -5, 0);
        rh.SetID(num_rh++);
        std::cout << rh;
    }
}

int main() {
    Test(1, 1, 1);
	return 0;
} 