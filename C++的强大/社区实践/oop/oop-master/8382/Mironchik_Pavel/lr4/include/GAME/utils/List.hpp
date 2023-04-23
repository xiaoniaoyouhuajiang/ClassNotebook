#pragma once

#include <iterator>
#include <cassert>
#include <functional>

template <class T>
struct ListItem {
	T value;
	ListItem<T>* next = nullptr;
	ListItem<T>* prev = nullptr;

	ListItem() {};
	ListItem(T value) : value(value) {};
};

template <class T>
class ListIterator : public std::iterator<
	std::input_iterator_tag,
	T
> {
private:
	ListItem<T> *item;

public:
	ListIterator(ListItem<T> *item) {
		this->item = item;
	}

	ListIterator& operator++() {
		item = item->next;
		return *this;
	}

	ListIterator operator++(int) {
		ListIterator retval = *this;
		++(*this);
		return retval;
	}

	bool operator==(ListIterator& other) const {
		return item == other.item;
	}

	bool operator!=(ListIterator& other) const {
		return !(*this == other);
	}

	T& operator*() const {
		return item->value;
	}
};

template <class T>
class List {
private:
	int size = 0;
	ListItem<T> *last = new ListItem<T>();
	ListItem<T> *first = last;

	ListItem<T>* getItem(int position);
	void removeItem(ListItem<T> *item);

public:

	explicit List();
	~List();

	int getSize() const;

	void insert(T& elem, int position);
	void add(T& elem);
	bool remove(T& elem);
	T& removeAt(int position);
	int indexOf(T& elem) const;
	void removeIf(std::function<bool(T&)>);
	bool contains(T& elem) const;
	void clear();

	List<T>* copy() const;

	ListIterator<T> begin() const;
	ListIterator<T> end() const;
};

template <class T>
List<T>::List() {}

template <class T>
List<T>::~List() {
	clear();
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
void List<T>::insert(T& elem, int position) {
	assert(position <= size && position >= 0);

	ListItem<T>* newItem = new ListItem<T>(elem);
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
void List<T>::add(T& elem) {
	insert(elem, size);
}

template <class T>
void List<T>::removeItem(ListItem<T> *item) {
	size--;
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
bool List<T>::remove(T& elem) {
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
T& List<T>::removeAt(int position) {
	assert(position <= size && position >= 0);

	auto item = getItem(position);
	T& value = item->value;
	removeItem(item);
	return value;
}

template <class T>
int List<T>::indexOf(T& elem) const {
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
	return ListIterator<T>(first);
}

template <class T>
ListIterator<T> List<T>::end() const {
	return ListIterator<T>(last);
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
void List<T>::removeIf(std::function<bool(T&)> cond) {
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
bool List<T>::contains(T& elem) const {
	for (T& item : *this)
		if (item == elem)
			return true;

	return false;
}

template<class T>
void List<T>::clear() {
	size = 0;
	while (first != last) {
		auto prev = first;
		first = first->next;
		delete prev;
	}
}