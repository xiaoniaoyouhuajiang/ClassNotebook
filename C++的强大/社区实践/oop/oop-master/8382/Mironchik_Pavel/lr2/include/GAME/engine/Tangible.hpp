#pragma once

class Tangible {
private:
	bool tangible = true;

public:
	void setTangible(bool tangible) {
		this->tangible = tangible;
	}

	bool isTangible() const {
		return tangible;
	}
};