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
    : m_first(count ? new Type[count] : nullptr), m_last(m_first + count)
    {}

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
      int count = last - first;
      if (count > 0){ 
            m_first = new Type[count];
            m_last = m_first + count;
            std::copy(first, last, m_first);
        }
        else{ 
            m_first = nullptr;
            m_last = nullptr;
        }
    }

    vector(std::initializer_list<Type> init)
    {
      if (init.size() > 0){ 
            m_first = new Type[init.size()];
            m_last = m_first + init.size();
            std::copy(init.begin(), init.end(), m_first);
        }
        else{
            m_first = nullptr;
            m_last = nullptr;
        }
    }

    vector(const vector& other)
    : vector(other.begin(), other.end())
    {
      // use previous step implementation
    }

    vector(vector&& other)
    :  m_first(other.m_first), m_last(other.m_last)
    {
      other.m_first = nullptr;
      other.m_last = nullptr;
    }

    ~vector()
    {
      if (m_first){ 
            delete [] m_first;
            m_first = m_last = nullptr;
        }
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
      if(this != &other)
            {
                delete[] m_first;
                m_first = new value_type[other.size()];
                m_last = m_first + other.size();
                std::copy(other.m_first, other.m_last, m_first);
            }
            return *this;
    }

    vector& operator=(vector&& other)
    {
        if (m_first != nullptr)
            delete [] m_first;
            
        m_first = nullptr;
        m_last = nullptr;
        std::swap(m_first, other.m_first);
        std::swap(m_last, other.m_last);
        return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      if (m_first!=nullptr)
          delete [] m_first;
      m_first = new value_type[last-first];
      m_last = m_first + (last-first);
      std::copy(first, last, m_first);
    }

    // resize methods
    void resize(size_t count)
    {
      if(count == size()) 
          return;
      iterator temp = new Type[count];
      if(count > size())
          std::copy(m_first, m_last, temp);
      else
          std::copy(m_first, m_first+count, temp);
      delete[] m_first;
      m_first = temp;
      m_last = m_first+count;
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
      size_t offset = pos - m_first;
      std::rotate( m_first+offset, m_first+offset+1, m_last);
      resize(size()-1);
      return m_first + offset;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        size_t new_first = first - m_first;
	    size_t new_last = last - m_first;
	    std::rotate(m_first + new_first, m_first + new_last, m_last);
	    resize(size() - new_last + new_first);
	    return m_first + new_first;
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
      size_t offset = pos - m_first;
            resize(size()+1);
            *(m_last-1) = value;
            std::rotate(m_first+offset, m_last-1, m_last);
            return m_first + offset;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
       size_t offset = pos - m_first;
            resize( size() + (last-first));
            std::copy(first, last, m_last - (last-first));
            std::rotate(m_first+offset, m_last - (last-first) , m_last);
            return m_first + offset;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
      resize(size()+1);
            *(m_last-1) = value;
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
}// namespace stepik