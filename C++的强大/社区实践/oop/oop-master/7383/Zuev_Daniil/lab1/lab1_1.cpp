#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>
class Array
{
public:
  // (default) constructor
    Array(const size_t size = 0):m_size(size), m_array(m_size ? new T[m_size]() : nullptr)
    {
    }
    //destructor
    ~Array()
    {
        delete [] m_array;
        m_array = nullptr;
        m_size = 0;
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
    //copy constructor
    Array(const Array& array):m_size(array.m_size), m_array(m_size ? new T[m_size]() : nullptr)
    {
        std::copy(array.m_array, array.m_array+m_size, m_array);
    }
    //move constructor
    Array(Array&& array):m_size(array.m_size), m_array(array.m_array)
    {
        delete [] array.m_array;
        array.m_array = nullptr;
        array.m_size = 0;
    }
    //assignment operator
    Array& operator = (const Array& array)
    {
        Array tmp(array.m_size);
        std::copy(array.m_array, array.m_array + array.m_size, tmp.m_array);
        std::swap(tmp.m_array, m_array);
        std::swap(tmp.m_size, m_size);
        return *this;
    }

private:
    size_t m_size;
    T* m_array;
};
