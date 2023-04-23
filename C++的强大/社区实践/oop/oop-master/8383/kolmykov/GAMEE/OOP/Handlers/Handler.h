#pragma once
#include "Request.h"
#include "Field.h"


class Handler
{
protected:
	std::shared_ptr<Field> field;
	std::shared_ptr<Handler> nextHandler;
public:
	Handler(std::shared_ptr<Field> field);
	~Handler();
	virtual void handle(std::shared_ptr<Request> request);
	void setNextHandler(std::shared_ptr<Handler> nextHandler);
	std::shared_ptr<Handler> getNextHandler();
};

