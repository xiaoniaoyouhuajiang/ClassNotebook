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
      
  //Деструктор  
   ~Array() { delete [] m_array;}
  //Конструктор копирования  
   Array(const Array& obj) : m_size(obj.size()), m_array ( m_size ? new T[m_size]() : nullptr)
   {  
     std::copy(obj.m_array,obj.m_array+m_size,m_array);    
   }
   //Оператор присваивания   
   Array &operator=(const Array& obj)
   {
     if(this!=&obj)
     {
     size_t backup_size=m_size;
     T backup [backup_size];
     std::copy(m_array,m_array+backup_size,backup);
      try
      {
          if(m_array!=nullptr)
          {
          delete [] m_array;
          m_size=0;
          m_array=nullptr; 
          }
          m_size=obj.size();
          if(m_size!=0)
          {
          m_array= new T[m_size]();
          std::copy(obj.m_array,obj.m_array+m_size,m_array);
          }
      }
      catch(std::exception & err)
      {
        m_size=backup_size;
        std::copy(backup,backup+backup_size,m_array);
      } 
     }
     return *this;
   }
   //Конструктор перемещения
   Array(const Array &&obj) :m_size(obj.m_size),m_array(obj.m_array)
   {
          obj.m_size=0;
          obj.m_array=nullptr;
   }
    
   

private:
  size_t m_size;
  T* m_array;
};
