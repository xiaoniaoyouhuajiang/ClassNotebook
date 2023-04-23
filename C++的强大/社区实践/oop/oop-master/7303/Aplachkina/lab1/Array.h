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
Array(const Array& a) : m_size(a.m_size)
    , m_array(m_size ? new T[m_size]() : nullptr) {    
   
      try {

          for(int i = 0; i < m_size; ++i) {
              m_array[i] = a.m_array[i];
          }
      } catch(...) {
       
          delete[] m_array;
          throw;
      }
  }
  
  Array(const Array&& a) : m_size(a.m_size)
    , m_array(a.m_array) {    
      
      a.m_array = nullptr;
  }
    
  Array& operator =(const Array& a) {
   
      Array tmp(a);

      m_size = tmp.m_size;
      m_array = new T[m_size];
      for(int i = 0; i < m_size; ++i) {
          m_array[i] = tmp.m_array[i];
      } 
      return *this;
  }
   ~Array(){
   
      delete[] m_array;
  }
private:
  size_t m_size;
  T* m_array;
};