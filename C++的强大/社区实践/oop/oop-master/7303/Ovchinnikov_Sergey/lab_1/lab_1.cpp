
#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

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
	// copy constructor
	Array(const Array &array):
		m_size(array.m_size),
		m_array(m_size ? new T[m_size]() : nullptr) {

		try {
			std::copy(array.m_array, array.m_array + m_size, m_array);
		}
		catch (...) {
			delete[] m_array;
			throw;
		}
	}

	// move constructor
	Array(const Array&& array):
		m_size(array.m_size),
		m_array(array.m_array){
		array.m_size = 0;
		array.m_array = nullptr;
	}

	Array& operator = (const Array& array) {
		if (this == &array)
			return *this;

		Array temp(array);
		m_size = temp.m_size;
		m_array = new T[temp.m_size];
		std::copy(temp.m_array, temp.m_array + temp.m_size, m_array);
		return *this;
	}

	~Array(){
		delete[] m_array;
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

private:
	size_t m_size;
	T* m_array;
};
