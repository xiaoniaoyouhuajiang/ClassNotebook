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
        if (count)
            m_first = new Type[count];
        else
            m_first = nullptr;
        if (count)
            m_last = m_first+count;
        else
            m_last = nullptr;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
           size_t len = last - first;
        if (len)
            m_first = new Type[len];
        else
            m_first = nullptr;
        std::copy(first, last, m_first);
        
        if(len)
            m_last = m_first+len;
        else 
            m_last = nullptr;
    }

    vector(std::initializer_list<Type> init)
    {
      if(init.size())
            m_first = new Type[init.size()];
        else
            m_first = nullptr;
        if(init.size())
            m_last = init.size() + m_first;
        else 
            m_last = nullptr;
        std::copy(init.begin(), init.end(), m_first);
    }

    vector(const vector& other)
    {
      if (other.size())
          m_first = new Type[other.size()];
      else
          m_first = nullptr;
      if (other.size())
          m_last = m_first + other.size();
      else
          m_last = nullptr;
      std::copy(other.begin(), other.end(), m_first);
    }

    vector(vector&& other)
    {
      m_first = other.begin();
      m_last = other.end();
      other.m_first = nullptr;
      other.m_last = nullptr;
    }

    ~vector()
    {
      delete[] m_first;
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value){
        int i = 0;
        while((m_first + i) != pos)
            i++;
        push_back(value);
        std::rotate(m_first + i, m_last - 1, m_last);
        return m_first + i;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last){
        int i = 0;
        while((m_first + i) != pos)
            i++;
        int count = last - first;
        for(int j=0; j<count; j++)
            push_back(*(first + j));
        std::rotate(m_first + i, m_last - count, m_last);
        return m_first + i;
    }

    //push_back methods
    void push_back(const value_type& value){
      resize(size() + 1);
      at(size()-1) = value;
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
        void resize(size_t count)
    {
        iterator v;
        if(count)
            v = new Type[count];
        else 
            v = nullptr;
        if(count >= size())
            std::copy(m_first, m_last, v);
        else
            std::copy(m_first, m_first + count, v);
        delete[] m_first;
        m_first = v;
        if (count)
            m_last = m_first + count;
        else
            m_last = nullptr;
    }
    
    iterator erase(const_iterator pos)
    {
        int i=0;
        iterator v = m_first;
        while(v != pos){
            v++;
            i++;
        }
        std::rotate(v, v+1, m_last);
        resize(size()-1);
        return m_first + i;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        iterator v = m_first;
        while(v != first)
            v++;
        int len = last - first;
        for(int i=0; i<len; i++)
            v = erase(v);
        return v;
    }

    void assign(InputIterator first, InputIterator last)
    {
        size_t len = last - first;
        delete[] m_first;
        if (len)
            m_first = new Type[len];
        else
            m_first = nullptr;
        std::copy(first, last, m_first);
        
        if(len)
            m_last = m_first+len;
        else 
            m_last = nullptr;
    }
    //your private functions
    
  private:
    iterator m_first;
    iterator m_last;
  };
}// namespace stepik


