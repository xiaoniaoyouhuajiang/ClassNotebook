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
    
  // copy constructor
  Array(const Array& obj)
      : m_size(obj.size())
      , m_array(obj.size() ? new_copy(obj.m_array, obj.size()) : nullptr)
  {
  }
   
  //move constructor
  Array(Array&& obj)
    : m_size(obj.size()), m_array(nullptr)
  {
    m_array = obj.m_array;
    obj.m_size = 0;
    obj.m_array = nullptr;
  }
  
  //assignment operator
  Array& operator=(Array& obj){
    if(this != &obj){
    T* temp;
    temp = new_copy(obj.m_array, obj.m_size);
    if(temp){
    delete[] m_array;
    m_size = obj.size();
    m_array = temp;
    }
    }
    return *this;
  }
   
  //move assignment operator
  Array& operator=(Array&& obj){
    std::swap(m_array, obj.m_array);
    std::swap(m_size, obj.m_size);
    return *this;
  }
  
  //destructor
  ~Array(){
    delete[] m_array;
    m_size = 0;     
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
    
  //copy array [safe]
  T* new_copy(T* arr, size_t size){
      T* new_array = new T[size];
        try{
            std::copy(arr, arr + size, new_array);
        }
        catch(...){
            delete[] new_array;
            throw;
        }
      return new_array;
  }
    
};

int main(){
	
	return 0;
}