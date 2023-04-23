#pragma once

#include <fstream>
#include <cassert>
#include <string>

#include <GAME/log/LogAdapter.hpp>
#include <GAME/log/FileSession.hpp>

using std::string;

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