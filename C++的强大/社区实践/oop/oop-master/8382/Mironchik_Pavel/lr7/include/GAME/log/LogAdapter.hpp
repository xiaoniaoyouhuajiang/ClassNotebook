#pragma once

#include <iostream>

class LogAdapter {
public:
	virtual void open() {}
	virtual void close() {}
	virtual std::ostream& ostream() = 0;
};