#include "Trapezium.h"
#pragma once

class EqualTrapezium : public Trapezium //Равнобедренная трапеция
{
public:
    void check();
	EqualTrapezium();
	EqualTrapezium(double lengthBottom, double lengthTop, double hight);
	//void Area();
	~EqualTrapezium();
	double static compareAreas(EqualTrapezium etrap1, EqualTrapezium etrap2);
};