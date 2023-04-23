#include <iostream>
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
        std::cout << "def" << std::endl;
	}
    
	//copy constructor
	Array(const Array &other)
    : m_size(other.m_size)
    , m_array(m_size ? new T[m_size]() : nullptr) 
    {
        std::cout << "copy constr" << std::endl;
        std::copy(other.m_array, other.m_array+other.m_size, m_array);
    }
    
    //copy assigment operator
    Array& operator=(const Array& other)
    {
	std::cout << "copy assigment operator" << std::endl;
        if(this==&other) return *this;
        Array buf(other.m_size);
        std::copy(other.m_array, other.m_array + other.m_size, buf.m_array);
        delete []m_array;
        m_size = buf.m_size;
        m_array = m_size ? new T[m_size]() : nullptr;
        std::copy(buf.m_array, buf.m_array + buf.m_size, m_array);
        return *this;
    }
    
    //move constructor
    Array(Array&& other)
    : m_array(other.m_array)
    , m_size(other.m_size) {
        std::cout << "move constr" << std::endl;
        other.m_array = nullptr;
        other.m_size = 0;
    }
    //move assingnment operator
    Array& operator=(Array&& other) 
    {
        std::cout << "move assigment operator" << std::endl;
       if(&other==this) return *this;
        delete [] m_array;
        m_array = other.m_array;
        m_size = other.m_size;
        other.m_array = nullptr;
        other.m_size = 0;
        return *this;
    }
    
    ~Array(){
         
            delete[] m_array;
          //  std::cout << "des" << std::endl;
	}
      

	const size_t size() const{
		return m_size;
	}

	T& operator [](const size_t index){
		assert(index < m_size);
		return m_array[index];
	}

private:
	size_t m_size;
	T* m_array;
};

int main(){
	Array <int>a = Array <int>(4);
	Array <int> b(6);
	a = b;
	a = Array <int> (8);
   // Array <int> c = Array <int> (5);
	Array <int> c = a;
	Array <int> d = std::move(a);	return 0;
}