// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <conio.h>

class Shapes
{
protected:
	static int count;
	int color;
	float left_x, left_y, right_x, right_y;
	Shapes() { count++; }

public:
	virtual ~Shapes() { count--; }

	static int GetCount() { return count; }
	virtual void Print() = 0;
	void Draw(int new_color = 0) { color = new_color; }
	virtual void Move(float new_x, float new_y) = 0;
	virtual void Scale(float k) = 0;
	virtual void Turn(float angle) = 0;
};

class Pentagon : public Shapes
{
private:
	float coordinates[5][2];
public:

	void Print() {
		for (int i = 0; i < 5; i++)
		{
			std::cout << "coordinates of angle: " << coordinates[i][0] << ' ' << coordinates[i][1] << std::endl;
		}
		std::cout << "coordinates of the opper-left corner: " << left_x << ' ' << left_y << std::endl;//вверхнего левого угла
		std::cout << "coordinates of the bottom right corner: " << right_x << ' ' << right_y << std::endl;//нижнего правого угла
		std::cout << "color: " << color << std::endl;
	}

	Pentagon(float(&coord)[5][2], int c = 0)
	{
		float x1 = coord[0][0], x2 = coord[0][0],
			y1 = coord[0][1], y2 = coord[0][1];
		for (int i = 0; i<5; i++)
		{
			coordinates[i][0] = coord[i][0]; coordinates[i][1] = coord[i][1];
			if (x1>coord[i][0]) x1 = coord[i][0];
			if (x2<coord[i][0]) x2 = coord[i][0];
			if (y1<coord[i][1]) y1 = coord[i][1];
			if (y2>coord[i][1]) y2 = coord[i][1];
		}
		left_x = x1; left_y = y1;
		right_x = x2; right_y = y2;
		color = c;
	}

	~Pentagon() { }

	void Move(float new_x, float new_y)
	{
		for (int i = 4; i>0; i--)
		{
			coordinates[i][0] = new_x + (coordinates[i][0] - coordinates[0][0]);
			coordinates[i][1] = new_y + (coordinates[i][1] - coordinates[0][1]);
		}

		if ((left_x == coordinates[0][0]) && (left_y == coordinates[0][1])) { left_x = new_x; left_y = new_y; }
		else { left_x = new_x + (left_x - coordinates[0][0]); left_y = new_y + (left_y - coordinates[0][1]); }

		if ((right_x == coordinates[0][0]) && (right_y == coordinates[0][1])) { right_x = new_x; right_y = new_y; }
		else { right_x = new_x + (right_x - coordinates[0][0]); right_y = new_y + (right_y - coordinates[0][1]); }

		coordinates[0][0] = new_x; coordinates[0][1] = new_y;
	}

	void Scale(float k)
	{
		for (int i = 4; i>0; i--)
		{
			coordinates[i][0] = coordinates[i][0] * k;
			coordinates[i][1] = coordinates[i][1] * k;
		}

		if ((left_x == coordinates[0][0]) && (left_y != coordinates[0][1])) { left_y = left_y * k; }
		if ((left_x != coordinates[0][0]) && (left_y == coordinates[0][1])) { left_x = left_x * k; }
		if ((left_x != coordinates[0][0]) && (left_y != coordinates[0][1])) { left_x = left_x * k; left_y = left_y * k; }

		if ((right_x == coordinates[0][0]) && (right_y != coordinates[0][1])) { right_y = right_y * k; }
		if ((right_x != coordinates[0][0]) && (right_y == coordinates[0][1])) { right_x = right_x * k; }
		if ((right_x != coordinates[0][0]) && (right_y != coordinates[0][1])) { right_x = right_x * k; right_y = right_y * k; }

	}

	void Turn(float angle)
	{
		float x, y;

		for (int i = 4; i>0; i--)
		{
			x = coordinates[i][0] * cos(angle) + coordinates[i][1] * sin(angle);
			y = -coordinates[i][0] * sin(angle) + coordinates[i][1] * cos(angle);
			coordinates[i][0] = x; coordinates[i][1] = y;
		}

		x = left_x*cos(angle) + left_y*sin(angle);
		y = -left_x*sin(angle) + left_y*cos(angle);
		left_x = x; left_y = y;

		x = right_x*cos(angle) + right_y*sin(angle);
		y = -right_x*sin(angle) + right_y*cos(angle);
		right_x = x; right_y = y;
	}
};

class Pentagram : public Shapes
{
private:
	float coordinates[5][2];
public:

	void Print() {
		for (int i = 0; i < 5; i++)
		{
		std::cout << "coordinates of angle: " << coordinates[i][0] << ' ' << coordinates[i][1] << std::endl;
	}
	std::cout << "coordinates of the opper-left corner: " << left_x << ' ' << left_y << std::endl;
	std::cout << "coordinates of the bottom right corner: " << right_x << ' ' << right_y << std::endl;
	std::cout << "color: " << color << std::endl;
	}

