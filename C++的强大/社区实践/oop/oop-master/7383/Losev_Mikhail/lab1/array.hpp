#pragma once
#include <assert.h>
#include <algorithm>	// std::copy
#include <cstddef>	// size_t

using namespace std;

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
		
	Array(Array const& other) // copy constructor
		: m_size(other.m_size)
		, m_array(m_size ? new T[m_size]() : nullptr)
	{
		std::copy(other.m_array, other.m_array + m_size, m_array);
			
		// for (int i = 0; i < m_size; i++)
		//		m_array[i] = other.m_array[i];
	}
		
	Array(Array const&& other) // move constructor
		: m_size(other.m_size)
		, m_array(other.m_array)
	{
		other.m_size = 0;
		other.m_array = nullptr;
	}

	const size_t size() const
	{
		return m_size;
	}

	Array & operator=(const Array &other) //copy assignment operator
	{
		if(&other == this)
			return *this;
	
		T* tmpa = other.m_size ? new T[other.m_size]() : nullptr;
		try {
			std::copy(other.m_array, other.m_array + other.m_size, tmpa);
			//for (size_t i = 0; i < other.m_size; i++)
			//		tmpa[i] = other.m_array[i];
			if (m_array) delete this->m_array;
			this->m_size = other.m_size;
			this->m_array = tmpa; 
		} catch (...) {
			delete[] tmpa;
			throw;
		}
	}

	T& operator [](const size_t index)
	{
		assert(index < m_size);
		return m_array[index];
	}
		
	~Array()
	{
		if (m_array) delete [] m_array;
	}

private:
	size_t m_size;
	T* m_array;
};


