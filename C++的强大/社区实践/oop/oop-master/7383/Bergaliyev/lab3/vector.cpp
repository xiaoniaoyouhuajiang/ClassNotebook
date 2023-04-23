#include <iostream>
#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

namespace stepik
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

    explicit vector(size_t count = 0) : m_first(count ? new Type[count] : nullptr), m_last(m_first + count)
    {  
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
      InputIterator cur = first;
      size_t count = 0;
      while(cur != last){
        ++count;
        ++cur;
      }
      m_first = count ? new Type[count] : nullptr;
      m_last = m_first + count;
      try{
        for(size_t i=0; i<count; ++i){
          m_first[i] = *first++;
        }
      }
      catch(std::exception & e){
        delete[] m_first;
        m_first = nullptr;
        m_last = nullptr;
        throw;
      }
    }

    vector(std::initializer_list<Type> init)
    {
      size_t count = init.end() - init.begin();
      const Type* cur = init.begin();
      m_first = count ? new Type[count] : nullptr;
      try{
        for(size_t i=0; i<count; ++i){
          m_first[i] = *cur;
          ++cur;
        }
      }
      catch(std::exception & e){
        delete[] m_first;
        m_first = nullptr;
        m_last = nullptr;
        throw;
      }
      m_last = m_first + count;
    }

    vector(const vector& other)
    {
      size_t count = other.m_last - other.m_first;
      m_first = count ? new Type[count] : nullptr;
      m_last = m_first + count;
      try{
        for(size_t i=0; i<count; ++i)
          m_first[i] = other.m_first[i];
      }
      catch(std::exception & e){
        delete[] m_first;
        m_first = nullptr;
        m_last = nullptr;
        throw;
      }
    }

    vector(vector&& other)
    {
      m_first = other.m_first;
      m_last = other.m_last;
      other.m_first = nullptr;
      other.m_last = nullptr;
    }

    ~vector()
    {
      delete[] m_first;
    }
    //assignment operators
    vector& operator=(const vector& other)
    {
      if(other.m_first == m_first)
        return *this;
      size_t count = other.m_last - other.m_first;
      if(count == 0){
        delete[] m_first;
        m_first = nullptr;
        m_last = nullptr;
        return *this;
      }
      iterator new_arr = new Type[count];
      try{
        for(int i=0; i<count; ++i)
          new_arr[i] = other.m_first[i];
      }
      catch(std::exception & e){
        delete[] new_arr;
        throw;
      }
      delete[] m_first;
      m_first = new_arr;
      m_last = m_first + count;
      return *this;
    }

    vector& operator=(vector&& other)
    {
      delete[] m_first;
      m_first = other.m_first;
      m_last = other.m_last;
      other.m_first = nullptr;
      other.m_last = nullptr;
      return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      size_t count = 0;
      InputIterator cur = first;
      while(cur != last){
        ++count;
        ++cur;
      }
      cur = first;
      iterator new_arr = new Type[count];
      try{
        for(int i=0; i<count; ++i){
          new_arr[i] = *cur;
          ++cur;
        }
      }
      catch(std::exception & e){
        delete[] new_arr;
        return;
      }
      delete[] m_first;
      m_first = new_arr;
      m_last = new_arr + count;
    }

    // resize methods
    void resize(size_t count)
    {
      iterator new_arr = count ? new Type[count] : nullptr;
      try{
        for(int i=0; i<std::min(count, (size_t)(m_last-m_first)); ++i)
          new_arr[i] = m_first[i];
      }
      catch(std::exception & e){
        delete[] new_arr;
        throw;
      }
      delete[] m_first;
      m_first = new_arr;
      m_last = m_first + count;
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
      size_t index = pos - m_first;
      for(int i=index; i<size()-1; ++i)
        new (m_first+i) Type(m_first[i+1]);
      --m_last;
      return m_first + index;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
      size_t count = last - first;
      size_t index = first - m_first;
      for(int i=index; i<size()-count; ++i)
        new (m_first+i) Type(m_first[i+count]);
      m_last -= count;
      return m_first + index;
    }
    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
      size_t size = m_last - m_first;
      iterator new_arr = new Type[size + 1];
      size_t index = pos - m_first;
      try{
        for(int i=0; i<index; ++i)
          new_arr[i] = m_first[i];
        new_arr[index] = value;
        for(int i=index; i<size; ++i)
          new_arr[i+1] = m_first[i];
      }
      catch(std::exception & e){
        delete[] new_arr;
        throw;
      }
      delete[] m_first;
      m_first = new_arr;
      m_last = m_first + size + 1;
      return m_first + index;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
      size_t size = m_last - m_first;
      iterator new_arr = new Type[size+1];
      size_t index = pos - m_first;
      size_t count = 0;
      InputIterator cur = first;
      while(cur != last){
        ++count;
        ++cur;
      }
      try{
        for(int i=0; i<index; ++i)
          new_arr[i] = m_first[i];
        cur = first;
        for(int i=index; i<index+count; ++i){
          new_arr[i] = *cur;
          ++cur;
        }
        for(int i=index; i<size; ++i)
          new_arr[i+count] = m_first[i];
      }
      catch(std::exception & e){
        delete[] new_arr;
        throw;
      }
      delete[] m_first;
      m_first = new_arr;
      m_last = m_first + size + count;
      return m_first + index;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
      size_t size = m_last - m_first;
      iterator new_arr = new Type[size+1];
      try{
        for(int i=0; i<size; ++i)
          new_arr[i] = m_first[i];
        new_arr[size] = value;
      }
      catch(std::exception & e){
        delete[] new_arr;
        throw;
      }
      delete[] m_first;
      m_first = new_arr;
      m_last = m_first + size + 1;
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

  private:
    iterator m_first;
    iterator m_last;
  };
}

