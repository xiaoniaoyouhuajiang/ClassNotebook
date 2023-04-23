#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>
class Array
{
public:
  // (default) constructor
  Array(const size_t size = 0): m_size(size), m_array(m_size ? new T[m_size]() : nullptr){}

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
   Array(Array const& a): m_size(a.m_size), m_array(m_size ? new T[m_size]: nullptr)
   {
       if (m_size)
           std::copy(a.m_array, a.m_array + a.m_size,m_array);
   }
    //assignment operator
    Array& operator=(Array const& a)
    {
      if (this != &a)
      {
          T* buffer = nullptr;
          try {
              if (a.m_size) {
                buffer = new T[a.m_size];
                std::copy(a.m_array, a.m_array + a.m_size,buffer);
              } else {
                  m_array = nullptr;
                  m_size = 0;
              }
          }
          catch (...) {
                delete[] buffer;
                throw;
          }
          delete[] m_array;
          m_size = a.m_size;
          m_array = buffer;
      }
        return *this;
    }
    //move constructor
    Array(Array&& a): m_array(a.m_array), m_size(a.m_size)
    {
        a.m_array = nullptr;
        a.m_size = 0;
    }
    ~Array()
    {
        delete [] m_array;
    }
private:
  size_t m_size;
  T* m_array;
};