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

    explicit vector(size_t count = 0):
      m_first(count ? new value_type[count] : nullptr), m_last(m_first+count)
    {}

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last):
      m_first(new value_type[last-first]), m_last(m_first+(last-first))
    {
      std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init):
      m_first(new value_type[init.size()]), m_last(m_first+init.size())
    {
      std::copy(init.begin(), init.end(), m_first);
    }

    vector(const vector& other):
      m_first(other.size() ? new value_type[other.size()] : nullptr), m_last(m_first+other.size())
    {
      std::copy(other.m_first, other.m_last, m_first);
    }

    vector(vector&& other):
      m_first(other.m_first), m_last(other.m_last)
    {
      other.m_first = nullptr;
      other.m_last = nullptr;
    }

    ~vector()
    {
      delete [] m_first;
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
      delete [] m_first;
      m_first = new value_type[other.size()];
      m_last = m_first + other.size();
      std::copy(other.m_first, other.m_last, m_first);
        
      return *this;
    }

    vector& operator=(vector&& other)
    {
      delete [] m_first;
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
      delete [] m_first;
      m_first = new value_type[last-first];
      m_last = m_first + (last - first);
      std::copy(first, last, m_first);
    }

    // resize methods
    void resize(size_t count)
    {
      if (size() == count)
        return;
        
      iterator tmp = new value_type[count];
        
      std::copy(m_first, count > size() ? m_last : m_first+count, tmp);
        
      delete [] m_first;
      m_first = tmp;
      m_last = m_first + count;
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
      size_t new_size = size() - 1;
      size_t part_before_erase = pos - m_first;
      iterator tmp = new value_type[new_size];
      
      std::copy(m_first, m_first+part_before_erase, tmp);
      std::copy(m_first+(part_before_erase+1), m_last, tmp+part_before_erase);
        
      delete [] m_first;
      m_first = tmp;
      m_last = m_first + new_size;
        
      return m_first+part_before_erase;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
      size_t erase_part = last - first;
      size_t before_erase = first - m_first;
      size_t after_erase = m_last - last;
      size_t new_size = size() - erase_part;
      iterator tmp = new value_type[new_size];
        
      std::copy(m_first, m_first+before_erase, tmp);
      std::copy(m_first+(before_erase+erase_part), m_last, tmp+before_erase);
        
      delete [] m_first;
      m_first = tmp;
      m_last = m_first + new_size;
        
      return m_first+before_erase;
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
      size_t new_size = size() + 1;
      size_t insert_pos = pos - m_first;
      iterator tmp = new value_type[new_size];
        
      std::copy(m_first, m_first+insert_pos, tmp);
      tmp[insert_pos] = value;
      std::copy(m_first+insert_pos, m_last, tmp+(insert_pos+1));
        
      delete [] m_first;
      m_first = tmp;
      m_last = m_first + new_size;
        
      return m_first+insert_pos;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
      size_t insert_size = last - first;
      size_t new_size = size() + insert_size;
      iterator tmp = new value_type[new_size];
        
      size_t before_insert = pos - m_first;
      std::copy(m_first, m_first+before_insert, tmp);
      std::copy(first, last, tmp+before_insert);
      std::copy(m_first+before_insert, m_last, tmp+(before_insert+insert_size));
        
      delete [] m_first;
      m_first = tmp;
      m_last = m_first + new_size;
        
      return m_first+before_insert;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
      resize(size()+1);
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

    //your private functions

  private:
    iterator m_first;
    iterator m_last;
  };
}// namespace stepik