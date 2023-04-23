#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef>   // size_t

template<typename T>
class Array
{
public:
  // (default) constructor
  Array(const size_t size = 0) : m_size(size), m_array(m_size ? new T[m_size]() : nullptr)
  {}

  const size_t size() const
  {
    return m_size;
  }

  T& operator [](const size_t index)
  {
    assert(index < m_size);

    return m_array[index];
  }

////////////////////////////////////
  //Конструктор копирования
  Array(const Array& a) : m_size(a.m_size), m_array(m_size ? new T[m_size]() : nullptr)
  {
    std::copy( a.m_array, a.m_array+a.m_size, m_array);
  }

  //Конструктор перемещения
  Array( Array&& a) : m_array(a.m_array), m_size(a.m_size)
  {
    a.m_array = NULL;
    a.m_size  = 0;
  }

  //Оператор присваивания
  Array& operator = ( Array &a)
 {
   T* save_a = m_array;
   size_t save_s = m_size;

   std::unique_ptr<T[]> b( new T[a.m_size] );

   try
   {
       std::copy( a.m_array, a.m_array+a.m_size, b.get() );

       m_size = a.m_size;
       m_array = b.release(); // +b больше не следит за памятью

       delete [] save_a;
   }
   catch(...)
   {
       m_array = save_a;
       m_size  = save_s;
   }

   return *this;
 }


  //Оператор перемещения
  Array& operator = ( Array &&a)
 {
   T*     save_a = m_array;
   size_t save_s = m_size;

   try
   {
       m_size  = a.m_size;
       m_array = a.m_array;

       delete [] save_a;

       a.m_array = NULL;
       a.m_size  = 0;
   }
   catch(...)
   {
       m_array = save_a;
       m_size  = save_s;
   }

   return *this;
 }
    
  ~Array()
  {
      delete[] m_array;
  }

private:
  size_t m_size;
  T* m_array;
};