#define _SCL_SECURE_NO_WARNINGS
#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <iostream>
#include <iomanip>

template<typename T>
class Array
{
public:
	// (default) constructor
	Array(const size_t size = 0)
		: m_size(size)
		, m_array(m_size ? new T[m_size]() : nullptr)
	{
		for (int i = 0; i < m_size; i++) m_array[i] = i;
	}

	Array(const Array& a) : m_size(a.m_size), m_array(m_size ? new T[m_size]() : nullptr)
	{//copy
		try
		{
			std::copy(a.m_array, a.m_array + m_size, m_array);
		}
		catch (...)
		{
			delete[] m_array;
			throw;
		}
	}

	void swap(Array & a) {
		std::swap(this->m_size, a.m_size);
		std::swap(this->m_array, a.m_array);
	}



	Array(Array&& a) {//move
		if (this != &a)
			swap(a);
	}

	Array & operator=(const Array& a) {//assigment
		if (this != &a) {
			Array(a).swap(*this);
		}
		return *this;
	}

	const size_t size() const
	{
		return m_size;
	}

	T& operator [](const size_t index)
	{
		assert(index < m_size);

		return m_array[index];
	}

	void print() {
		for (int j = 0; j < m_size; j++) {
			std::cout << std::setw(3) << m_array[j];
		}
		std::cout << std::endl;
	}

	~Array() {
		delete[] m_array;
	}

private:
	size_t m_size;
	T* m_array;
};

int main() {
	Array<int> a1(10);
	Array<int> a2;
	a2= a1;
	Array<int> a3(a1);
	Array<int> a4(6);
	a1 = a4;
	a1.print();
	a2.print();
	a3.print();
	a4.print();
	system("pause");
	return 0;
}