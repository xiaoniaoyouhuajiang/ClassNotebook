#pragma once
#include "File.h"
#include <string>
#include <vector>


class Memento {
public:
	std::string saveString;
	int getNum(int& pos);
	void getNum(int& pos, std::vector<int>& info);
	bool isValid();
	Memento(std::string message, bool flag); //flag 0 = out, 1 - in
	~Memento();
private:
	File* filePtr;
};
