#include "Snapshot.h"

Snapshot::Snapshot(std::string data_)
{
	data = data_;
}

bool Snapshot::write(std::string fileName)
{
	std::ofstream out(fileName);

	if (out.is_open() == false)
		return false;

	out << data;

	return true;
}

bool Snapshot::read(std::string fileName)
{
	std::ifstream in(fileName);

	if (!in.is_open() || !(in >> data))
		return false;
	return true;
}

std::string& Snapshot::get()
{
	data = "";
	return data;
}

std::string& SnapReader::get()
{
	return data;
}
