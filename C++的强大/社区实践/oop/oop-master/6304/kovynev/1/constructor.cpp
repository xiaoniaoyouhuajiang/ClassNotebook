#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <memory>
#include <iostream>

template<typename T>
class Array
{
private:
  size_t m_size;
  std::unique_ptr <T[]> m_array;
    
public:
  // (default) constructor
  Array(const size_t size = 0)
    : m_size(size)
    , m_array(m_size ? new T[m_size]() : nullptr)
  {
  }
        
  //Конструктор копирования
  Array(const Array& obj)
     : m_size(obj.m_size)
    , m_array(m_size ? new T[m_size]() : nullptr)
  {
      std::copy(obj.m_array.get(), obj.m_array.get() + m_size, m_array.get());  
  }
    
     //Оператор присваивания
    Array& operator=(Array obj)
    {
        std::swap(m_size, obj.m_size);
        std::swap(m_array, obj.m_array);
        return* this;
    }
    
    //Конструктор перемещения
    Array(Array&& obj)
    {
        m_array=move(obj.m_array);
        swap(m_size, obj.m_size);
        obj.m_size = 0;
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

};