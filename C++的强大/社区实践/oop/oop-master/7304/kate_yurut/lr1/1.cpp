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
  {}
 
  // copy-constructor
  Array(const Array &array)
    : m_size(array.m_size) 
    , m_array(m_size ? new T[m_size]() : nullptr)
  {
    try
    {
      std::copy(array.m_array, array.m_array + m_size, m_array); 
    }
    catch(...)
    {
      this->~Array();
      throw;
    }
  }
  
  // move constructor     
  Array(Array &&array) 
    : Array()
  {
    swap(array);
  }
  
  // assignment  
  Array &operator=(Array array)
  {
    swap(array); 
    return *this;
  } 
   
  void swap(Array &array) 
  {
    using std::swap;
      
    swap(m_size, array.m_size);
    swap(m_array, array.m_array);
  }

  // destructor
  ~Array()
  {
      delete [] m_array;
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
  std::size_t m_size;
  T* m_array;
};
