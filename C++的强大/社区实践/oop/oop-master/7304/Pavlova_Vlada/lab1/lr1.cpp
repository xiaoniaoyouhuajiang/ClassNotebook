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

	//constructor =
	Array & operator = (Array const& arr)
	{
		Array new_array(arr);
		m_size = new_array.m_size;
		m_array = new T[m_size];
		std::copy(new_array.m_array, new_array.m_array + new_array.m_size, m_array);

		return *this;
	}

//copy constructor
	Array(const Array &arr)
		: m_size(arr.m_size), m_array(new T[m_size]) {
		try {
			for (int i = 0; i < m_size; i++) {
				m_array[i] = arr.m_array[i];
			}
		}
		catch (...) {
			delete[] m_array;
			throw;
		}
	}

	//move constructor
	Array(Array &&arr)
		: m_array(arr.m_array), m_size(arr.m_size)
	{
		arr.m_array = nullptr;
		arr.m_size = 0;

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

	//destructor
	~Array() {
		delete[] m_array;
	}
private:
	size_t m_size;
	T* m_array;
};

int main(){
	return 0;
}
