#pragma once

#include <fstream>
#include <cassert>
#include <string>

#include <GAME/log/LogAdapter.hpp>

using std::string;

class FileSession;

class FileLogAdapter : public LogAdapter {
private:
	string _filename;
	FileSession* _session;

public:
	FileLogAdapter() : FileLogAdapter("log.txt") {}
	FileLogAdapter(string filename) : _filename(filename) {}

	virtual void open() override;

	virtual std::ostream& ostream() override;

	virtual void close() override;

	~FileLogAdapter();
};

class FileSession {
private:
	std::fstream _fs;
	string _filename;

public:
	FileSession(string name);
	~FileSession();
	std::fstream& fstream();
};