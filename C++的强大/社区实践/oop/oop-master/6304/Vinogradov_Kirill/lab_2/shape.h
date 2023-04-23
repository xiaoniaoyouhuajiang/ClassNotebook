#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdint>
#include <vector>


struct point
{
	double x;
	double y;
};

class Shape
{
public:
	Shape(double ins_x, double ins_y)
	{
		scale = 1;
		cen.x = ins_x;
		cen.y = ins_y;
		angle = 0;
		colour = { 0, 0, 0 };
	}

	double getCenx()
	{
		return cen.x;
	}

	double getCeny()
	{
		return cen.y;
	}

	double toDeg(double rad)
	{
		return rad * 180 / M_PI;
	}

	double toRad(double deg)
	{
		return deg * M_PI / 180;
	}

	void setCenter(double ins_x, double ins_y)
	{
		for (auto& p : arr)
		{
			p.x += ins_x - cen.x;
			p.y += ins_y - cen.y;
		}

		this->cen.x = ins_x;
		this->cen.y = ins_y;
	}

	virtual void setAngle(double ins_angle)
	{
		if (ins_angle == 360 || ins_angle == 0)
			return;

		angle += ins_angle;
		angle = std::fmod(angle, 360);

		double temp_x;
		double rang = toRad(ins_angle);
		
		for (auto& p : arr)
		{
			temp_x = p.x;
			p.x = cen.x + (temp_x - cen.x)*cos(rang) - (p.y - cen.y)*sin(rang);
			p.y = cen.y + (temp_x - cen.x)*sin(rang) + (p.y - cen.y)*cos(rang);
		}
	}

	virtual void setScale(double ins_scale)
	{
		scale *= ins_scale;

		for (auto& p : arr)
		{
			p.x = (p.x - cen.x) * ins_scale + cen.x;
			p.y = (p.y - cen.y) * ins_scale + cen.y;
		}
	}

	void setColour(uint8_t r, uint8_t g, uint8_t b)
	{
		colour = { r, g, b };
	}

	virtual void shape_clear()
	{
		cen.x = cen.y = angle = 0;
		scale = 1;
		colour = { 0, 0, 0 };
		arr.clear();
	}

	virtual void print(std::ostream& out)
	{
		out << "Class: shape" << '\n';
		out << "Center: " << cen.x << ',' << cen.y << '\n';
		out << "Angle: " << angle << '\n';
		out << "Scale: " << scale << '\n';
		out << "RGB: " << colour << '\n';
		out << "Point number: " << arr.size() << '\n';

		for (auto p : arr)
			out << "x: " << p.x << " y: " << p.y << '\n';

		out << '\n';
	}

	friend std::ostream& operator<<(std::ostream& out, Shape& in)
	{
		in.print(out);
		return out;
	}

protected:

	struct RGB
	{
		uint8_t R;
		uint8_t G;
		uint8_t B;

		friend std::ostream& operator<<(std::ostream& out, RGB& in)
		{
			out << (unsigned int)in.R << ' ' << (unsigned int)in.G << ' ' << (unsigned int)in.B << '\n';
			return out;
		}

	} colour;

	point cen;
	double angle;
	double scale;
	std::vector<point> arr;
};

class Ellipse : public Shape
{
public:
	Ellipse(double ins_x, double ins_y, double ins_foc, double rad_sml, double rad_lrg)
		:Shape(ins_x, ins_y)
	{
		foc_rang = 2 * std::abs(ins_foc);

		l_foc.x = ins_x - std::abs(ins_foc);
		l_foc.y = ins_y;
		r_foc.x = ins_x + std::abs(ins_foc);
		r_foc.y = ins_y;

		point dot;

		//Left edge
		dot.x = cen.x - std::abs(rad_lrg);
		dot.y = cen.y;
		arr.push_back(dot);

		//Right edge
		dot.x = cen.x + std::abs(rad_lrg);
		dot.y = cen.y;
		arr.push_back(dot);

		//Top edge
		dot.x = cen.x;
		dot.y = cen.y + std::abs(rad_sml);
		arr.push_back(dot);

		//Bottom edge
		dot.x = cen.x;
		dot.y = cen.y - std::abs(rad_sml);
		arr.push_back(dot);
	}

