#ifndef FIGURES_H
#define FIGURES_H

#include "shape.hpp"
	class Pentagon : public Shape {
	public:

		Pentagon(double x = 0, double y = 0, int SideSize = 0);

		void ChangeCoordinates(double new_x, double new_y) override;

		void Rotate(double new_angle) override;

		void Scale(double factor) override;

		void SetColour(int r, int g, int b) override;

		Colour GetColour() override;

		int GetSide();

		Point GetCenter() const override;

		virtual void SetPerimetr() override;

		double GetPerimetr() const override;

		ostream& operator<<(ostream & stream) const override;
	private:
		int side;
	};

	class Pentagram : public Shape {
	public:

		Pentagram(double x = 0, double y = 0, double Radius = 0);

		void ChangeCoordinates(double new_x, double new_y) override;

		void Rotate(double new_angle) override;

		void Scale(double factor) override;

		void SetColour(int r, int g, int b) override;

		Colour GetColour() override;

		double GetRadius();

		Point GetCenter() const override;

		virtual void SetPerimetr() override;

		double GetPerimetr() const override;

		ostream& operator<<(ostream & stream) const override;

	protected:

		double radius;

	};

	class Rectangle : public Shape {
	public:

		Rectangle(double x = 0, double y = 0, double _length = 0, double _width = 0);

		void ChangeCoordinates(double new_x, double new_y) override;

		void Rotate(double new_angle) override;

		void Scale(double factor) override;

		void SetColour(int r, int g, int b) override;

		Colour GetColour() override;

		double GetLength();

		double GetWidth();

		Point GetCenter() const override;

		virtual void SetPerimetr() override;

		double GetPerimetr() const override;

		ostream& operator<<(ostream & stream) const override;

	protected:

		double length;
		double width;

	};

#endif //FIGURES_H