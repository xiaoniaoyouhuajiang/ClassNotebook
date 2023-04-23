#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <cstring> 
#include <memory>
template<typename T>
class Array
{
public:
    // (default) constructor
    Array(const size_t size = 0) : m_size(size), m_array(m_size ? new T[m_size]() : nullptr){
    }
    
    const size_t size() const    
    {
        return m_size;
    }

    T& operator [](const size_t index){
        assert(index < m_size); 
        return m_array[index];
    }


    Array & operator =(const Array &other){ 
        std::unique_ptr<T[]> array(new T[other.m_size]);
        std::copy(other.m_array, other.m_array + other.m_size, array.get());
        if (this != &other){ 
            delete m_array;
            m_size = other.m_size;
            m_array = new T[m_size];
            std::copy(other.m_array, other.m_array + m_size, m_array); }
            array=std::move(nullptr);
        return *this;
    }

    Array(const Array &other){
        std::unique_ptr<T[]> array(new T[other.m_size]);
        std::copy(other.m_array, other.m_array + other.m_size,array.get());
        m_size = other.m_size;
        m_array = new T[m_size];
        std::copy(array.get(), array.get() + m_size, m_array);
        array = std::move(nullptr);
    }

    Array(const Array &&other):m_size(0),m_array(nullptr){ 
        std::unique_ptr<T[]> array(new T[other.m_size]);
        std::copy(other.m_array, other.m_array + other.m_size,array.get());
        m_size = other.m_size;
        std::copy(other.m_array, other.m_array + m_size, m_array); 
        delete[] other.m_array;
        other.m_size = 0;
        array = std::move(nullptr);
    }
    
    ~Array(){
        delete [] m_array;
    }

private:
    size_t m_size;
    T* m_array;
};