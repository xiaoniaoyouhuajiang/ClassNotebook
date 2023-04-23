#include "Command.h"

CommandBase::CommandBase(Field* field, Base* base, string type) {
	this->field = field;
	this->base = base;
	this->type = type;
}

void CommandBase::execute(string& str) {
	if (type == "createME") {
		base->createMEBase(field->getSizeOfField(), *field);
	}

	else if (type == "createO") {
		base->createOrcsBase(field->getSizeOfField(), *field);
	}

	else if (type == "addInME") {
		base->addInMEBase(str, *field, field->getSizeOfField());
	}

	else if (type == "addInO") {
		base->addInOrcsBase(str, *field, field->getSizeOfField());
	}
}

CommandField::CommandField(Field* field, string type) {
	this->field = field;
	this->type = type;
}

void CommandField::execute(string& str) {
	if (type == "add") {
		field->add(str, -30, 0);
	}

	else if (type == "del") {
		field->del(str);
	}

	else if (type == "move") {
		string character = "";
		character += str[0];
		character += str[1];
		character += str[2];
		//const char* direction = str[3];
		field->moving(character, str[3] - '0');
	}
}
