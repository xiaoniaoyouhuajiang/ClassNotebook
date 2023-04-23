#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>
class Array
{
public:
	// default constructor
	Array(const size_t size = 0) :
		m_size(size),
		m_array(m_size ? new T[m_size]() : nullptr)
	{}
	// copy constructor
	Array(const Array &obj) :
		m_size(obj.m_size),
		m_array(m_size ? new T[m_size]() : nullptr)
	{
		std::copy(obj.m_array, obj.m_array + obj.m_size, m_array);
	}
	// move constructor
	Array(Array &&obj) :
		m_size(obj.m_size),
		m_array(obj.m_array)
	{

	}

	const size_t size() const {
		return m_size;
	}

	T& operator [](const size_t index) {
		assert(index < m_size);
		return m_array[index];
	}

	~Array() {
		delete[] m_array;
		m_size = 0;
	}

	Array& operator=(const Array& object)         // оператор присваивания
	{

		size_t newSize = object.m_size;
		T* newArray = nullptr;
		if (newSize)
			newArray = new T[newSize]();
		try
		{
			std::copy(object.m_array, object.m_array + newSize, newArray);
		}
		catch (...)
		{
			delete[] newArray;
			throw;
		}
		delete[]m_array;
		m_size = newSize;
		m_array = newArray;


		return *this;
	}
	Array& operator=(Array&& object)         // оператор присваивания с перемещением
	{

		if (this != &object)
			return *this;

		delete[] m_array;
		m_size = 0;

		m_array = object.m_array;
		m_size = object.size;

		object.m_array = nullptr;
		object.size = 0;






		return *this;
	}



private:
	size_t m_size;
	T* m_array;
};