#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <iostream>

template<typename T>
class Array
{
public:
	// (default) constructor
	Array(const size_t size = 0)
		: m_size(size)
		, m_array(m_size ? new T[m_size]() : nullptr)
	{
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

	// copy constructor
	Array(Array const &rvalue) {
		m_size = rvalue.m_size;
		m_array = new T[m_size];
		try {
			if (m_size) {
				for (int i = 0; i < m_size; i++) {
					m_array[i] = rvalue.m_array[i];
				}
			}
			else {
				m_array = nullptr;
			}
		}
		catch (...) {
			delete[] m_array;
			throw;
		}
	}

	// move constructor
	Array(Array&& tmp)
		: m_array(std::move(tmp.m_array))
		, m_size(std::move(tmp.m_size))
	{
		tmp.m_array = nullptr;
	}

	void swap(Array& arr)
	{
		std::swap(this->m_size, arr.m_size);
		std::swap(this->m_array, arr.m_array);
	}

	// operator  
	Array& operator=(const Array& ptr) {
		if (this != &ptr)
			Array(ptr).swap(*this);
		return *this;
	}

	void print() const
	{
		if (!m_array)
			std::cout << "Empty array! ";
		else {
			std::cout << "print func ";
			for (int i = 0; i < m_size; i++)
				std::cout << m_array[i] << " ";
		}
		std::cout << std::endl;
	}

	// destructor  
	~Array() {
		delete[] m_array;
	}

private:
	size_t m_size;
	T* m_array;
};

int main() {
	Array <int> object1(5);
	Array <int> object2(10);
	for (int i = 0; i < 5; i++) {
		std::cin >> object1[i];
	}
	object1.print();
	for (int i = 0; i < 10; i++) {
		std::cin >> object2[i];
	}
	object2 = object1;
	object2.print();
	Array <int> object3 = object1;
	object3.print();
	system("pause>nul");
}