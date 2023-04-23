#pragma once
#include "Field.h"

class Field;

class Object {
	
	Field* parentField;

public:
	Field* getParentField();
	void setParentField(Field*& field);
	void setNullParentField();
	virtual ~Object() = default;

};

