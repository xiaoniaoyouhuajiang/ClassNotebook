#include <assert.h>
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

      std::cout << "Default constructor\n";
  }

  void print()
  {
      for(size_t it=0; it < m_size; it++)
          std::cout << m_array[it] << ", ";
      std::cout << "\n";
  }

  // copy constr
  Array(const Array& src) : Array(src.size())
  {
      std::cout << "Copy constructor\n";
      if(src.size())
          for(size_t it=0; it < src.size(); it++)
              m_array[it] = src[it];
  }

  // move constr
  Array(Array&& src) : Array(src.size())
  {
      std::cout << "Move constructor\n";
      if(src.size())
          for(size_t it=0; it < src.size(); it++)
              m_array[it] = src[it];
  }

  // copy "=" operator
  Array& operator=(const Array& src)
  {
      std::cout << "Copy Operator = \n";

      delete m_array;
      m_size = src.size();
      m_array = new T[m_size];
      if(m_size)
          for(size_t it=0; it < m_size; it++)
              m_array[it] = src[it];
      else
          m_array = nullptr;
      return *this;
  }

  // оператор перемещения
  Array& operator=(Array&& src)  
  {
      std::cout << "Move Operator = \n";
      
      std::swap(m_array, src.m_array);
      m_size = src.size();
  }

  size_t size() const
  {
      return m_size;
  }

  T& operator [](const size_t index) const
  {
      assert(index < m_size);
      return m_array[index];
  }

  ~Array() { delete[] m_array; }

private:
    size_t m_size;
    T* m_array;
};

int main()
{
    Array<int> a(10);
    std::cout << "_________________________________\n";

    Array<int> b(a);
    std::cout << "_________________________________\n";

    Array<int> arr(23);
    arr = b;
    arr.print();
    std::cout << "_________________________________\n";

    Array<int> ex(std::move(a));
    std::cout << "_________________________________\n";

    Array<int> ex2(13);
    ex2 = std::move(b);
    ex2.print();
    std::cout << "_________________________________\n";

    return 0;
}
