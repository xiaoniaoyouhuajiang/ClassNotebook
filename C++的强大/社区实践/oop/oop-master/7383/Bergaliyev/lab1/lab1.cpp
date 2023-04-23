#include <assert.h>
#include <algorithm>
#include <cstddef>

template<typename T>
class Array
{
public:
  Array(const size_t size = 0)
    : m_size(size)
    , m_array(m_size ? new T[m_size]() : nullptr)
  {
  }
  Array(Array const& arr)
  {
    m_size = arr.m_size;
    m_array = m_size ? new T[m_size] : nullptr;
    try
    {
      for(int i=0; i<m_size; ++i)
        m_array[i] = arr.m_array[i];
    }
    catch(std::exception& e)
    {
      delete[] m_array;
      m_array = nullptr;
      m_size = 0;
      throw;
    }
  }
  Array(Array&& arr)
    : m_size(arr.m_size)
    , m_array(arr.m_array)
  {
    arr.m_size = 0;
    arr.m_array = nullptr;
  }
  Array& operator=(Array const& arr)
  {
    Array new_arr(arr);
    std::swap(m_array, new_arr.m_array);
    std::swap(m_size, new_arr.m_size);
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
  ~Array(){
    delete[] m_array;
  }

private:
  size_t m_size;
  T* m_array;
};
