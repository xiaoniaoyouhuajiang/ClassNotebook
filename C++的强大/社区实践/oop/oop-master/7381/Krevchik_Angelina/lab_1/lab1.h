
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
    
   ~Array()                //деструктор
    {
        delete[] m_array;
    }
    

  
    
    Array(const Array& object): Array(object.m_size) //конструктор копирования
  {
        try
        {
            std::copy(object.m_array, object.m_array + m_size, m_array);
        }
        catch(...)
        {
            delete[] m_array;
            throw;
        }

  }


  Array(Array&& object) {    //конструктор перемещения
        m_size = object.m_size;
        m_array = object.m_array;
        
        object.m_size = 0;
        object.m_array = nullptr; 
    }


  Array& operator=(const Array& object)         // оператор присваивания
{ 
    if (this != &object) 
    {
        size_t newSize = object.m_size;
        T* newArray = nullptr;                      
        if(newSize)
            newArray = new T[newSize]();
        try
        {
            std::copy(object.m_array, object.m_array + newSize, newArray); 
        }
        catch(...)
        {
            delete [] newArray;
            throw;
        }    
        m_size = newSize;                       // replace the old data (all are non-throwing)
        m_array = newArray;
    }

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