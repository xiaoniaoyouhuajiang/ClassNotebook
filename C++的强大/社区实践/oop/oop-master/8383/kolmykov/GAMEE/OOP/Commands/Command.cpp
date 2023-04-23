#include "Command.h"



Command::Command(std::shared_ptr<Field> field)
{
	this->field = field;
}


Command::~Command()
{
}

void Command::execute(std::shared_ptr<Request> request) {

}
