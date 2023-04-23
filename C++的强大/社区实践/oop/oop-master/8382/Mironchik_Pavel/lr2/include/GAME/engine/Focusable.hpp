#pragma once

class Focusable {
private:
	bool focusable = false;
	bool focused = false;

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