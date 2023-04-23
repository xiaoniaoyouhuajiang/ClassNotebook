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

   Array(const Array& arr)
  {
      *this = arr;
  }

   Array(Array&& arr)
  {
      m_array = arr.m_array;
	  m_size = arr.m_size;
	  
	  arr.m_array = nullptr;
  }

   Array& operator=(const Array& arr)
  {
      Array tmp(arr.m_size);

       std::copy(arr.m_array, arr.m_array + arr.m_size, tmp.m_array);

       m_size = tmp.m_size;
      m_array = m_size ? new T[m_size]() : nullptr;

       std::copy(tmp.m_array, tmp.m_array + tmp.m_size, m_array);

       return *this;
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

   ~Array()
  {
      delete[] m_array;
  }

 private:
  size_t m_size;
  T* m_array;
};
