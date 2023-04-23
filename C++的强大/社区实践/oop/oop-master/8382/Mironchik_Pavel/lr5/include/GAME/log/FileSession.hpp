#pragma once

#include <string>
#include <iostream>
#include <fstream>

class FileSession {
private:
	std::fstream _fs;
	std::string _filename;

public:
	FileSession(std::string name, int mode = std::ios::app) : _filename(name) {
		_fs.open(_filename, mode);
	}

	~FileSession() {
		_fs.close();
	}

	std::fstream& fstream() {
		return _fs;
	}
};