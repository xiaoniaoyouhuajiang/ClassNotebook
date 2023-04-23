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
		, m_array(m_size ? new T[m_size]() : nullptr) {}
    
    ~Array() {
        delete[]m_array;
    }    
    
	Array(Array &array) {
		m_size = array.size();
		m_array = m_size ? new T[m_size]() : nullptr;
		std::copy(array.m_array, array.m_array + array.m_size, m_array);
	}
    
    Array(Array &&array) {
        m_size = array.m_size;
        std::copy(array.m_array, array.m_array + array.m_size, m_array);
        delete[]array.m_array;
        array.m_size = 0;
    } 

	Array &operator=(Array &array) { 
        T *arr = nullptr;
        
        try {
            arr = new T[array.m_size];
            std::copy(array.m_array, array.m_array + array.m_size, arr); 
        }
        catch (...) {
            delete[]arr;
            throw;
        }
        
        if (this != &array) {
            if (m_array) delete[]m_array;
            m_array = arr;
            m_size = array.m_size;
        }
        else delete[]arr;
        
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

private:
	size_t m_size;
	T* m_array;
};