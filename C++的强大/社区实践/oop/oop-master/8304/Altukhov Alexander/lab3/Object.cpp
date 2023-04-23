#include "Object.h"

Field* Object::getParentField() {
	return parentField;
}
void Object::setParentField(Field*& field) {
	parentField = field;
}
void Object::setNullParentField() {
	parentField = nullptr;
}