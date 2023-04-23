#include <GAME/log/FileLogAdapter.hpp>
#include <GAME/log/Log.hpp>

void FileLogAdapter::open() {
	if (_session != nullptr) {
		Log::exception("FileLogAdapter", "Failed start new session: session is already active");
	}
	
	_session = new FileSession(_filename);
}

std::ostream& FileLogAdapter::ostream() {
	return _session->fstream();
}

void FileLogAdapter::close() {
	if (_session != nullptr) {
		Log::exception("FileLogAdapter", "Failed close session: session is not active");
	}

	delete _session;
	_session = nullptr;
}

FileLogAdapter::~FileLogAdapter() {
	if (_session != nullptr)
		delete _session;
}