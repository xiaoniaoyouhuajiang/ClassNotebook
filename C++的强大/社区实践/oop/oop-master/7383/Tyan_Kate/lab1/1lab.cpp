#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t

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
    
    Array(const Array & other) try :m_size(other.m_size), m_array(new T[other.m_size])
    {
        std::copy(other.m_array,(other.m_array)+(other.m_size),m_array);
    }
    catch(...){
        throw;
    };
    
    Array & operator = (const Array & other){
        if(this!=&other){
            unique_ptr<T[]> mdata(new T[other.m_size]);
            std::copy(other.m_array,(other.m_array)+(other.m_size),mdata.get());
            T* data= new T[m_size];
            std::copy(m_array,m_array+m_size,data);
            delete[] m_array;
            try{
                size_t t1=other.m_size;
                m_array= new T[t1];
                m_size = t1;
                m_array=mdata.release();
            }catch(...){
                m_array= new T[m_size];
                std::copy(data,data+m_size,m_array);
                throw;
            }
            delete [] data;
        }
        return *this;
    }
    
    void move(Array& other){
        size_t t1=m_size;
        m_size=other.m_size;
        other.m_size=t1;
        
        T* const data=m_array;
        m_array=other.m_array;
        other.m_array=data;
    }
    
    ~Array(){
        delete[] m_array;
    }
private:
    size_t m_size;
    T* m_array;
};
