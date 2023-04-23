#pragma once
#include <string>
#include <fstream>
#include <iostream>

class MyException {
protected:
	std::string errMes;
public:
	MyException(std::string errMes) : errMes(errMes) {
	}
	~MyException() = default;

	virtual std::string &getMes() {
		return errMes;
	}
};

class ArrayException : public MyException {
private:
	int accsessIndex;
	int arraySize;
public:
	~ArrayException() = default;
	ArrayException(std::string errMes, int arrSize, int arrIndex) : MyException(errMes), arraySize(arrSize), accsessIndex(arrIndex){
	}

	virtual std::string &getMes();
};

class FileException : public MyException {
private:
	std::string fileName;
	std::ios::iostate fileState;
public:
	~FileException() = default;
	FileException(std::string errMes, std::string fileName, std::ios::iostate fileState) : MyException(errMes),
		fileName(fileName), fileState(fileState) {
	
	}

	virtual std::string &getMes();
};

