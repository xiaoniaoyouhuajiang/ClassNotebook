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

    explicit vector(size_t count = 0)
    {
      if(count){
          m_first=new Type[count];
          m_last=m_first+count;
      }
      else{
          m_first=nullptr;
          m_last=nullptr;
      }
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last):vector(last-first)
    {
        std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init):vector(init.size())
    {
        std::copy(init.begin(), init.end(), m_first);
    }

    vector(const vector& other): vector(other.size())
    {
         std::copy(other.m_first, other.m_last, m_first);
    }

    vector(vector&& other):m_first(other.m_first), m_last(other.m_last)
    {
         other.m_first=nullptr;
         other.m_last=nullptr;
    }

    ~vector()
    {
      delete [] m_first;
      m_first=nullptr;
      m_last=nullptr;
    }
  //assignment operators
    vector& operator=(const vector& other)
    {
      if(this!=&other){
          vector tmp(other);
          tmp.swap(*this);
      }
        return *this;
    }

    vector& operator=(vector&& other)
    {
        if(this!=&other){
          delete [] m_first;
          m_first=other.m_first;
          m_last=other.m_last;
          other.m_first=nullptr;
          other.m_last=nullptr;
        }
        return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      vector tmp (first, last);
      tmp.swap(*this);
    }
    // resize methods
    void resize(size_t count)
    {
      vector tmp(count);
      if(count>=size()){
          std::copy(m_first, m_last, tmp.m_first);
      }
      else{
          std::copy(m_first, m_first+count, tmp.m_first);
      }
      swap(tmp);
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
      size_t delta=pos-m_first;
      std::rotate(m_first+delta, m_first+delta+1, m_last);
      resize(size()-1);
      return m_first+delta;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
      size_t delta=first-m_first;
      size_t lenght=last-first;
      std::rotate(m_first+delta, m_first+delta+lenght, m_last);
      resize(m_last-m_first-lenght);
      return m_first+delta;
    }
//insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
      size_t delta=pos-m_first;
      resize(size()+1);
      *(m_last-1)=value;
      std::rotate(m_first+delta, m_last-1, m_last);
      return m_first+delta;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        size_t delta=last-first;
        iterator new_pos=const_cast<iterator>(pos);
        while(delta){
            delta--;
            new_pos=insert(new_pos, *(first+delta));
        }
        return new_pos;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
      resize(size()+1);
      *(m_last-1)=value;
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
     void swap(vector& other){
         std::swap(this->m_first, other.m_first);
         std::swap(this->m_last, other.m_last);
     }     

  private:
    iterator m_first;
    iterator m_last;
  };
}// namespace stepik