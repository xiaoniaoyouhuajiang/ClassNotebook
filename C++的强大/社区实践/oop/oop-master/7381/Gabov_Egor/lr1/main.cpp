#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>
class Array{
public:
  Array(const size_t size = 0)
    : m_size(size)
    , m_array(m_size ? new T[m_size]() : nullptr){}
    
 Array(Array const& a)
    :m_size(a.m_size), m_array(new T [m_size])
  {
    try
    {
      for(size_t i = 0; i != m_size; ++i)
        m_array[i] = a.m_array[i];
    }
    catch(...)
    {
      delete [] m_array;
      throw;
    }
  }

  void swap(Array & a) {
		std::swap(this->m_size, a.m_size);
		std::swap(this->m_array, a.m_array);
	}

	Array(Array&& a) {
		if (this != &a)
			swap(a);
	}

	Array& operator=(Array const& a) {
		if (this != &a) {
			Array(a).swap(*this);
		}
		return *this;
	}

  const size_t size() const{
    return m_size;
  }

  T& operator [](const size_t index){
    assert(index < m_size);

    return m_array[index];
  }

  ~Array(){
      delete [] m_array;
  }

private:
  size_t m_size;
  T* m_array;
};
