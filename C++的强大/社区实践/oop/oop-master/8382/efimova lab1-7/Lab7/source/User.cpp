#include "User.h"

User::User(std::string name) : _name(name) {}

std::string User::getName() {
	return _name;
}