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

  const size_t size() const
  {
    return m_size;
  }

  T& operator [](const size_t index)
  {
    assert(index < m_size);

    return m_array[index];
  }

    //копирование
  Array(const Array& a) : m_size(a.m_size), m_array(m_size ? new T[m_size]() : nullptr)
  {
    std::copy( a.m_array, a.m_array+a.m_size, m_array);
  }
    //перемещение
  Array( Array&& a) : m_array(a.m_array), m_size(a.m_size)
  {
    a.m_array = NULL;
    a.m_size  = 0;
  }
    
     //перемещение
  Array& operator = ( Array &a)
 {
    std::unique_ptr<T[]> b( new T[a.m_size] );
    std::copy( a.m_array, a.m_array+a.m_size, b.get() );
    delete[] m_array;
    m_size = a.m_size;
    m_array = b.release();
    return *this;
 }
    
     ~Array()
  {
      delete[] m_array;
  }
    
private:
  size_t m_size;
  T* m_array;
};