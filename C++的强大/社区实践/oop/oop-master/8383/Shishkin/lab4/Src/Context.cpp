#include "Context.h"

Context::Context(NeutralObject* NO) : NO(NO) {

}

Context::~Context() {
	delete NO;
}

void Context::setNO(NeutralObject* NO) {
	delete this->NO;
	this->NO = NO;
}

void Context::operator+=(Warrior* w) {
	NO->operator+=(w);
}
