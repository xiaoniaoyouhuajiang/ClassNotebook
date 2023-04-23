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
    Array(const size_t size = 0)
        : m_size(size)
        , m_array(m_size ? new T[m_size]() : nullptr)
    {
        cout << "Default constructor" << endl;
    }

    Array(const Array& initial_array)
        :m_size(initial_array.size())
        , m_array(m_size ? new T[m_size]() : nullptr)
    {
        cout << "Copy constructor" << endl;
            for (int i = 0; i < m_size; i++) {
                m_array[i] = initial_array.m_array[i];
        }
    }

    Array& operator=(const Array& initial_array){
        cout << "Copy operator" << endl;
        Array arr(*this);
        try{
            if(this != &initial_array){
                delete m_array;
                m_size = initial_array.size();
                m_array = m_size == 0 ? nullptr: new T[m_size];
                copy(initial_array.m_array, initial_array.m_array+m_size,this->m_array);
            }
        } catch(...){
            m_size = arr.m_size;
            m_array = move(arr.m_array);

        }
        return *this;
    }

    Array(Array&& initial_array):m_size(initial_array.m_size),m_array(initial_array.m_array){
        cout << "Move constructor" << endl;
        initial_array.m_array = nullptr;
        initial_array.m_size = 0;
    }

    Array& operator=(Array&& initial_array){
        cout << "Move operator" << endl;
        if(this != &initial_array){
            delete m_array;
            m_size = initial_array.size();
            m_array = initial_array.m_array;
            initial_array.m_array = nullptr;
            initial_array.m_size = 0;
        }
        return *this;
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

    void print (){
        for (int i = 0; i<m_size; i++) {
            cout << m_array[i] << " ";
        }
        cout << endl;
    }

    ~Array()
    {
        delete[] m_array;
        m_size = 0;
    }

private:
    size_t m_size;
    T* m_array;
};

int main(){
    Array <int> array(4);
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array[3] = 4;
    array.print();
     Array <int> arr(4);
     arr = move(array);
     arr.print();
}
