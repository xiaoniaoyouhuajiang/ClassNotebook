#include <ostream>

class Dot { // класс для координат
public:
	Dot(double x, double y) : x(x), y(y) {}
	Dot() : x(0), y(0) {}
	double x1() const;
	void set_x(double x);
	double y1() const;
	void set_y(double y);
	friend std::ostream& operator<<(std::ostream& s, const Dot& dot);
private:
	double x;
	double y;
};

class Color { // класс цветов
public:
	Color(const char r, const char g, const char b) : r_(r), g_(g), b_(b) {}
	int r1();
	void set_r(char r);
	int g1();
	void set_g(char g);
	int b1();
	void set_b(char b);
	int transform(char c);
	friend std::ostream& operator<<(std::ostream& s, const Color& color);
private:
	char r_;
	char g_;
	char b_;
};

class Shape {
public:
	void move(double x_new, double y_new); // перемещение 
	virtual void rotation(double angle) = 0; // поворот
	virtual void scaling (double k) = 0; // масштабирование
	Dot* dots1() const;
	void set_dots(Dot* dots);
	Color* color1() const;
	void set_color(Color* color);
protected:
	static int currentId;
	int id;
private:
	Dot* dots_ = nullptr;
	Color* color_ = nullptr;
};

class Circle : public Shape {
public:
	Circle(unsigned radius, Dot* center, Color* color);
	void rotation(double angle) override;
	void scaling (double k) override;
	friend std::ostream& operator<<(std::ostream& s, const Circle& circle);
private:
	unsigned int radius;
};

class Rectangle : public Shape {
public:
	Rectangle(double x, double y, unsigned int width, unsigned int  height, Color* color);
	void rotation(double angle) override;
	void scaling (double k) override;
	friend std::ostream& operator<<(std::ostream& s, const Rectangle& rectangle);
private:
	unsigned int height;
	unsigned int width;
};

class Trapezoid : public Shape {
public:
	Trapezoid(double shortX, double shortY, double longX, double longY,  unsigned short_width, unsigned long_width, Color* color);
	void rotation(double angle) override;
	void scaling (double k) override;
	friend std::ostream& operator<<(std::ostream& s, const Trapezoid& trapezoid);
private:
	unsigned int height;
};