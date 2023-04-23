#include "RegPentagon.hpp"

double RegPentagon::getDotsRadius() const
{
	return R;
}

void RegPentagon::setDotsRadius(double newR)
{
	R = newR;
}

void RegPentagon::print() const
{
	std::cout << "Reg pentagon object with ID " << getID() << std::endl;
	std::cout << "It's position: " << Pos.x << " " << Pos.y << " " << Pos.z << std::endl;
	std::cout << "It's color: " << Color.x << " " << Color.y << " " << Color.z << " " << std::endl;
	std::cout << "It's angle: " << Angle << std::endl;
	std::cout << "It's radius: " << R << std::endl;
}

void RegPentagon::scale(double sc)
{
	R *= sc;
}
