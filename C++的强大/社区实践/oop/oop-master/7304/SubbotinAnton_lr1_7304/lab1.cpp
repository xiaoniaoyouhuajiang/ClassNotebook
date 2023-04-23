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

  Array(const Array& arr) : m_size(arr.m_size), m_array(m_size ? new T [m_size] : nullptr)
  {
      try
      {
          std::copy(arr.m_array, arr.m_array + arr.m_size, m_array);
      }
      catch(...)
      {
          delete[] m_array;
          throw;
      }
  }

  Array(Array&& arr) : m_size(arr.m_size), m_array(arr.m_array)
  {
      arr.m_array = nullptr;
  }

  Array& operator=(Array& arr)
  {
      if(this != &arr)
      {
          T* tmp = nullptr;
          try
          {
              arr.m_size ? tmp = new T[arr.m_size] : nullptr;
              std::copy(arr.m_array, arr.m_array + arr.m_size, tmp);
          }
          catch(...)
          {
              delete[] tmp;
              throw;
          }
          m_size = arr.m_size;
          delete[] m_array;
          m_array = tmp;
      }
      return *this;
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

private:
  size_t m_size;
  T* m_array;
};
