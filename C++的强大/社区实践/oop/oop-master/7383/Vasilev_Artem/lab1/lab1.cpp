#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>
class Array
{
public:
    
  Array(const size_t size = 0) : m_size(size), m_array(m_size ? new T[m_size]() : nullptr)
  {
  }
    
  Array (const Array& old) : m_size(old.m_size), m_array(m_size ? new T[m_size]() : nullptr)
    {
      try {
        for (size_t i = 0; i < m_size; i++)
            m_array[i] = old.m_array[i];
      }
      
      catch (...)
      {
          delete [] m_array;
          throw;
      }
    }
    
    Array (const Array&& old) : m_size(old.m_size), m_array(old.m_array)
    {
        old.m_size = 0;
        old.m_array = nullptr;
    }
    
    
    void swap(Array & old) {
		std::swap(this->m_size, old.m_size);
		std::swap(this->m_array, old.m_array);
	}


	Array(Array&& old) {
		if (this != &old)
			swap(old);
	}

	Array & operator=(Array const & old) {
		if (this != &old) {
			Array(old).swap(*this);
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
    
  ~Array() 
  {
     delete [] m_array;
  }

private:
  size_t m_size;
  T* m_array;
    

};
