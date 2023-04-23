/*Bykov Ilya 6383. Lab 1. Class Array*/
#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <iostream>

template<typename T>
class Array
{
public:
	// default constructor
	Array(const size_t size = 0)
		: m_size(size)
		, m_array(m_size ? new T[m_size]() : nullptr)
	{
		for (size_t i = 0; i != m_size; i++) *(m_array + i) = i;
	}
	
	//copy constructor
	Array(const Array & Arr) : m_size(Arr.m_size), m_array(m_size ? new T[m_size]() : nullptr)
	{
		try
		{
			std::copy(Arr.m_array, Arr.m_array + m_size, m_array);
		}
		catch (...)
		{
			delete[] m_array;
			throw;
		}
	}
	
	//my swap for oerator =
	void swap(Array & Arr)
	{
		std::swap(this->m_size, Arr.m_size);
		std::swap(this->m_array, Arr.m_array);
	}

	//my operator = 
	Array & operator = (const Array& Arr)
	{
		if (this != &Arr)
			Array(Arr).swap(*this);
		return *this;
	}

	//my move constructor
	Array(Array&& Arr) : Array()
	{
		if (this != &Arr)
			swap(Arr);
	}

	Array& operator = (Array&& Arr)
	{
		if (this != &Arr)
			swap(Arr);
		return *this;
	}

	const size_t size() const
	{
		return m_size;
	}
	
	// my destructor
	~Array()
	{
		destroy();
	}

	T& operator [](const size_t index)
	{
		assert(index < m_size);

		return m_array[index];
	}
	
	void out()
	{
		for (size_t i = 0; i < m_size; i++)
			std::cout << m_array[i] << " ";
		std::cout << std::endl;
	}

private:
	void destroy()
	{
		delete[] m_array;
	}
	size_t m_size;
	T* m_array;
};

int main()
{
	Array<double> arr_1(12);
	Array<double> arr_2 = arr_1;
	Array<double> arr_3(arr_1);
	Array<double> arr_6(8);
	arr_1 = arr_6;
	Array<double> arr_4(10);
	arr_4 = arr_1;
	arr_1 = arr_2;
	arr_1.out();
	arr_2.out();
	arr_3.out();
	arr_4.out();
	return 0;
}
