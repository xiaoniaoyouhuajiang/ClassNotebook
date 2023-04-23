#pragma once

class RelativeSized {
private:
	float relativeHeight;
	float relativeWidth;

public:
	void setRelativeWidth(float relativeWidth);
	void setRelativeHeight(float relativeHeight);

	float getRelativeWidth();
	float getRelativeHeight();
};