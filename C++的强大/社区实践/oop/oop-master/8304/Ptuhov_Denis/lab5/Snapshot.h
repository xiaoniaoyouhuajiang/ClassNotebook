#pragma once
#include <string>
#include <fstream>

struct Snapshot
{
	Snapshot() = default;
	Snapshot(std::string data_);
	bool write(std::string fileName);
	bool read(std::string fileName);
	virtual std::string& get();

protected:
	std::string data;
};

struct SnapReader : Snapshot
{
	SnapReader() = default;
	std::string& get();
};