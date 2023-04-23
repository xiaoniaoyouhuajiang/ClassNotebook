#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>
class Array{
public:
  // (default) constructor
  Array(const size_t size = 0)
    : m_size(size)
    , m_array(m_size ? new T[m_size]() : nullptr)
  { }

  Array (const Array &obj) : Array(obj.size()) { //copy
      std::copy(obj.m_array, obj.m_array+obj.m_size, m_array);
  }

  Array (Array &&obj):
        m_size(obj.m_size),
        m_array (obj.m_array){ //move

      obj.m_size = 0;
      obj.m_array = nullptr;
  }

  Array& operator =(const Array &obj){
      if (this == &obj) return *this;

      Array tmp(obj);
      m_size = tmp.m_size;
      m_array = m_size ? new T[m_size]() : nullptr;

      std::copy(tmp.m_array, tmp.m_array+tmp.m_size, m_array);

      return *this;
  }

  const size_t size() const {
    return m_size;
  }

  T& operator [](const size_t index){
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
