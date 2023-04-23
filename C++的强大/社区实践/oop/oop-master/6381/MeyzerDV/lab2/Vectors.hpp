#pragma once

class V3d
{
public:
	double x, y, z;
	V3d() : x(0), y(0), z(0)
	{ }
	V3d(double x, double y, double z = 0) : x(x), y(y), z(z)
	{ }
};

class V5d
{
public:
	double x, y, z, w, t;
	V5d() : x(0), y(0), z(0), w(0), t(0)
	{ }
	V5d(double x, double y, double z, double w, double t) : x(x), y(y), z(z), w(w), t(t)
	{ }
};

class V3i
{
public:
	int x, y, z;
	V3i() : x(0), y(0), z(0)
	{ }
	V3i(int x, int y, int z = 0) : x(x), y(y), z(z)
	{ }
};
