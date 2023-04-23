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
  //copy constructor
    Array(const Array &c)
    : m_size(c.m_size)
    , m_array(m_size ? new T[m_size]() : nullptr) {
        std::copy(c.m_array, c.m_array+c.m_size, m_array);
    }
  //move constructor 
    Array(Array&& c)
    : m_array(c.m_array),
    m_size(c.m_size) {
        c.m_array = nullptr;
        c.m_size = 0;
    }
   //copy assignment operator
    Array& operator=(const Array& c){
        Array buf(c.m_size);
        std::copy(c.m_array, c.m_array + c.m_size, buf.m_array);
        delete []m_array;
        m_size = buf.m_size;
        m_array = m_size ? new T[m_size]() : nullptr;
        std::copy(buf.m_array, buf.m_array + buf.m_size, m_array);
        return *this;
    }
   //move assignment operator
    Array& operator=(Array&& c) {
        *this = std::move(c);
        c.m_array = nullptr;
        c.m_size = 0;
        return *this;
    }
    
  const size_t size() const
  {
    return m_size;
  }
    
    ~Array()
  {
      delete[] m_array;
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