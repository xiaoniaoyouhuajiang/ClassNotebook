#include <GAME/log/FileLogAdapter.hpp>

void FileLogAdapter::open() {
	assert(_session == nullptr);
	_session = new FileSession(_filename);
}

std::ostream& FileLogAdapter::ostream() {
	assert(_session != nullptr);
	return _session->fstream();
}

void FileLogAdapter::close() {
	assert(_session != nullptr);
	delete _session;
	_session = nullptr;
}

FileLogAdapter::~FileLogAdapter() {
	if (_session != nullptr)
		delete _session;
}