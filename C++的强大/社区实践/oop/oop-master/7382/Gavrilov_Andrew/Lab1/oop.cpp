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
    Array(const Array& el)
            : m_array(el.size() ? new T[el.size()]() : nullptr)
            , m_size(el.size())
    {
	    std::cout<<"Called copying constructor\n";
        for(int i=0;i<el.size();i++)
            m_array[i]=el.m_array[i];
    }
 Array& operator=(const Array& el)
    {
	    std::cout<<"Called operator '='\n";
        if(this!=&el){
            T *arr=nullptr;
            try{
                arr = new T[el.size()];
                for(int i=0;i<el.size();i++)
                    arr[i]=el.m_array[i];
            }
            catch(...){
                delete[] arr;
                throw;
            }
            if(arr!=nullptr){
                m_size=el.size();
                delete[] m_array;
                m_array=arr;
            }
        }
        return *this;
    }

    Array(Array &&el){
        m_size=el.size();
        m_array = el.m_array;
        el.m_array = nullptr;
        el.m_size = 0;   
          std::cout<<"Called move constructor\n";
  }
    ~Array(){
        delete[] m_array;
    }
private:
  size_t m_size;
  T* m_array;
};

int main(){
	Array<int> a(5);
	Array<int> b(a);
	Array<int> c(6);
	a=c;
	Array<int> d(static_cast<Array<int>&&>(a));
}
