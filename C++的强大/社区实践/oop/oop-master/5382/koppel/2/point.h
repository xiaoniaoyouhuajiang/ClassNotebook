#ifndef POINT_H
#define POINT_H

template <typename T>
bool float_comparison(T f1, T f2) {
	return (fabs(f1 - f2) <= std::numeric_limits<T>::epsilon());
}

class Point {
public:

	double x;
	double y;
	Point();
	Point(double x, double y);
	bool distance(const Point &smth) const; 
	friend bool operator == (const Point& first, const Point& second) {
		return ((float_comparison(first.x, second.x)) && (float_comparison(first.y, second.y)));
	}

	friend bool operator< (const Point& first, const Point& second) {
		if (float_comparison(first.x, second.x))
			return (first.y < second.y);
		else
			return (first.x < second.x);
	}

	friend bool operator<= (const Point& first, const Point& second) {
		return ((first < second) || (first == second));
	}

};

#endif 