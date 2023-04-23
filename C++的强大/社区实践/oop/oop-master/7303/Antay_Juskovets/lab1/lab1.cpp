#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <memory>

template<typename T>
class Array
{
public:
  // (default) constructor
  Array(const size_t size = 0)
    : m_size(size)
    , m_array(m_size ? std::unique_ptr<T[]>(new T[m_size]) : nullptr)
  {
  }
    
  Array(Array<T> const& array) {
    m_array = std::unique_ptr<T[]>(new T[array.m_size]);
    m_size = array.m_size;
    
    T* array_ptr = array.m_array.get();  
    std::copy(array_ptr, array_ptr+array.m_size, m_array.get());
  }
    
  Array(Array<T>&& array): m_size(array.m_size), m_array(array.m_array) {
    array.m_size = 0;
    array.m_array = nullptr;
  }
    
  Array<T>& operator=(Array<T> const& array) {
    if (this != &array) {
      Array<T> temp{*this};
              
      try {
        m_array = std::unique_ptr<T[]>(new T[array.m_size]);  
        m_size = array.m_size;  
      } catch (std::exception const& error) {
        *this = temp;
        throw error;  
      }
        
      T* array_ptr = array.m_array.get();  
      std::copy(array_ptr, array_ptr+array.m_size, m_array.get());  
    }  
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
  std::unique_ptr<T[]> m_array;
};
