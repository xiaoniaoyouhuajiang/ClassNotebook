#include "pch.h"
#include "MyException.h"
#include <sstream>

std::string & ArrayException::getMes() {
	std::stringstream ss;
	ss << errMes << " Array size was " << arraySize << ". Tried to accsess element at index " << accsessIndex << "." << std::endl;
	errMes = ss.str();

	return errMes;
}

std::string & FileException::getMes() {
	std::stringstream ss;
	ss << errMes << " Failed file name: " << fileName << ". File bits state: " << fileState << std::endl;
	errMes = ss.str();

	return errMes;
}
