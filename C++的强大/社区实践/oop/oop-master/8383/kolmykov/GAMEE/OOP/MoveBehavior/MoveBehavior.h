#pragma once
#include <memory>


class Unit;


class MoveBehavior
{
public:
	MoveBehavior();
	MoveBehavior(const MoveBehavior& other);
	virtual ~MoveBehavior();
	virtual void move(std::shared_ptr<Unit> unit);
};

