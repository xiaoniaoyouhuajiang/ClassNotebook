  #include <assert.h>
  #include <algorithm> // std::copy
  #include <cstddef> // size_t
  #include <iostream>
  using namespace std;
  template<typename T>
  class Array
  {
  public:
    // (default) constructor
    Array(const size_t size = 0): m_size(size), m_array(m_size ? new T[m_size]() : nullptr){
      for (size_t i = 0; i != m_size; i++) *(m_array + i) = i;
    }

    Array(const Array& CopySource) : m_size(CopySource.size()), m_array(m_size ? new T[m_size]() : nullptr)
    {
        try{
          copy(CopySource.m_array, CopySource.m_array+CopySource.size(), m_array);
        }
        catch(...){
          delete [] m_array;
          throw;
        }
    }

    Array& operator= (const Array& CopySource){
      if(this !=&CopySource){
          Array tmp(CopySource);
          m_size = tmp.size();
          m_array = m_size ? new T[m_size]() : nullptr;
          copy(tmp.m_array, tmp.m_array+tmp.size(), m_array);
      }
      return *this;
    }

    Array(Array&& MoveSource): m_size(MoveSource.size()), m_array(MoveSource.m_array) {
        MoveSource.m_array = nullptr;
    }

    Array& operator= (Array&& MoveSource){
      this->~Array();
      m_size = MoveSource.size();
      m_array = MoveSource.m_array;
      MoveSource.m_array = nullptr;
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
      m_size = 0;
    }
    void out()
  	{
  		for (size_t i = 0; i < m_size; i++)
  			cout << m_array[i] << " ";
  		cout << endl;
  	}

  private:
    size_t m_size;
    T* m_array;
  };
  int main()
  {
  	Array<double> arr_1(12);
  	Array<double> arr_2 = arr_1;
  	Array<double> arr_3(arr_1);
  	Array<double> arr_6(8);
  	arr_1 = arr_6;
  	Array<double> arr_4(10);
  	arr_4 = arr_1;
  	arr_1 = arr_2;
  	arr_1.out();
  	arr_2.out();
  	arr_3.out();
  	arr_4.out();
  	return 0;
  }
