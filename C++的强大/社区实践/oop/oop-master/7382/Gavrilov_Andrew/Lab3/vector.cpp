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
        my_alloc(count);
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last)
    {
        my_alloc(last-first);
        std::copy(first,last,m_first);
    }

    vector(std::initializer_list<Type> init)
    {
        my_alloc(init.size());
        std::copy(init.begin(),init.end(),m_first);
    }

    vector(const vector& other)
    {
        my_alloc(other.size());
        std::copy(other.begin(),other.end(),m_first);
    }

    vector(vector&& other): m_first(nullptr),m_last(nullptr)
    {
        std::swap(m_first, other.m_first);
        std::swap(m_last,other.m_last);
    }

    ~vector()
    {
      delete[] m_first;
    }
    
    void resize(size_t count)
    {
        auto old_first=m_first;
        auto old_last=m_last;
        my_alloc(count);
        if(count>old_last-old_first){
            std::copy(old_first,old_last,m_first);
        }
        else{
            std::copy(old_first,old_first+count,m_first);
        }
        delete[] old_first;
    }
      
    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
      auto old_first=m_first;
      auto old_last=m_last;
      my_alloc(m_last-m_first+1);
      auto added=pos-old_first;
      std::copy(old_first,old_first+added,m_first);
      m_first[added]=value;
      std::copy(old_first+added,old_last,m_first+added+1);
      delete[] old_first;
      return m_first+added;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
      auto old_first=m_first;
      auto old_last=m_last;
      auto added_begin=pos-old_first;
      if(first==last)
            return m_first+added_begin;
      auto count=m_last-m_first+(last-first);
      my_alloc(count);
      std::copy(old_first,old_first+added_begin,m_first);
      std::copy(first,last,m_first+added_begin);
      std::copy(old_first+added_begin,old_last,m_first+added_begin+(last-first));
        delete[] old_first;
        return m_first+added_begin;
    }


    void push_back(const value_type& value)
    {
      auto count=m_last-m_first;
      resize(count+1);
      m_first[count]=value;
    }

    vector& operator=(const vector& other)
    {
      delete[] m_first;
      my_alloc(other.size());
      std::copy(other.begin(),other.end(),m_first);
    }

    vector& operator=(vector&& other)
    {
        delete[] m_first;
        m_first=nullptr;
        m_last=nullptr;
        std::swap(m_first, other.m_first);
        std::swap(m_last,other.m_last);
    }
    iterator erase(const_iterator pos)
    {
      auto old_first=m_first;
      auto old_last=m_last;
      my_alloc(m_last-m_first-1);
      auto deleted=pos-old_first;
      std::copy(old_first,old_first+deleted,m_first);
      std::copy(old_first+deleted+1,old_last,m_first+deleted);
      delete[] old_first;
      return m_first+deleted;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        if(first==last)
            return m_first;
      auto old_first=m_first;
      auto old_last=m_last;
      my_alloc(m_last-m_first-(last-first));
      auto deleted_begin=first-old_first;
      auto deleted_end=last-old_first;
      std::copy(old_first,old_first+deleted_begin,m_first);
      std::copy(old_first+deleted_end,old_last,m_first+deleted_begin);
        delete[] old_first;
        return m_first+deleted_begin;
    }
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      delete[] m_first;
      my_alloc(last-first);
      std::copy(first,last,m_first);
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

    void my_alloc(size_t size){
        m_first=size ? new Type[size]() : nullptr;
        m_last=m_first+size;
    }

  private:
    iterator m_first;
    iterator m_last;
  };
}