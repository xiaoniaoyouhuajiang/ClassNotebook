#pragma once

#include <GAME/engine/Attachable.hpp>
#include <GAME/engine/Provider.hpp>

template<class T>
class AttachableProvider : public Attachable<Provider<T>>, public Provider<T> {
public:
	virtual T& provide() override {
		return Attachable<Provider<T>>::origin()->provide();
	}
};

/*template<class T>
void AttachableProvider<T>::F() {
		origin();
}*/