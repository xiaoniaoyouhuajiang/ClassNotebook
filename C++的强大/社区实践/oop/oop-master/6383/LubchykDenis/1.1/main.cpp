#include <assert.h>
#include <iostream>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <memory>

template<typename T>
class Array
{
public:
    //default
    Array(const size_t size = 0) :
    m_size(size),
    m_array(m_size ? new T[m_size]() : nullptr)
    {
    }
    
    //copy
    Array(const Array& tmp) :
    m_size(tmp.m_size),
    m_array(m_size ? new T[m_size] : nullptr)
    {
        for (size_t i = 0; i != m_size; ++i)
            m_array[i]=tmp.m_array[i];
    }
    
    //=
    Array & operator=(Array obj)
    {
        std::swap(m_size, obj.m_size);
        std::swap(m_array, obj.m_array);
        return *this;
    }
    
    //move
    Array(Array&& tmp)
    {
        swap(m_array,tmp.m_array);
        swap(m_size,tmp.m_size);
        tmp.m_size = 0;
        tmp.m_array = 0;
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
    std::unique_ptr <T[]> m_array;
};

int main(int argc, const char * argv[]) {
    Array<int> k1;
    Array<int> k2(20);
    k1=k2;
    return 0;
}
