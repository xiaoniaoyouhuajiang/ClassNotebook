#include "Command.h"

CommandBase::CommandBase(Field* field, Base* base, int x, int y, string type) {
	this->field = field;
	this->base = base;
	this->x = x;
	this->y = y;
	this->type = type;
}

void CommandBase::execute(string& str) {
	//if (str == )
}
