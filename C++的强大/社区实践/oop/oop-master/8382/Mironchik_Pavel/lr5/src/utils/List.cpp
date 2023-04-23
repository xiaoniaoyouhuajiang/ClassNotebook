/*#include <GAME/utils/List.hpp>
#include <cassert>

template <class T>
List<T>::List() {}

template <class T>
List<T>::~List() {
	ListItem<T>* cur = first;

	while (cur != last) {
		auto nextItem = cur->next;
		delete cur;
		cur = nextItem;
	}

	delete last;
}

template <class T>
int List<T>::getSize() const {
	return size;
}

template <class T>
ListItem<T>* List<T>::getItem(int position) {
	if (position - size > position) {
		auto curItem = last->prev;
		
		for (int i = size - 1; i > position; i--)
			curItem = curItem->prev;

		return curItem;
	}
	else {
		auto curItem = first;

		for (int i = 0; i < position; i++)
			curItem = curItem->next;

		return curItem;
	}
}

template <class T>
void List<T>::insert(T* elem, int position) {
	assert(position <= size && position >= 0);

	ListItem<T>* newItem = new ListItem(elem);
	size++;

	if (position == 0) {
		auto prevFirst = first;
		first = newItem;
		first->next = prevFirst;
		prevFirst->prev = first;
		return;
	}

	ListItem<T>* itemBefore = getItem(position - 1);

	itemBefore->next->prev = newItem;
	newItem->next = itemBefore->next;
	newItem->prev = itemBefore;
	itemBefore->next = newItem;
}

template <class T>
void List<T>::add(T* elem) {
	insert(elem, size);
}

template <class T>
void List<T>::removeItem(ListItem<T> *item) {
	if (item == first) {
		first = first->next;
		first->prev = nullptr;
		delete item;
		return;
	} 

	item->prev->next = item->next;
	item->next->prev = item->prev;
	delete item;
}

template <class T>
bool List<T>::remove(T* elem) {
	auto curItem = first;

	while (curItem != last) {
		if (curItem->value == elem) {
			removeItem(curItem);
			return true;
		}
		curItem = curItem->next;
	}

	return false;
}

template <class T>
T* List<T>::removeAt(int position) {
	assert(position <= size && position >= 0);

	auto item = getItem(position);
	auto value = item->value;
	removeItem(item);
	return value;
}

template <class T>
int List<T>::indexOf(T* elem) const {
	auto curItem = first;
	auto position = 0;

	while (curItem != last) {
		if (curItem->value == elem) {
			return position;
		}

		position++;
		curItem = curItem->next;
	}

	return -1;
}

template <class T>
ListIterator<T> List<T>::begin() const {
	return ListIterator<T, T*>(first);
}

template <class T>
ListIterator<T> List<T>::end() const {
	return ListIterator<T, T*>(last);
}

template <class T>
List<T>* List<T>::copy() const {
	auto newList = new List<T>();

	for (T value : *this) {
		newList->add(value);
	}

	return newList;
}

template <class T>
void List<T>::removeIf(bool(*cond)(const T*)) {
	auto curItem = first;

	while (curItem != last) {
		auto nextItem = curItem->next;
		if (cond(curItem->value)) {
			removeItem(curItem);
		}
		curItem = nextItem;
	}
}

template <class T>
bool List<T>::contains(T* elem) const {
	for (T item : this)
		if (item == elem)
			return true;

	return false;
}*/