	void print(std::ostream& out)
	{
		out << "Class: ellipse" << '\n';
		out << "Center: " << cen.x << ',' << cen.y << '\n';
		out << "Focus range: " << foc_rang << "\n";
		out << "Left focus: x: " << l_foc.x << " y: " << l_foc.y << '\n';
		out << "Right focus: x: " << r_foc.x << " y: " << r_foc.y << '\n';
		out << "Angle: " << angle << '\n';
		out << "Scale: " << scale << '\n';
		out << "RGB: " << colour << '\n';
		out << "Point number: " << arr.size() << '\n';

		for (auto p : arr)
			out << "x: " << p.x << " y: " << p.y << '\n';

		out << '\n';
	}

	void setAngle(double ins_angle)
	{
		if (ins_angle == 360 || ins_angle == 0)
			return;

		angle += ins_angle;
		angle = std::fmod(angle, 360);

		double temp_x;
		double rang = toRad(ins_angle);

		temp_x = l_foc.x;
		l_foc.x = cen.x + (temp_x - cen.x)*cos(rang) - (l_foc.y - cen.y)*sin(rang);
		l_foc.y = cen.y + (temp_x - cen.x)*cos(rang) + (l_foc.y - cen.y)*sin(rang);

		temp_x = r_foc.x;
		r_foc.x = cen.x + (temp_x - cen.x)*cos(rang) - (r_foc.y - cen.y)*sin(rang);
		r_foc.y = cen.y + (temp_x - cen.x)*cos(rang) + (r_foc.y - cen.y)*sin(rang);

		for (auto& p : arr)
		{
			temp_x = p.x;
			p.x = cen.x + (temp_x - cen.x)*cos(rang) - (p.y - cen.y)*sin(rang);
			p.y = cen.y + (temp_x - cen.x)*sin(rang) + (p.y - cen.y)*cos(rang);
		}
	}

	void setScale(double ins_scale)
	{
		scale *= ins_scale;

		foc_rang *= ins_scale;

		for (auto& p : arr)
		{
			p.x = (p.x - cen.x) * ins_scale + cen.x;
			p.y = (p.y - cen.y) * ins_scale + cen.y;
		}
	}

	void shape_clear()
	{
		cen.x = cen.y = l_foc.x = l_foc.y = r_foc.x = r_foc.y = angle = foc_rang = 0;
		scale = 1;
		colour = { 0, 0, 0 };
		arr.clear();
	}

protected:
	point l_foc;
	point r_foc;
	double foc_rang;
};

class Trap : public Shape
{
public:
	Trap(double ins_x, double ins_y, double height_length, double top_base_length, double bottom_base_length, double top_base_offset)
		: Shape(ins_x, ins_y), height(std::abs(height_length)), top_base(std::abs(top_base_length)), bot_base(std::abs(bottom_base_length)), offset(std::abs(top_base_offset))
	{

		point dot;

		//Top left
		dot.x = cen.x - top_base / 2 + top_base_offset;
		dot.y = cen.y + height / 2;
		arr.push_back(dot);

		//Top right
		dot.x = cen.x + top_base / 2 + top_base_offset;
		dot.y = cen.y + height / 2;
		arr.push_back(dot);

		//Bot left
		dot.x = cen.x - bot_base / 2;
		dot.y = cen.y - height / 2;
		arr.push_back(dot);

		//Bot right
		dot.x = cen.x + bot_base /2 ;
		dot.y = cen.y - height / 2;
		arr.push_back(dot);

	}

	void setScale(double ins_scale)
	{
		scale *= ins_scale;

		top_base *= ins_scale;
		bot_base *= ins_scale;
		height *= ins_scale;

		for (auto& p : arr)
		{
			p.x = (p.x - cen.x) * ins_scale + cen.x;
			p.y = (p.y - cen.y) * ins_scale + cen.y;
		}
	}

	void print(std::ostream& out)
	{
		out << "Class: trapezium" << '\n';
		out << "Center: " << cen.x << ',' << cen.y << '\n';
		out << "Top base length: " << top_base << '\n';
		out << "Bot base length: " << bot_base << '\n';
		out << "Height length: " << height << '\n';
		out << "Angle: " << angle << '\n';
		out << "Scale: " << scale << '\n';
		out << "RGB: " << colour << '\n';
		out << "Point number: " << arr.size() << '\n';

		for (auto p : arr)
			out << "x: " << p.x << " y: " << p.y << '\n';

		out << '\n';
	}

	void shape_clear()
	{
		cen.x = cen.y = angle = top_base = bot_base = height = 0;
		scale = 1;
		colour = { 0, 0, 0 };
		arr.clear();
	}

protected:
	double top_base;
	double bot_base;
	double height;
	double offset;
};
