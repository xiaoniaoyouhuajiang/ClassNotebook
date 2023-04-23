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

    explicit vector(size_t count = 0) : m_first(count ? new value_type[count] : nullptr), m_last(m_first+count)
    {}

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last) : m_first(new value_type[last-first]), m_last(m_first+(last-first))
    {
        std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init) : m_first(new value_type[init.size()]), m_last(m_first+init.size())
    {
        std::copy(init.begin(), init.end(), m_first);
    }

    vector(const vector& other) : m_first(new value_type[other.size()]), m_last(m_first+other.size())
    {
        std::copy(other.begin(), other.end(), m_first);
    }

    vector(vector&& other) : m_first(other.m_first), m_last(other.m_last)
    {
        other.m_first = nullptr;
        other.m_last = nullptr;
    }

    ~vector()
    {
        delete[] m_first;
    }
     
     void resize(size_t count)
    {
        if(count == size())
            return;
        vector Temp(count);
        std::copy(m_first, count > size() ? m_last : m_first+count, Temp.m_first);
        std::swap(m_first, Temp.m_first);
        std::swap(m_last, Temp.m_last);
    }
	vector& operator=(const vector& other)
    {
        delete[] m_first;
        m_first = new value_type[other.size()];
        m_last = m_first + other.size();
        std::copy(other.begin(), other.end(), m_first);
    }

    vector& operator=(vector&& other)
    {
        delete[]m_first;
        std::swap(m_first, other.m_first);
        std::swap(m_last, other.m_last);
        other.m_first = nullptr;
        other.m_last = nullptr;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        delete[] m_first;
        m_first = new value_type[last-first];
        m_last = m_first+(last-first);
        std::copy(first, last, m_first);
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
        //vector Temp(size() + 1);
        size_t offset = pos - m_first;
        //std::copy(m_first, m_first+offset, Temp.m_first);
        //Temp.m_first[offset] = value;
        //std::copy(m_first+offset, m_last, Temp.m_first+offset+1);
        resize(size()+1);
        std::rotate(m_first+offset, m_last - 1, m_last);
        *(m_first+offset) = value;
        //std::swap(m_first, Temp.m_first);
        //std::swap(m_last, Temp.m_last);
        return m_first+offset;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        size_t count = last - first;
        size_t offset = pos - m_first;
        resize(size() + count);
        std::rotate(m_first+offset, m_last - count, m_last);
        std::copy(first, last, m_first+offset);
        return m_first+offset;
    }
	iterator erase(const_iterator pos)
    {    
        vector Temp(size()-1);
        size_t offset = pos - m_first;
        std::copy(m_first, m_first+offset, Temp.m_first);
        std::copy(m_first+(offset+1), m_last, Temp.m_first+offset);
        std::swap(m_first, Temp.m_first);
        std::swap(m_last, Temp.m_last);
        return m_first+offset;
    }

    iterator erase(const_iterator first, const_iterator last)
    {   
        size_t offset = last - first;
        size_t begin = first - m_first;
        vector Temp(size() - offset);
        std::copy(m_first, m_first+begin, Temp.m_first);
        std::copy(m_first+(begin+offset), m_last, Temp.m_first+begin);
        std::swap(*this,Temp);
        return m_first+begin;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
        vector Temp(size() + 1);
        std::copy(m_first, m_last, Temp.m_first);
        Temp.m_first[size()] = value;
        std::swap(m_first, Temp.m_first);
        std::swap(m_last, Temp.m_last);        
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
