#pragma once

template<class T>
class Provider {
public:
	virtual T& provide() = 0;
};