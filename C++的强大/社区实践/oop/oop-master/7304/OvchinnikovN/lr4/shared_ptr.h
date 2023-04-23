#include <iostream>

namespace stepik
{
  template <typename T>
  class shared_ptr
  {
      template <class A> friend class shared_ptr;
      
  public:
    explicit shared_ptr(T *ptr = 0)
    {
        m_ptr = ptr;
        if(ptr)
            count = new long(1);
        else
            count = nullptr;
    }

    ~shared_ptr()
    {
        if(use_count() > 1)
        {
            (*count) -= 1;
        }
        else
        {
            delete count;
            delete m_ptr;
            m_ptr = nullptr;
            count = nullptr;
        }
    }

    shared_ptr(const shared_ptr & other)
    {
        m_ptr = other.m_ptr;
        count = other.count;
        if(use_count())
            (*count)++;
    }
      
      template <typename A>
      shared_ptr(const shared_ptr<A> & other)
      {
        m_ptr = other.m_ptr;
        count = other.count;
        if(use_count())
            (*count)++;
      }

    shared_ptr& operator=(const shared_ptr & other)
    {
        if(this != &other)
        {
            this->~shared_ptr();
            m_ptr = other.m_ptr;
            count = other.count;
            if(use_count())
                (*count)++;
        }
        return *this;
    }
      
      template <typename A>
      shared_ptr& operator=(const shared_ptr<A> & other)
      {
          if(m_ptr != other.get())
          {
            this->~shared_ptr();
            m_ptr = other.m_ptr;
            count = other.count;
            if(use_count())
                (*count)++;
          }
          return *this;
      }

    explicit operator bool() const
    {
        return get() != nullptr;
    }

    T* get() const
    {
        return m_ptr;
    }

    long use_count() const
    {
        return (m_ptr) ? *count : 0;
    }

    T& operator*() const
    {
        return *m_ptr;
    }

    T* operator->() const
    {
        return m_ptr;
    }

    void swap(shared_ptr& x) noexcept
    {
        std::swap(m_ptr, x.m_ptr);
        std::swap(count, x.count);
    }

    void reset(T *ptr = 0)
    {
        this->~shared_ptr();
        m_ptr = ptr;
        count = (ptr) ? new long(1) : nullptr;
    }
      
      bool operator==(const shared_ptr & other) const
      {
          return get() == other.get();
      }
      
      template <typename A>
      bool operator==(const shared_ptr<A> & other) const
      {
          return get() == other.get();
      }

  private:
    T* m_ptr;
    long *count;
  };   
}