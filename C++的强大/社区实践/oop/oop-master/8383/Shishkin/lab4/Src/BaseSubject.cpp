#include "BaseSubject.h"

void Subject::addObserver(IObserver* observer) {
	observers.push_back(observer);
}

void Subject::removeObserver(IObserver* observer) {
	for (vector<IObserver*>::iterator iter = observers.begin(); iter != observers.end(); iter++) {
		if (*iter == observer) {
			observers.erase(iter);
			return;
		}
	}
}

void Subject::notify() {
	for (IObserver* el : observers)
		el->updateNotify(this);
}