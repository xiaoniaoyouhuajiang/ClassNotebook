#include <GAME/engine/RelativeSized.hpp>


void RelativeSized::setRelativeWidth(float relativeWidth) {
	this->relativeWidth = relativeWidth;
}
void RelativeSized::setRelativeHeight(float relativeHeight) {
	this->relativeHeight = relativeHeight;
}

float RelativeSized::getRelativeWidth() {
	return relativeWidth;
}

float RelativeSized::getRelativeHeight() {
	return relativeHeight;
}