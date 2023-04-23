#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>
class Array
{
public:
   
   void swap(Array<T> & arr) 
   {
       std::swap(m_array, arr.m_array);
       std::swap(m_size, arr.m_size);
   }
    
   Array & operator =(const Array<T>& arr)
   {
       if (this != &arr)
       {
           Array<T> tmp(arr);
           tmp.swap(*this);
       }
       return *this;       
   }

  // (default) constructor
  Array(const size_t size = 0)
    : m_size(size)
    , m_array(m_size ? new T[m_size]() : nullptr)
  {
  }
  // (copy) constructor
  Array(const Array<T> & arr)
  : m_size(arr.m_size)
  , m_array(m_size ? new T[m_size]() : nullptr)
  {
      try 
      {
      std::copy(arr.m_array,arr.m_array + m_size, m_array); 
      } catch(...)
      {
          delete[] m_array;
          throw;
      }
  }
    
  // (move) constructor
  Array(const Array<T>&& arr)
  :  m_size(std::move(arr.m_size))
  , m_array(std::move(arr.m_array))
  {
  }
  
  ~Array()
  {
      delete[] m_array;
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
  /*size_t getSize()
  {
      return m_size;
  }
  T* getArray()
  {
      return m_array;
  }*/
private:
  size_t m_size;
  T* m_array;
};
