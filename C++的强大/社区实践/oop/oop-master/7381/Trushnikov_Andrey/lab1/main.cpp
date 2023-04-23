#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <algorithm>
template<typename T>
class Array
{
public:
  // (default) constructor
  Array(const size_t size = 0): m_size(size), m_array(m_size ? new T[m_size]() : nullptr){
  }

  const size_t size() const{
    return m_size;
  }

  T& operator [](const size_t index){
    assert(index < m_size);

    return m_array[index];
  }
  //конструктор копирования
  Array(const Array &array):m_size(array.size()){
      try {
          if(m_size){
              m_array = new T [m_size];
              std::copy(array.m_array, array.m_array+array.m_size, m_array);
          }
          else
              m_array = nullptr;
      } catch (...) {
        if(m_array)
            delete []m_array;
        m_size = 0;
      }
  }
  // конструктор оператора присваивания
  Array & operator= (Array & array){
      if(this != &array){
          T* tmp_array = nullptr;
          try {
              if(array.m_size){
                  tmp_array = new T [array.m_size];
                  std::copy(array.m_array, array.m_array+array.m_size, tmp_array);
              }
              else
                  tmp_array = nullptr;

          } catch (...) {
              delete [] tmp_array;
              throw;
          }
          delete[] m_array;
          m_array = tmp_array;
          m_size = array.m_size;
      }
  }
  // конструктор перемещения
  Array(Array && array): m_size(array.size()), m_array(array.m_array){
      array.size = 0;
      array.m_array = nullptr;
  }
  //перемещающий оператор присваивания
  Array & operator =(Array && array ){
      if(this != &array){
          T* tmp_array = nullptr;
          try {
              if(array.m_size){
                  tmp_array = new T [array.m_size];
                  std::copy(array.m_array, array.m_array+array.m_size, tmp_array);
              }
              else
                  tmp_array = nullptr;

          } catch (...) {
              if(tmp_array)
                delete [] tmp_array;
              throw;
          }
          delete[] m_array;
          m_array = tmp_array;
          m_size = array.m_size;
          array.m_array = nullptr;
          array.m_size = 0;
      }
  }

  // деструктор
  ~Array() {
      delete[] m_array;
  }


private:
  size_t m_size;
  T* m_array;
};