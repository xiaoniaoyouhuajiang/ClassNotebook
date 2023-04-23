#include <iostream>
#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
 
using namespace std;
 
template<typename T>
class Array {
    public:
        // (default) constructor
        Array(const size_t size = 0)
            : m_size(size)
            , m_array(m_size ? new T[m_size]() : nullptr) {
        }
 
        // destructor
        ~Array() {
            delete [] m_array;
        }
 
        // return size of Array
        const size_t size() const {
            return m_size;
        }
 
        T& operator [](const size_t index) {
            assert(index < m_size);
            return m_array[index];
        }
 
        // copy constructor
        Array(const Array& rst)
            : m_size(rst.m_size),
              m_array(m_size ? new T[m_size] : nullptr) {
            try {
                copy(rst.m_array, rst.m_array + m_size, m_array);
            } catch(...) {
                m_size = 0;
                delete [] m_array;
                m_array = nullptr;
                throw;
            }
        }
 
        // 
        friend void swap(Array& first, Array& second) {
            // enable ADL
            using std::swap;
 
            swap(first.m_size, second.m_size);
            swap(first.m_array, second.m_array);
        }
 
        // move constructor
        Array(Array&& rst)
            : Array() {// init by default constructor
            swap(*this, rst);
        }
 
        // move assignment operator
        Array& operator =(Array rst) {
            swap(*this, rst);
            return *this;
        }
 
    private:
        size_t m_size;
        T* m_array;
};
