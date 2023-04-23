#pragma once

#include <functional>

#include "vector.h"
#include "sharedptr.hpp"
#include "shape.hpp"
#include "Circle.hpp"
#include "Pentagon.hpp"
#include "RegularPentagon.hpp"


void change(rabid::vector < rabid::shared_ptr< Shape > > &sourcev,
	const rabid::shared_ptr< Shape > &rep,
	std::function< bool(const Shape&)> pred)
{
	/*for (int n = 0; n < sourcev.size(); n++)
	{
	if (pred(*sourcev[n])) sourcev[n] = rep;
	}*/

	for (auto& i : sourcev)
	{
		if (pred(*i)) i = rep;
	};

	return;
};

rabid::shared_ptr< Shape > findShape(rabid::vector < rabid::shared_ptr< Shape > > sourcev,
	std::function< bool(const Shape&)> pred)
{
	for (auto& i : sourcev)
	{

		if (pred(*i)) return i;
	};
	throw std::exception("not found");
};