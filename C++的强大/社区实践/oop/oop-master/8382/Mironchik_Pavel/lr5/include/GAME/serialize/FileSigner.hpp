#pragma once

#include <fstream>

class FileSigner {
public:
	void makeSign(std::fstream& fs);
	bool checkSign(std::fstream& fs);
};