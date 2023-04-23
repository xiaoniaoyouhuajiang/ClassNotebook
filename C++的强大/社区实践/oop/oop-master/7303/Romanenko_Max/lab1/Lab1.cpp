#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>
class Array
{
public:
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
    
    
  Array(const Array& orig)
      : m_size(orig.m_size)
      , m_array(m_size ? new T[m_size]() : nullptr){
      try{
          std::copy(orig.m_array,  orig.m_array + orig.m_size, m_array);
      }catch(...){
          delete [] m_array;
          m_array = nullptr;
          m_size = 0;
          throw;
      }
  }
  
  Array(Array&& orig)
      : m_size(std::move(orig.m_size))
      , m_array(std::move(orig.m_array)){
      orig.m_array = nullptr;
  }
  
  Array& operator=(const Array& orig){
      if (&orig == this)
			return *this;
      
      T* arr_old = m_array;
      size_t size_old = m_size;
      std::unique_ptr<T[]> a(new T[orig.m_size]);
      try{
          std::copy(orig.m_array,orig.m_array + orig.m_size, a.get());
          m_size = orig.m_size;
          m_array = a.release();
          delete [] arr_old;
      }catch(...){
          m_size = size_old;
          m_array = arr_old;
          throw;
      }
      return *this;
  }
    
  ~Array(){
      delete [] m_array;
  }

private:
  size_t m_size;
  T* m_array;
};
