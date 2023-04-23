#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template <typename T>
class Array {
public:
	Array(const size_t size = 0)
		: m_size(size) , m_array(m_size ? new T[m_size]() : nullptr)
	{}

	const size_t size() const
	{
		return m_size;
	}

	T& operator [](const size_t index)
	{
		assert(index < m_size);
		return m_array[index];
	}

	Array(const Array& data)
	    : m_array(data.size() ? new T[data.size()]() : nullptr), m_size(data.size()) {
		for (int i = 0; i < data.size(); i++)
		m_array[i] = data.m_array[i];
	}

	Array& operator=(const Array& data) {
		if (this!=&data) {
			T *elem = nullptr;
			try{
				elem = new T[data.size()];
				for (int i = 0; i < data.size(); i++)
				elem[i] = data.m_array[i];
                m_size= data.size();
                delete[] m_array;
                m_array=elem;
			}
			catch (...) {
				delete[] elem;
				throw;
			}
		}
		return *this;
	}

	Array(const Array&& data) {
		m_size = data.size();
		m_array = data.m_array;
		data.m_array = nullptr;
		data.m_size = 0;
	}

	~Array() {
		delete[] m_array;
	}
private:
	size_t m_size;
	T* m_array;
};
