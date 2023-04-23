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

  ~Array()
	{
		destroy();
	}
    
 
    
  Array(const Array& obj)
      : m_size(obj.m_size)
      , m_array(m_size ? new T[m_size]():nullptr)
      {
            std::copy(obj.m_array, obj.m_array + obj.m_size, m_array);
      }
  
  Array(Array && obj)
      {
          if (this != &obj){
          this->m_size = obj.m_size;
          this->m_array = obj.m_array;
          
          obj.m_array = nullptr;
          obj.m_size = 0;// Mark the other object as "empty"
          }
      }
  
  Array& operator=(Array & obj)
  {
      if (this != &obj) {           // If the object isn't being called on itself
          T* temp= new T[obj.m_size];
          std::unique_ptr<T[]> ptr(temp); 
          std::copy(obj.m_array,obj.m_array+obj.m_size,ptr.get());
          delete[] m_array; 
          this->m_size = obj.m_size;
          this->m_array = ptr.release(); 
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
  void destroy()
	{
		delete[] m_array;
        m_size = 0;
  }
  size_t m_size;
  T* m_array;
};