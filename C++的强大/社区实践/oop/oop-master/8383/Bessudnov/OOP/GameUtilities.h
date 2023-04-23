#pragma once
#include <iostream>

#define UNIT_L_BEE 'A'
#define UNIT_D_FLY 'B'
#define UNIT_L_FLOWER 'C'
#define UNIT_D_COAL 'D'
#define UNIT_L_SPRINKLER 'E'
#define UNIT_D_COLLECTOR 'F'

#define FIELD_MAX_SIZE 50
#define FIELD_MIN_SIZE 10

class Vector2D {
public:
	int x;
	int y;

	Vector2D(const Vector2D &vec) : x(vec.x), y(vec.y){}
	Vector2D(int x, int y) : x(x), y(y) {}
	Vector2D() : x(0), y(0) {}

	Vector2D &operator=(const Vector2D &vec) {
		if (&vec == this) return *this;

		x = vec.x;
		y = vec.y;

		return *this;
	}

	Vector2D operator+(const Vector2D &vec) {
		Vector2D newVec;

		newVec.x = vec.x + x;
		newVec.y = vec.y + y;

		return Vector2D(vec.x + x, vec.y + y);
	}

	friend Vector2D& operator+=(Vector2D& left, const Vector2D& right) {
		left.x += right.x;
		left.y += right.y;
		return left;
	}

	friend Vector2D &operator*(Vector2D &vec, const int mult) {
		vec.x *= mult;
		vec.y *= mult;

		return vec;
	}

	int operator==(const Vector2D &vec) {
		if (x == vec.x && y == vec.y) return 1;

		return 0;
	}

	friend std::ostream &operator<<(std::ostream &os, const Vector2D &location) {
		os << location.x << " " << location.y;
		return os;
	}

	friend std::istream &operator>>(std::istream &is, Vector2D &location) {
		is >> location.x;
		is >> location.y;
		return is;
	}
};


class GameUtilities {
public:
	static void clamp(int &value, int max, int min);
	static void clamp(Vector2D &value, int max, int min);
	static void clamp(Vector2D &value, Vector2D max, Vector2D min);
	GameUtilities();
	~GameUtilities();
};
