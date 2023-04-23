#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

template<typename T>
class Array{
    public:
    // (default) constructor
    Array(const size_t size = 0)
    : m_size(size)
    , m_array(m_size ? new T[m_size]() : nullptr){}

    Array(const Array<T> &src)  // Конструктор копирования (copy constructor)
    : m_size(src.m_size) 
    , m_array(m_size ? new T[m_size]() : nullptr){
    	std::copy(src.m_array, src.m_array + src.m_size, m_array);
    }  

    ~Array(){
    	delete[] m_array;
    }

    Array(Array<T> &&src)  // Конструктор перемещения (move constructor)
{
    	std::swap(m_size, src.m_size);
        std::swap(m_array, src.m_array);
    }

    Array<T>& operator=(const Array<T>& src) { // Оператор присваивания копированием (copy assignment)
	    if (this != &src) {

          T* nm_array = src.m_size ? new T[src.m_size]() : nullptr;
          try {
              std::copy(src.m_array, src.m_array + src.m_size, nm_array);
              delete[] m_array;
              m_array = nm_array;
              m_size = src.m_size;
          }
          catch(...) {
              delete[] nm_array;
              throw;
          }            
      }
      return *this;
    }

    Array<T>& operator=(Array<T>&& src) { // Оператор присваивания перемещением (move assignment) 
	    std::swap(m_size, src.m_size);
        std::swap(m_array, src.m_array);
	    return *this;
    }

    const size_t size() const {
    	return m_size;
    }

    T& operator [](const size_t index) {
        assert(index < m_size);
        return m_array[index];
    }

    private:
    size_t m_size;
    T* m_array;
};