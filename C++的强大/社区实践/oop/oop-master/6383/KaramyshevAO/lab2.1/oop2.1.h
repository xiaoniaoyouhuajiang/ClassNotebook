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

     explicit vector(size_t count = 0) : m_first((count) ? new Type[count] : nullptr), m_last((count) ? (m_first + count) : nullptr){}

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last) : vector(last-first) {
        std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init) : vector(init.begin(), init.end()) {}

    vector(const vector& other) : vector(other.size()){
        std::copy(other.m_first, other.m_last, m_first);
    }

    vector(vector&& other) : vector() {
         if(this != &other){
             swap(other);
         }
    }

    ~vector()
    {
       delete[] m_first;
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
      if(this !=&other){
          vector tmp(other);
          tmp.swap(*this);
      }
      return *this;
    }

    vector& operator=(vector&& other)
    {
      if(this !=&other){
          vector();
          swap(other);
      }
      return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      vector tmp(first, last);
      tmp.swap(*this);
    }

    // resize methods
    void resize(size_t count)
    {
      vector tmp(count);
      (count >= size()) ? std::copy(m_first, m_last, tmp.m_first) : std::copy(m_first, m_first+count, tmp.m_first);
      swap(tmp);
      //delete[] tmp.m_first;
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
      size_t pos1=pos-m_first;
      std::rotate(pos1+m_first, pos1+m_first+1, m_last);
      resize(size()-1);
      return m_first+pos1;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
      size_t pos1=last-first;
      iterator first1 = const_cast<iterator>(first);
      while(pos1--){
          first1=erase(first1);
      }
      return first1;
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
      size_t pos1 = pos-m_first;
      resize( size()+1);
      *(m_last-1) = value;
      std::rotate(m_first+pos1, m_last-1, m_last);
      return m_first+pos1;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
      size_t size_in = last-first;
      iterator newpos = const_cast<iterator>(pos);
      while(size_in--){
          newpos = insert(newpos, *(first+size_in));
      }
      return newpos;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
      insert(end(), value);
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
     void swap( vector &other){
        std::swap(this->m_first, other.m_first);
		std::swap(this->m_last, other.m_last);
    }
    //your private functions

  private:
    iterator m_first;
    iterator m_last;
  };
}// namespace stepik
