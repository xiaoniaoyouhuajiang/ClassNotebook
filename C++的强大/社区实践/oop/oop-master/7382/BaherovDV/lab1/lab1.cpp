#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>
class Array
{
public:
  // (default) constructor
  Array(const size_t size = 0) : m_size(size), m_array(m_size ? new T[m_size]() : nullptr)
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
    
  Array(Array&& Object)
  {
      delete [] m_array;
      m_size = Object.m_size;
      m_array = Object.m_array;
      Object.m_size = 0;
      Object.m_array = nullptr;
  }
    
  Array(const Array &Object) : m_size(Object.m_size), m_array(m_size ? new T[m_size]():nullptr)
  {
        std::copy(Object.m_array, Object.m_array+Object.m_size, m_array);
  }
  
  Array& operator=(const Array& Object)
  {
    if (this != &Object)
    {
      T* A = nullptr;
      try
      {
          A = new T[Object.size()]();
          std::copy(Object.m_array, Object.m_array + Object.size(), A);  
      }
      catch(...)
      {
          delete[] A;
          throw;
      }          
      if (A != nullptr)
      {
          m_size = Object.size();
          delete [] m_array;
          m_array = A;
          
      }  
    }
    return *this;
  }
    
  ~Array()
  {
    delete [] m_array;
  }
    
  

private:
  size_t m_size;
  T* m_array;
};