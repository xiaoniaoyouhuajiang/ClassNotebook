#include "Handler.h"



Handler::Handler(std::shared_ptr<Field> field){
	this->field = field;
}


Handler::~Handler()
{
}

void Handler::handle(std::shared_ptr<Request> request)
{
}

void Handler::setNextHandler(std::shared_ptr<Handler> nextHandler) {
	this->nextHandler = nextHandler;
}

std::shared_ptr<Handler> Handler::getNextHandler()
{
	return nextHandler;
}
