#ifndef VECTOR
#define VECTOR
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

    explicit vector(size_t count = 0) {
      m_first = new Type[count];
      m_last = m_first+count;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
        : vector(last-first) {
     std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init)
        : vector(init.begin(),init.end()) {
    }

    vector(const vector& other)
        : vector(other.begin(), other.end()) {
    }

    vector(vector&& other)
        : m_first(other.begin())
        , m_last(other.end()){
        other.m_first = nullptr;
        other.m_last = nullptr;    
    }

    ~vector() {
      delete [] m_first;
      m_last = nullptr;
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
      vector(other).swap(*this);
      return *this;
    }
      
    void swap(vector &obj) throw() {
        std::swap(m_first,obj.m_first);
        std::swap(m_last,obj.m_last);
    }    

    vector& operator=(vector&& other)
    {
        vector(std::move(other)).swap(*this);
        return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      vector(first, last).swap(*this);
    }

    // resize methods
    void resize(size_t count);
    
    //erase methods
    iterator erase(const_iterator pos)
    {
      erase(pos,pos+1);
    }

    iterator erase(const_iterator first, const_iterator last);

    //insert methods
    iterator insert(const_iterator pos, const Type& value);

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last);

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
    reference checkIndexAndGet(size_t pos) const;

    //your private functions
    iterator m_first;
    iterator m_last;
  };




    // resize methods
template <typename Type>
    void vector<Type>::resize(size_t count) {
      vector newvec(count);
      std::copy(begin(), begin()+count > end() ? end() : begin()+count, newvec.begin());
      newvec.swap(*this);
    }
    
template <typename Type>
    typename vector<Type>::iterator vector<Type>::erase( typename vector<Type>::const_iterator first, typename vector<Type>::const_iterator last)
    {
      vector newvec(size()-(last-first));
      size_t n = (first-begin());
      std::copy(const_iterator(begin()), first, newvec.begin());
      std::copy(last, const_iterator(end()), newvec.begin()+n);
      newvec.swap(*this);
      return begin()+n;
    }

    //insert methods
    template <typename Type>
    typename vector<Type>::iterator vector<Type>::insert(typename vector<Type>::const_iterator pos, const Type& value)
    {
        vector newvec(size()+1);
        size_t n = (pos-begin());
        std::copy(const_iterator(begin()), pos, newvec.begin());
        *(newvec.begin()+n) = value;

        if (pos+1 < end())
          std::copy(pos,
                    const_iterator(end()),
                    newvec.begin()+n+1);
        newvec.swap(*this);
        return begin()+n;
    }

    template <typename Type>
    template <typename InputIterator>
    typename vector<Type>::iterator vector<Type>::insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        vector newvec(size()+(last-first));
        size_t n = (pos-begin());
        std::copy(const_iterator(begin()), pos, newvec.begin());
        std::copy(first, last, newvec.begin()+n);

        if (pos+1 < end())
          std::copy(pos,
                    const_iterator(end()),
                    newvec.begin()+n+(last-first));
        newvec.swap(*this);
        return begin()+n;
    }

template <typename Type>
    typename vector<Type>::reference vector<Type>::checkIndexAndGet(size_t pos) const
    {
      if (pos >= size())
      {
        throw std::out_of_range("out of range");
      }

      return m_first[pos];
    }
}// namespace stepik
#endif
