#ifndef vector_hpp
#define vector_hpp

#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

namespace last
{
 template <typename Type>
  class vector
  {
  public:
    typedef Type* iterator;
    typedef const Type* const_iterator;

    typedef Type value_type;

    typedef value_type& reference;
    typedef const value_type& const_reference;

    typedef std::ptrdiff_t difference_type;

    explicit vector(size_t count = 0)
    {
      if(count){
        m_first=new Type[count];
        m_last=m_first+count;
      }
      else{
        m_first=m_last=nullptr;
      }
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
      difference_type count=last-first;
      if(count){
        m_first=new Type[count];
        m_last=m_first+count;
        std::copy(first,last,m_first);
      }
      else{
        m_first=m_last=nullptr;
      }
    }

    vector(std::initializer_list<Type> init)
    {
      size_t size=init.size();
      if(size){
        m_first=new Type[size];
        m_last=m_first+size;
        std::copy(init.begin(),init.end(),m_first);
      }
      else
        m_first=m_last=nullptr;
    }

    vector(const vector& other)
    {
      size_t size=other.size();
      if(size){
        m_first=new Type[size];
        m_last=m_first+size;
        std::copy(other.m_first,other.m_last,m_first);
      }
      else
        m_first=m_last=nullptr;
    }

    vector(vector&& other)
    {
      m_first=other.m_first;
      m_last=other.m_last;
      other.m_first=other.m_last=nullptr;
    }

    ~vector()
    {
      if(!empty()){
        delete[] m_first;
        m_first=m_last=nullptr;
      }
    }
    //assignment operators
    vector& operator=(const vector& other)
    {
      if(this!=&other){
       if(!empty()){
          delete[] m_first;
          m_first=m_last=nullptr;
        }
        size_t size=other.size();
        if(size){
          m_first=new Type[size];
          m_last=m_first+size;
          std::copy(other.m_first,other.m_last,m_first);
        }
      }
      return *this;
    }

    vector& operator=(vector&& other)
    {
      if(this!=&other){
        if(!empty()){
          delete[] m_first;
        }
        m_first=other.m_first;
        m_last=other.m_last;
        other.m_first=other.m_last=nullptr;
      }
      return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      if(!empty()){
        delete[] m_first;
        m_first=m_last=nullptr;
      }
      difference_type count=last-first;
      if(count){
        m_first=new Type[count];
        m_last=m_first+count;
        std::copy(first,last,m_first);
      }
    }
    // resize methods
    void resize(size_t count)
    {
      if(count && count!=size()){
        iterator tmp=new Type[count];
        if(count>size()){
          std::copy(m_first,m_last,tmp);
        }
        else{
          std::copy(m_first,m_first+count,tmp);
        }
        if(!empty()){
          delete[] m_first;
        }
        m_first=tmp;
        m_last=m_first+count;
      }
      else if(!count && count!=size()){
          delete[] m_first;
          m_last=m_first=nullptr;
      }
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
       if (pos < m_first || pos > m_last)
      {
        throw std::out_of_range("out of range");
      }
      difference_type delpos=pos-m_first;
      std::rotate(m_first+delpos,m_first+delpos+1,m_last);
      resize(size()-1);
      return m_first+delpos;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
      if (first < m_first || first > m_last || last < m_first || last > m_last )
      {
        throw std::out_of_range("out of range");
      }
      difference_type delpos=first-m_first;
      difference_type dellen=last-first;
      std::rotate(m_first+delpos,m_first+delpos+dellen,m_last);
      resize(size()-dellen);
      return m_first+delpos;
    }
        //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
      difference_type newpos=pos-m_first;
      iterator tmp=new Type[size()+1];
      std::copy(m_first,m_first+newpos,tmp);
      tmp[newpos]=value;
      std::copy(m_first+newpos,m_last,tmp+newpos+1);
      m_last=tmp+size()+1;
      if(m_first)
        delete[] m_first;
      m_first=tmp;
      return m_first+newpos;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
      difference_type newpos=pos-m_first;
      difference_type addsize= last-first;
      iterator tmp=new Type[size()+addsize];
      std::copy(m_first,m_first+newpos,tmp);
      std::copy(first,last,tmp+newpos);
      std::copy(m_first+newpos,m_last,tmp+newpos+addsize);
      m_last=tmp+size()+addsize;
      if(m_first)
        delete[] m_first;
      m_first=tmp;
      return m_first+newpos;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
      iterator tmp=new Type[size()+1];
      std::copy(m_first,m_last,tmp);
      tmp[size()]=value;
      m_last=tmp+size()+1;
      if(m_first)
        delete[] m_first;
      m_first=tmp;
    }
    //at methods
    reference at(size_t pos)
    {
      return checkIndexAndGet(pos);
    }

    const_reference at(size_t pos) const
    {
      return checkIndexAndGet(pos);
    }

    //[] operators
    reference operator[](size_t pos)
    {
      return m_first[pos];
    }

    const_reference operator[](size_t pos) const
    {
      return m_first[pos];
    }

    //*begin methods
    iterator begin()
    {
      return m_first;
    }

    const_iterator begin() const
    {
      return m_first;
    }

    //*end methods
    iterator end()
    {
      return m_last;
    }

    const_iterator end() const
    {
      return m_last;
    }

    //size method
    size_t size() const
    {
      return m_last - m_first;
    }

    //empty method
    bool empty() const
    {
      return m_first == m_last;
    }

  private:
    reference checkIndexAndGet(size_t pos) const
    {
      if (pos >= size())
      {
        throw std::out_of_range("out of range");
      }

      return m_first[pos];
    }

    //your private functions

  private:
    iterator m_first;
    iterator m_last;
  };
}

#endif //vector_hpp