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
  Array & operator = (Array const &a) // Оператор присваивания
  {
      if (this != &a)
      {

          T* nm_array = a.m_size ? new T[a.m_size]() : nullptr;
          try
          {
              std::copy(a.m_array, a.m_array + a.m_size, nm_array);
              delete[] m_array;
              m_array = nm_array;
              m_size = a.m_size;
          }
          catch(...)
          {
              delete[] nm_array;
              throw;
          }            
      }
      return *this;
  }
  Array(Array const & a) // Конструктор копирования
      : m_size(a.m_size), m_array(a.m_size ? new T[a.m_size]() : nullptr)
      {
          if (this->m_array != nullptr && a.m_array != nullptr)
              std::copy(a.m_array, a.m_array + a.m_size, m_array);
      }
  Array(Array &&a) // Перемещающий конструктор
  {
      std::swap(m_size, a.m_size);
      std::swap(m_array, a.m_array);
  }
  ~Array() 
    {
        delete[] m_array;
    }
private:
  size_t m_size;
  T* m_array;
};