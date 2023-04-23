#include <assert.h>
#include <iostream>
#include <algorithm> // std::copy
#include <cstddef> // size_t


template<typename T>
class Array
{
public:
  // (default) constructor
  Array(const size_t size = 0): m_size(size), m_array(m_size ? new T[m_size]() : nullptr)
  {
  }

  // copy constructor
  Array(const Array& arr): m_size(arr.m_size), m_array(m_size ? new T[m_size]() : nullptr)
  {
      try{
          std::copy(arr.m_array,arr.m_array+arr.size(),m_array);
      }
      catch (...) {
          delete[] m_array;
          throw;
      }
  }

  // move constructor
  Array(const Array&& arr) : m_size(arr.m_size), m_array(arr.m_array)
  {
      m_array = nullptr;
      m_size = 0;
  }

  //operator =
  Array& operator = (const Array& arr)
  {
      Array temp(arr);
      m_size = temp.m_size;
      m_array = m_size ? new T[m_size]() : nullptr;
      std::copy(temp.m_array, temp.m_array+temp.size(),m_array);
      return *this;
  }

  //destructor
  ~Array(){
      delete[] m_array;
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

void print(Array<int> &arr){
    for(int i=0; i<5; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
    return;
}

int main()
{
    Array<int> arr(5);
    for(int i=0; i<5; i++){
        std::cin >> arr[i];
    }

    std::cout << "Array: ";
    print(arr);

    Array<int> arr_copy(arr);
    Array<int> arr3(Array<int>(Array<int>(5)));

    std::cout << "Array copy: ";
    print(arr_copy);

    std::cout << "Array 3: "<<arr3.size();
    print(arr3);

    arr3 = arr;
    std::cout << "Array 3 = arr: ";
    print(arr3);
    return 0;
}
