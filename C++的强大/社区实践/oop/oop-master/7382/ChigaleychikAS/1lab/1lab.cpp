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

  Array(const Array &other)
  {
      //std::cout<<"Copy constructor"<<std::endl;
      if (this != &other){
        this->m_size = other.m_size;
        this->m_array = new T[other.m_size];
        std::copy(other.m_array,other.m_array+other.m_size,this->m_array);
      }
  }
  
  Array( Array &&other)
  {

    if (this != &other)
    {
        this->m_size = other.m_size;
        this->m_array = std::move(other.m_array);
    }
  }
  
  Array operator = (const Array &other)
  {
    //std::cout<<"Operator = ";
    if (this != &other)
    {
        Array<T> tmp(this->m_size);
        std::copy(this->m_array,this->m_array+this->m_size,tmp.m_array);
        try 
        {
            this->m_size = other.m_size;
            delete[] m_array;
            m_array = new T[m_size];
            for (size_t i = 0; i < other.m_size; ++i)
            {      
                this->m_array[i] = other.m_array[i];
            }
        }
        catch (std::exception e)
        {
            delete[] m_array;
            this->m_array = std::move(tmp.m_array);  
            this->m_size = tmp.m_size;    
            throw;  
        }
    }
    return *this;
  }

  Array operator = (Array &&other)
  {
      //std::cout<<"moving operator =";
      if (this != &other)
      {
        this->m_size = other.m_size;
        this->m_array = std::move(other.m_array);
      }
      return *this;
  }
  //
  const size_t size() const
  {
    return m_size;
  }

  ~Array()
  {
    delete[] m_array;
  }
  T& operator [](const size_t index)
  {
    assert(index < m_size);

    return m_array[index];
  }
  
  void print()
  {
      for (size_t i = 0;i < (this->m_size);++i)
      {
          std::cout <<this->m_array[i]<<" ";
      }
    std::cout<<std::endl;
  }
private:
  size_t m_size;
  T* m_array;
};
