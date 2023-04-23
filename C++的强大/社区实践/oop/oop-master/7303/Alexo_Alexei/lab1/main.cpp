#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <new>
#include <memory>

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
    
  ~Array() {
      delete[]m_array;
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
    Array(const Array& array) {           
      m_array = new T[array.m_size]; 
      std::copy(array.m_array, array.m_array + array.m_size, m_array);
      m_size = array.m_size;
  }
 //move constructor
    Array(Array&& array) {   
      delete[]m_array;
      m_array = new T[array.m_size];
      std::copy(array.m_array, array.m_array + array.m_size, m_array);
      m_size = array.m_size;
      delete array;
  }
 //operator
  Array& operator=(Array& array) {
      std::unique_ptr<T[]> arr(new T[array.m_size]);
      std::copy(array.m_array, array.m_array + array.m_size, arr.get());
      
      if (this != &array) {
          m_size = array.m_size;
          m_array = new T[m_size];
          std::copy(array.m_array, array.m_array + array.m_size, m_array);
          arr.reset();
      }
      
      return *this;
  }
    
private:
  size_t m_size;
  T* m_array;
};
