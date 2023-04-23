#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <exception>

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
	Array(const Array& arr1){
        m_size=arr1.m_size;
        if (arr1.m_size){
		    m_array= new T[m_size]();
            std::copy(arr1.m_array,arr1.m_array+m_size,m_array);
        }
        else m_array=nullptr;
	}
	Array(Array&& arr1){
        m_array=nullptr;
        m_size=0;
        std::swap(m_array,arr1.m_array);
        std::swap(m_size,arr1.m_size);
	}
	~Array(){
		delete [] m_array;
	}
	Array& operator=(const Array& arr1){
        T* tmp=m_array;
        try{
    		m_array= arr1.m_size ? new T[arr1.m_size]() : nullptr;
    		std::copy(arr1.m_array,arr1.m_array+arr1.m_size,m_array);
        }
        catch(std::exception & e){
            if (tmp != m_array){
                delete [] m_array;
                m_array=tmp;
            }
            throw;
        }
        delete [] tmp;
        m_size=arr1.m_size;
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