	Pentagram(float(&coord)[5][2], int c = 0)
	{
		float x1 = coord[0][0], x2 = coord[0][0],
			y1 = coord[0][1], y2 = coord[0][1];
		for (int i = 0; i<5; i++)
		{
			coordinates[i][0] = coord[i][0]; coordinates[i][1] = coord[i][1];
			if (x1>coord[i][0]) x1 = coord[i][0];
			if (x2<coord[i][0]) x2 = coord[i][0];
			if (y1<coord[i][1]) y1 = coord[i][1];
			if (y2>coord[i][1]) y2 = coord[i][1];
		}
		left_x = x1; left_y = y1;
		right_x = x2; right_y = y2;
		color = c;
	}

	~Pentagram() { }

	void Move(float new_x, float new_y)
	{
		for (int i = 4; i>0; i--)
		{
			coordinates[i][0] = new_x + (coordinates[i][0] - coordinates[0][0]);
			coordinates[i][1] = new_y + (coordinates[i][1] - coordinates[0][1]);
		}

		if ((left_x == coordinates[0][0]) && (left_y == coordinates[0][1])) { left_x = new_x; left_y = new_y; }
		else { left_x = new_x + (left_x - coordinates[0][0]); left_y = new_y + (left_y - coordinates[0][1]); }

		if ((right_x == coordinates[0][0]) && (right_y == coordinates[0][1])) { right_x = new_x; right_y = new_y; }
		else { right_x = new_x + (right_x - coordinates[0][0]); right_y = new_y + (right_y - coordinates[0][1]); }

		coordinates[0][0] = new_x; coordinates[0][1] = new_y;
	}

	void Scale(float k)
	{
		for (int i = 4; i>0; i--)
		{
			coordinates[i][0] = coordinates[i][0] * k;
			coordinates[i][1] = coordinates[i][1] * k;
		}

		if ((left_x == coordinates[0][0]) && (left_y != coordinates[0][1])) { left_y = left_y * k; }
		if ((left_x != coordinates[0][0]) && (left_y == coordinates[0][1])) { left_x = left_x * k; }
		if ((left_x != coordinates[0][0]) && (left_y != coordinates[0][1])) { left_x = left_x * k; left_y = left_y * k; }

		if ((right_x == coordinates[0][0]) && (right_y != coordinates[0][1])) { right_y = right_y * k; }
		if ((right_x != coordinates[0][0]) && (right_y == coordinates[0][1])) { right_x = right_x * k; }
		if ((right_x != coordinates[0][0]) && (right_y != coordinates[0][1])) { right_x = right_x * k; right_y = right_y * k; }

	}

	void Turn(float angle)
	{
		float x, y;

		for (int i = 4; i>0; i--)
		{
			x = coordinates[i][0] * cos(angle) + coordinates[i][1] * sin(angle);
			y = -coordinates[i][0] * sin(angle) + coordinates[i][1] * cos(angle);
			coordinates[i][0] = x; coordinates[i][1] = y;
		}

		x = left_x*cos(angle) + left_y*sin(angle);
		y = -left_x*sin(angle) + left_y*cos(angle);
		left_x = x; left_y = y;

		x = right_x*cos(angle) + right_y*sin(angle);
		y = -right_x*sin(angle) + right_y*cos(angle);
		right_x = x; right_y = y;
	}
};

class Rectangle : public Shapes
{
private:
	float coordinates[4][2];
public:

	void Print() {
		for (int i = 0; i < 4; i++)
		{
		std::cout << "coordinates of angle: " << coordinates[i][0] << ' ' << coordinates[i][1] << std::endl;
	}
	std::cout << "coordinates of the opper-left corner: " << left_x << ' ' << left_y << std::endl;
	std::cout << "coordinates of the bottom right corner: " << right_x << ' ' << right_y << std::endl;
	std::cout << "color: " << color << std::endl;
	}

	Rectangle(float(&coord)[4][2], int c = 0)
	{
		float x1 = coord[0][0], x2 = coord[0][0],
			y1 = coord[0][1], y2 = coord[0][1];
		for (int i = 0; i<4; i++)
		{
			coordinates[i][0] = coord[i][0]; coordinates[i][1] = coord[i][1];
			if (x1>coord[i][0]) x1 = coord[i][0];
			if (x2<coord[i][0]) x2 = coord[i][0];
			if (y1<coord[i][1]) y1 = coord[i][1];
			if (y2>coord[i][1]) y2 = coord[i][1];
		}
		left_x = x1; left_y = y1;
		right_x = x2; right_y = y2;
		color = c;
	}

