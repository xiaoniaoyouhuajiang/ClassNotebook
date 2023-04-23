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
  void swap(Array & a){
      size_t const t1 = m_size;
      m_size = a.m_size;
      a.m_size = t1;
      
      T * const t2 = m_array;
      m_array = a.m_array;
      a.m_array = t2;
  }
  Array(Array const& a){
       Array tmp(a.m_size);
      for (size_t i = 0; i < tmp.m_size;i++){
          tmp.m_array[i] = a.m_array[i];
      }
      m_size = tmp.m_size;
      m_array = m_size ? new T[m_size]() : nullptr;
      for (size_t i = 0;i < m_size;i++){
          m_array[i] = tmp.m_array[i];
      }
  }
                                 
  Array & operator = (Array const & a){
      if (this != &a)
          Array(a).swap(*this);
      return *this;
  }
                                 
  Array (Array&& other){
      Array tmp(other.m_size);
      for (size_t i = 0; i < tmp.m_size;i++){
          tmp.m_array[i] = other.m_array[i];
      }
      m_size = tmp.m_size;
      m_array = m_size ? new T[m_size]() : nullptr;
      for (size_t i = 0;i < m_size;i++){
          m_array[i] = tmp.m_array[i];
      }
      other.~Array();
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
      if (m_array)
          delete[] m_array;
  }
private:
  size_t m_size;
  T* m_array;
};

int main(){
    Array<int> tmp(5);
    Array<int> a_copy(tmp);

    Array<int> a_move = CreateArray(Array<int>(10));

    Array<int> oper (4);
    oper = tmp;
}
