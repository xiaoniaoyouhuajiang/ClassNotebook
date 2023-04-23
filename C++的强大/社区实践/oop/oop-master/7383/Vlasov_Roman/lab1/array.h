#include <assert.h>
#include <iostream>
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

  Array(const Array &a) //copy constructor
  {
      size_t tmps = a.m_size;
      T* tmpa = tmps ? new T[tmps]() : nullptr;
      try {
          for (size_t i = 0; i < tmps; i++)
              tmpa[i] = a.m_array[i];
      } catch (...) {
          delete[] tmpa;
          throw;
      }
      this->m_size = tmps;
      this->m_array = tmpa;
      
  }
  Array(Array &&a) //move constructor
  {
      this->m_size = a.m_size;
      this->m_array = a.m_array;
      a.m_array = nullptr;
  }
  Array & operator=(const Array &a) //copy assignment operator
  {
      if(&a == this)
          return *this;
      
      size_t tmps = a.m_size;
      T* tmpa = tmps ? new T[tmps]() : nullptr;;
      try {
          for (size_t i = 0; i < tmps; i++)
              tmpa[i] = a.m_array[i];
      } catch (...) {
          delete[] tmpa;
          throw;
      }
      delete this->m_array;
      this->m_size = tmps;
      this->m_array = tmpa; 
      return *this;
  }
  Array & operator=(Array &&a) //move assignment operator
  {
      if (&a == this)
          return *this;
      
      delete this->m_array;
      this->m_size = a.m_size;
      this->m_array = a.m_array;
      a.m_array = nullptr;
      return *this;
  }
  ~Array()
  {
      delete[] this->m_array;
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
