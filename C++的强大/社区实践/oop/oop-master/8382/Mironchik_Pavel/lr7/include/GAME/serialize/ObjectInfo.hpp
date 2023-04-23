#pragma once

class ObjectInfo {
public:
	const void* object;
	bool needWrite;

	bool operator==(const ObjectInfo& other) const {
		return object == other.object;
	}

	bool operator<(const ObjectInfo& other) const {
		return object < other.object;
	}

	bool operator>(const ObjectInfo& other) const {
		return !(*this < other);
	}
};