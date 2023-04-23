#include <assert.h>
#include <algorithm> // std::copy
#include <functional>
#include <cstddef> // size_t
#include <memory>
#include <iostream>
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

const size_t size() const
{
	return m_size;
}

T& operator [](const size_t index)
{
	assert(index < m_size);
	return m_array[index];
}

Array(const Array& other)
	: m_size(other.m_size),
	m_array(m_size ? new T[m_size] : nullptr)	
{
	std::copy(other.m_array.get(), other.m_array.get() + m_size, m_array.get());
}

Array & operator = (Array const& object)	
{
	if (this != &object)
	{
	Array(object).swap(*this);
	}
//std::copy(object.m_array.get(), object.m_array.get() + m_size, * this->m_array.get());
	return *this;
}

void swap(Array & object) 
{
	std::swap(this->m_size, object.m_size);
	std::swap(this->m_array, object.m_array);
}

Array(Array&& tmp): m_size(0)
{
	m_array.reset(tmp.m_array.release());
	m_size = tmp.m_size;
	tmp.m_size = 0;
}

private:
	size_t m_size;
	unique_ptr<T[]> m_array;
};