#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

#ifndef ARRAY_H
#define ARRAY_H

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

  // (copy) constructor
  Array(const Array& arr)
    : Array(arr.m_size)
  {
        try
        {
            for(size_t i=0; i<m_size; i++)
                m_array[i] = arr.m_array[i];
        }
        catch(...)
        {
            delete[] m_array;
            throw;
        }

  }

  // (move) constructor
  Array(Array&& arr)
    : m_size(arr.m_size)
    , m_array(arr.m_array)
  {
      arr.m_size = 0;
      arr.m_array = nullptr;
  }

  // operator =
  Array& operator=(const Array& arr)
  {
      if(this != &arr)
      {
          T* new_m_array = arr.m_size ? new T[arr.m_size]() : nullptr;
          try
          {
              for(size_t i=0; i<arr.m_size; i++)
                  new_m_array[i] = arr.m_array[i];
              delete[] m_array;
              m_array = new_m_array;
              m_size = arr.m_size;
          }
          catch(...)
          {
              delete[] new_m_array;
              throw;
          }
      }
      return *this;
  }


  const size_t size() const
  {
    return m_size;
  }

  T* get_array() const
  {
      return m_array;
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

#endif // ARRAY_H