	~Rectangle() { }

	void Move(float new_x, float new_y)
	{
		for (int i = 4; i>0; i--)
		{
			coordinates[i][0] = new_x + (coordinates[i][0] - coordinates[0][0]);
			coordinates[i][1] = new_y + (coordinates[i][1] - coordinates[0][1]);
		}

		if ((left_x == coordinates[0][0]) && (left_y == coordinates[0][1])) { left_x = new_x; left_y = new_y; }
		else { left_x = new_x + (left_x - coordinates[0][0]); left_y = new_y + (left_y - coordinates[0][1]); }

		if ((right_x == coordinates[0][0]) && (right_y == coordinates[0][1])) { right_x = new_x; right_y = new_y; }
		else { right_x = new_x + (right_x - coordinates[0][0]); right_y = new_y + (right_y - coordinates[0][1]); }

		coordinates[0][0] = new_x; coordinates[0][1] = new_y;
	}

	void Scale(float k)
	{
		for (int i = 3; i>0; i--)
		{
			coordinates[i][0] = coordinates[i][0] * k;
			coordinates[i][1] = coordinates[i][1] * k;
		}

		if ((left_x == coordinates[0][0]) && (left_y != coordinates[0][1])) { left_y = left_y * k; }
		if ((left_x != coordinates[0][0]) && (left_y == coordinates[0][1])) { left_x = left_x * k; }
		if ((left_x != coordinates[0][0]) && (left_y != coordinates[0][1])) { left_x = left_x * k; left_y = left_y * k; }

		if ((right_x == coordinates[0][0]) && (right_y != coordinates[0][1])) { right_y = right_y * k; }
		if ((right_x != coordinates[0][0]) && (right_y == coordinates[0][1])) { right_x = right_x * k; }
		if ((right_x != coordinates[0][0]) && (right_y != coordinates[0][1])) { right_x = right_x * k; right_y = right_y * k; }

	}

	void Turn(float angle)
	{
		float x, y;

		for (int i = 3; i>0; i--)
		{
			x = coordinates[i][0] * cos(angle) + coordinates[i][1] * sin(angle);
			y = -coordinates[i][0] * sin(angle) + coordinates[i][1] * cos(angle);
			coordinates[i][0] = x; coordinates[i][1] = y;
		}

		x = left_x*cos(angle) + left_y*sin(angle);
		y = -left_x*sin(angle) + left_y*cos(angle);
		left_x = x; left_y = y;

		x = right_x*cos(angle) + right_y*sin(angle);
		y = -right_x*sin(angle) + right_y*cos(angle);
		right_x = x; right_y = y;
	}
};

int Shapes::count = 0;

int main()
{

	Shapes* shapes[10];                                              // Т.к. класс Shapes является абстрактным,
	float coordinates[5][2];
	coordinates[0][0] = 0; coordinates[0][1] = 0;
	coordinates[1][0] = 0; coordinates[1][1] = 3;
	coordinates[2][0] = 2; coordinates[2][1] = 5;
	coordinates[3][0] = 4; coordinates[3][1] = 3;
	coordinates[4][0] = 4; coordinates[4][1] = 0;

	float coordinates2[5][2];
	coordinates2[0][0] = 0; coordinates2[0][1] = 0;
	coordinates2[1][0] = 0; coordinates2[1][1] = 3;
	coordinates2[2][0] = 2; coordinates2[2][1] = 5;
	coordinates2[3][0] = 4; coordinates2[3][1] = 3;
	coordinates2[4][0] = 4; coordinates2[4][1] = 0;

	float coordinates1[4][2];
	coordinates1[0][0] = 0; coordinates1[0][1] = 0;
	coordinates1[1][0] = 0; coordinates1[1][1] = 3;
	coordinates1[2][0] = 2; coordinates1[2][1] = 5;
	coordinates1[3][0] = 4; coordinates1[3][1] = 3;
	// можно объявить массив указателей, но не массив фигур	
	shapes[0] = new Pentagon(coordinates, 1);
	shapes[1] = new Rectangle(coordinates1, 1);
	shapes[2] = new Pentagram(coordinates2, 1);

	for (int i = 0; i < Shapes::GetCount(); i++)
	{
		shapes[i]->Print();
		shapes[i]->Draw(i + 1);
		shapes[i]->Move(5, 5);
		std::cout << "Move" << std::endl; shapes[i]->Print();
		shapes[i]->Scale(2);
		std::cout << "Scale" << std::endl; shapes[i]->Print();
		shapes[i]->Turn(0.524);
		std::cout << "Turn" << std::endl; shapes[i]->Print();
		std::cout << std::endl;
		std::cout << std::endl;

	}

	_getch();
	return 0;
}


