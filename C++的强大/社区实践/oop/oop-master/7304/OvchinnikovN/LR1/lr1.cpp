#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <iostream>

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
    
    ~Array(){
            delete [] m_array;
    }
    
    Array(const Array &other){
            this->m_size = other.m_size;
            m_array = new T[this->m_size];

            for(size_t i = 0; i<this->m_size; i++)
                this->m_array[i] = other.m_array[i];
    }
    
    Array & operator = (const Array &other){
        size_t saveSize = this->m_size;
        T saveArr[saveSize];
        std::copy(this->m_array, this->m_array+saveSize, saveArr);
        
        if(this != &other){
            try {
                delete [] m_array;
                m_size = other.m_size;
                m_array = new T[other.m_size];
                std::copy(other.m_array, other.m_array + other.m_size, m_array);
            }
            catch(...) {
                if(this->m_array != nullptr)
                    delete [] this->m_array;
                this->m_size = saveSize;
                this->m_array = new T[saveSize];
                std::copy(saveArr, saveArr+saveSize, this->m_array);
            }
            return *this;
        }
    }
    
    Array(Array &&other){
        this->m_size = other.m_size;
        this->m_array = other.m_array;
        other.m_size = 0;
        other.m_array = nullptr;
    }
        
private:
  size_t m_size;
  T* m_array;
};