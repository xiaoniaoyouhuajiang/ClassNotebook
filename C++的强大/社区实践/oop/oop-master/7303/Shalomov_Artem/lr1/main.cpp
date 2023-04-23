#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
using namespace std;
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
  //copy constructor
  Array(Array& t)
      : m_size(t.m_size)
      , m_array(m_size ? new T[m_size]() : nullptr){
      try{
          copy(t.m_array,  t.m_array + t.m_size, m_array);
      }catch(...){
          delete [] m_array;
          m_array = nullptr;
          m_size = 0;
          throw;
      }
  }
  //move constructor
  Array(Array &&t)
      : m_size(t.m_size)
      , m_array(t.m_array){
      t.m_size = 0;
      t.m_array = nullptr;
  }
  //copy assignment
  Array& operator=(const Array& t){
      T* arr_b = m_array;
      size_t size_b = m_size;
      unique_ptr<T[]> p(new T[t.m_size]);
      try{
          copy(t.m_array,t.m_array + t.m_size, p.get());
          m_size = t.m_size;
          m_array = p.release();
          delete [] arr_b;
      }catch(...){
          m_size = size_b;
          m_array = arr_b;
          throw;
      }
      return *this;
  }
    ~Array(){
       delete [] m_array;
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