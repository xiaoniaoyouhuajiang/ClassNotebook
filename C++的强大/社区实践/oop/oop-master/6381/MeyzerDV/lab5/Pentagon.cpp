#include "Pentagon.hpp"

void Pentagon::print() const
{
	std::cout << "Pentagon object with ID " << getID() << std::endl;
	std::cout << "It's position: " << Pos.x << " " << Pos.y << " " << Pos.z << std::endl;
	std::cout << "It's color: " << Color.x << " " << Color.y << " " << Color.z << " " << std::endl;
	std::cout << "It's angle: " << Angle << std::endl;
	std::cout << "It's points relative to the position of figure in polar(first is angle): " << std::endl;
	std::cout << "(" << A.x << ", "<< R.x << ")" << ", "
			<< "(" << A.y << ", "<< R.y << ")" << ", "
			<< "(" << A.z << ", "<< R.z << ")" << ", "
			<< "(" << A.w << ", "<< R.w << ")" << ", "
			<< "(" << A.t << ", "<< R.t << ")" << std::endl;
}

void Pentagon::scale(double sc)
{
	R.x*=sc;
	R.y*=sc;
	R.z*=sc;
	R.w*=sc;
	R.t*=sc;
}

const V5d& Pentagon::getDotsRadius() const
{
	return R;
}

const V5d& Pentagon::getDotsAngle() const
{
	return A;
}

void Pentagon::setDotsRadius(const V5d& newR)
{
	R = newR;
}
void Pentagon::setDotsAngle(const V5d& newA)
{
	A = newA;
	while (A.x < 0) A.x += 360;
	while (A.y < 0) A.y += 360;
	while (A.z < 0) A.z += 360;
	while (A.w < 0) A.w += 360;
	while (A.t < 0) A.t += 360;
	while (A.x >= 360) A.x -= 360;
	while (A.y >= 360) A.y -= 360;
	while (A.z >= 360) A.z -= 360;
	while (A.w >= 360) A.w -= 360;
	while (A.t >= 360) A.t -= 360;
}
