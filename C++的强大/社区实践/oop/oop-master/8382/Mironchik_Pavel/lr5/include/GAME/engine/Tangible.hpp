#pragma once

#include <iostream>

#include <GAME/serialize/Serializer.hpp>
#include <GAME/serialize/InObjectsTable.hpp>
#include <GAME/serialize/OutObjectsTable.hpp>

using std::istream;
using std::ostream;

class Tangible {
private:
	bool tangible = true;

protected:
	void writeTangible(ostream& os, OutObjectsTable& table) {
		Serializer::writeBool(os, &tangible);
	}

	void readTangible(istream& is, InObjectsTable& table) {
		Serializer::readBool(is, &tangible);
	}

public:
	void setTangible(bool tangible) {
		this->tangible = tangible;
	}

	bool isTangible() const {
		return tangible;
	}
};