#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template <typename T>
class Array
{
public:
	// (default) constructor
	Array(const size_t size = 0)
		: m_size(size)
		, m_array(m_size ? new T[m_size]() : nullptr)
	{}

	// copy constructor
	Array(const Array& arr) : m_size(arr.m_size)
		, m_array(m_size ? new T[m_size]() : nullptr) {
		try {
			for (size_t i = 0; i < m_size; ++i) {
				m_array[i] = arr.m_array[i];
			}
		}
		catch (...) {
			delete[] m_array;
			throw;
		}
	}

	// move constructor
	Array(const Array&& arr) : m_size(arr.m_size)
		, m_array(arr.m_array) {
		arr.m_array = nullptr;
		arr.m_size = 0;
	}

	// copy assignment operator
	Array& operator =(const Array& arr) {
		Array tmp(arr);
		m_size = tmp.m_size;
		m_array = new T[m_size];
		for (size_t i = 0; i < m_size; ++i) {
			m_array[i] = tmp.m_array[i];
		}
		return *this;
	}

	// move assignment operator
	Array & operator=(const Array &&arr) {
		if (this != &arr) {
			delete[] m_array;
			m_size = arr.m_size;
			m_array = arr.m_array;
			arr.m_array = nullptr;
			m_size = 0;
		}
		return *this;
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
	}

private:
	size_t m_size;
	T* m_array;
};
