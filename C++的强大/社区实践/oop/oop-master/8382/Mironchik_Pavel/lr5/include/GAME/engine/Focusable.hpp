#pragma once

#include <iostream>

#include <GAME/serialize/Serializer.hpp>
#include <GAME/serialize/InObjectsTable.hpp>
#include <GAME/serialize/OutObjectsTable.hpp>

using std::istream;
using std::ostream;

class Focusable {
private:
	bool focusable = false;
	bool focused = false;

protected:
	void writeFocusable(ostream& os, OutObjectsTable& table) {
		Serializer::writeBool(os, &focusable);
		Serializer::writeBool(os, &focused);
	}

	void readFocusable(istream& is, InObjectsTable& table) {
		Serializer::readBool(is, &focusable);
		Serializer::readBool(is, &focused);
	}

public:
	void setFocusable(bool focusable) {
		this->focusable = focusable;
	}

	bool isFocusable() const{
		return focusable;
	}

	void setFocused(bool focused) {
		this->focused = focused;
	}

	bool isFocused() const{
		return focused && focusable;
	}
};