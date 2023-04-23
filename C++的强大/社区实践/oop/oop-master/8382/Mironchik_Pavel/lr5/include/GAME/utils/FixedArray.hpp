#pragma once

template <typename T>
class FixedArray
{
private:
	T* arr;
	int size;

public:
	FixedArray(int size) {
		this->size = size;
		this->arr = new T[size];
	}

	~FixedArray() {
		delete arr;
	}

	T& operator [] (int n) {
		return arr[n];
	}

	int getSize() {
		return size;
	}
};

