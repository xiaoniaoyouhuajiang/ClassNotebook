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
        if(count<=0) throw std::bad_alloc();
            m_first = new Type[count];
            m_last = m_first+count;
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last){
        size_t size = last - first;
        if (!size) return;
        m_first = new Type[size];
        m_last = m_first + size;
        std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init)
    : vector(init.begin(), init.end())
    {}

    vector(const vector& other)
    {
        if(other.empty()) return;
        m_first = new Type[other.size()];
        m_last = m_first + other.size();
        std::copy(other.m_first,other.m_last,m_first);
    }

    vector(vector&& other)
    {
        swap(other);
    }

    ~vector()
    {
        if(m_first)
            delete [] m_first;
        m_first = m_last = nullptr;
    }
    vector& operator=(const vector& other)
    {
        if(m_first)
            delete [] m_first;
        if(other.size()){
            m_first = new Type[other.size()];
            m_last = m_first + other.size();
            std::copy(other.m_first,other.m_last,m_first);
        }
        else m_first = m_last = nullptr;
    }

    vector& operator=(vector&& other)
    {
        if(m_first)
            delete [] m_first;
        m_first = m_last = nullptr;
        if(other.size()){
            swap(other);
        }
    }

    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        if(m_first)
            delete [] m_first;
        if(first!=last){
            size_t s = last - first;
            m_first = new Type[s];
            m_last = m_first + s;
            std::copy(first, last, m_first);
        }
        else m_first = m_last = nullptr;
    }

    void resize(size_t count)
    {
        if(count==0){
            delete [] m_first;
            m_first = m_last = nullptr;
            return;
        }
        iterator new_first = new Type[count];
        std::copy(m_first,count>size()?m_last:m_first+count,new_first);
        delete [] m_first;
        m_first = new_first;
        m_last = m_first + count;
    }

    iterator erase(const_iterator pos)
    {
        auto d = pos - m_first;
        std::rotate(m_first + d, m_first + d + 1, m_last);
        resize(size()-1);
        return m_first+d;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        auto d = first - m_first;
        auto erase_d = last - first;
        std::rotate(m_first + d, m_first +d + erase_d, m_last);
        resize(m_last - m_first - erase_d);
        return m_first + d;
    }

    iterator insert(const_iterator pos, const Type& value)
    {
        auto new_first = new Type[size()+1];
        auto index = pos-m_first;
        std::copy(m_first,m_first + index, new_first);
        new_first[index] = value;
        std::copy(m_first + index, m_last, new_first + index);
        m_last = new_first + size() + 1;
        delete [] m_first;
        m_first = new_first;
        return new_first + index;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
        auto in_size = last - first, index = pos - m_first;
        auto new_first = new Type[size()+in_size];
        using std::copy;
        copy(m_first,m_first + index, new_first);
        copy(first,last, new_first + index);
        copy(m_first + index, m_last, new_first + index + in_size);
        m_last = new_first + size() + in_size;
        delete [] m_first;
        m_first = new_first;
        return m_first + index;
    }

    void push_back(const value_type& value)
    {
       resize(size()+1);
       *(m_last - 1) = value;
    }

    reference at(size_t pos)
    {
      return checkIndexAndGet(pos);
    }

    const_reference at(size_t pos) const
    {
      return checkIndexAndGet(pos);
    }

    reference operator[](size_t pos)
    {
      return m_first[pos];
    }

    const_reference operator[](size_t pos) const
    {
      return m_first[pos];
    }

    iterator begin()
    {
      return m_first;
    }

    const_iterator begin() const
    {
      return m_first;
    }

    iterator end()
    {
      return m_last;
    }

    const_iterator end() const
    {
      return m_last;
    }

    size_t size() const
    {
      return m_last - m_first;
    }

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
    void swap(vector &other){
        std::swap(m_first, other.m_first);
        std::swap(m_last, other.m_last);
    }

  private:
    iterator m_first = nullptr;
    iterator m_last = nullptr;
  };
}// namespace stepik
