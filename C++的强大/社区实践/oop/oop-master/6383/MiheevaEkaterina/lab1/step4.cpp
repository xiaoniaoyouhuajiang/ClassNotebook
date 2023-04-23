#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <iostream>
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

 //destructor 
    ~Array(){
       delete []m_array;
    }
    //copy
     Array(Array &a)
    {
        m_size = a.m_size;
        m_array = new T[m_size];
         for (int i=0;i<a.m_size;i++) m_array[i] = a.m_array[i];
    }
 
   // move constructor
    
    Array (Array && a){
      m_size = a.m_size;
      m_array = a.m_array;
        std::copy ( a.m_array, a.m_array+a.m_size, m_array);
    }
    //operator =
    Array & operator = ( Array & a){   
      T* arr= new T[a.m_size];
      std::unique_ptr<T[]> p(arr); 
      std::copy(a.m_array,a.m_array+a.m_size,p.get());
      delete[] m_array;
      m_size = a.m_size;
      m_array = p.release(); //снимаем контроль над указателем, если не брошено исключение
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

private:
  size_t m_size;
  T* m_array;
};