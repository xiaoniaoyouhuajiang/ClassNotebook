#include <assert.h>
#include <algorithm>
#include <cstddef>

template<typename T>
class Array { 
public:
    // constructors and destructor
    Array(const size_t size = 0)
        : m_size(size), m_array(m_size ? new T[m_size] : nullptr)
    {
    }
    
    Array(const Array<T> &var)
        : Array(var.m_size)
    {
        std::copy(var.m_array, var.m_array + m_size, m_array);
    }
    
    Array(Array<T> &&var)
        : Array()
    {
        std::swap(m_size, var.m_size);
        std::swap(m_array, var.m_array);
    }
    
    ~Array()
    {
        if (m_array != nullptr)
            delete[] m_array;
    }
    
    
    // methods
    const size_t size() const
    {
        return m_size;
    }
    
    
    // operators
    T& operator [] (const size_t index)
    {
        assert(index < m_size);
        return m_array[index];
    }
    Array<T>& operator = (const Array<T> &var)
    {
        if (this != &var) {
            Array<T> temp(var);
            m_size = temp.m_size;
            std::swap(m_array, temp.m_array);
        }
        return *this;
    }
    Array<T>& operator = (Array<T> &&var)
    {
        m_size = var.m_size;
        std::swap(m_array, var.m_array);
        return *this;
    }
    
private:
    size_t m_size;
    T* m_array;
   
};
