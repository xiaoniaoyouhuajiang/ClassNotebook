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

    explicit vector(size_t count = 0): m_first(count ? new value_type[count] : nullptr), m_last(count ? m_first + count : nullptr)
    {
      // implement this
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last): vector(last - first)
    {  
       for(int i = 0; i < last - first; i++)
       m_first[i] = (value_type)first[i];
      // implement this
    }

    vector(std::initializer_list<Type> init): vector(init.begin(), init.end()) 
    {
      // implement this
    }

    vector(const vector& other): vector(other.m_first, other.m_last)
    {
      // implement this
    }

    vector(vector&& other): vector()
    {
        swap(*this, other);
      // implement this
    }

    ~vector()
    {
        delete[] m_first;
      // implement this
    }
    
      void resize(size_t count)
      {
        if (m_last - m_first != count) {
            vector temp(count);
            std::copy(m_first, m_last - m_first > count ? m_first + count : m_last, temp.m_first);
            swap(*this, temp);
        }
      // implement this
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {  
      size_t offset = pos - m_first;
      resize(size()+1);
      *(m_last-1) = value;
      std::rotate(m_first+offset, m_last-1, m_last);
      return m_first + offset; 
      // implement this
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
      size_t offset = pos - m_first;
      resize( size() + (last-first));
      std::copy(first, last, m_last - (last-first));
      std::rotate(m_first+offset, m_last - (last-first) , m_last);
      return m_first + offset;
      // implement this
    }

    //push_back methods
    void push_back(const value_type& value)
    { 
      resize(size()+1);
      *(m_last-1) = value;
      // implement this
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
    void swap(vector& v1, vector& v2) {
	    std::swap(v1.m_first, v2.m_first);
		std::swap(v1.m_last, v2.m_last);
    }
  };
}// namespace stepik