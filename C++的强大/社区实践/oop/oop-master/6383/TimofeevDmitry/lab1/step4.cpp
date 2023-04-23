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
  
  Array(Array &x){
      m_size=x.m_size;
      m_array=(x.m_size ? new T[x.m_size]() : nullptr);
      std::copy(x.m_array,x.m_array+m_size,m_array);
  }
    
  Array & operator = (Array &x){
      std::unique_ptr<T[]> sp(new T[x.m_size]); // для освобождения памяти при исключениях
      std::copy(x.m_array,x.m_array+x.m_size,sp.get());
      delete[] m_array;
      m_size = x.m_size;
      m_array = sp.release(); // копирование прошло успешно, освоюождать память не надо
      return *this;
  }
  
  Array(Array &&x){
     m_size=x.m_size;
     m_array=x.m_array;
     x.m_array=nullptr;
  }
  
  ~Array(){
     delete[] m_array;
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