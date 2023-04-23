#pragma once

#include "NeutralObject.h"

class Context {
public:
	Context(NeutralObject* NO = nullptr);
	~Context();
	void setNO(NeutralObject*);
	void operator+=(Warrior* w);

private:
	NeutralObject* NO;
};
