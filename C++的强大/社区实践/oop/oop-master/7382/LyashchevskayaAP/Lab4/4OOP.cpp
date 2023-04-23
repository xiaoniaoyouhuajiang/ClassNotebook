#include <iostream>

namespace stepik
{
template <typename T>
class shared_ptr
{
  public:
    
    template <typename D>friend class shared_ptr;

    explicit shared_ptr(T *ptr = 0) :
        m_ptr(ptr), m_counter(new size_t(1))
    {}

    ~shared_ptr()
    {
        dec_counter();
    }

    template<typename D>
    shared_ptr(const shared_ptr<D> &other) :
        m_ptr(other.m_ptr), m_counter(other.m_counter)
    {
        inc_counter();
    }
    
    shared_ptr(const shared_ptr &other) :
        m_ptr(other.m_ptr), m_counter(other.m_counter)
    {
        inc_counter();
    }

    template<typename D>
    shared_ptr &operator=(const shared_ptr<D> &other)
    {
        shared_ptr(other).swap(*this);
        return *this;
    }

    shared_ptr &operator=(const shared_ptr &other)
    {
        shared_ptr(other).swap(*this);
        return *this;
    }

    template<typename D>
    bool operator == (const shared_ptr<D> &other) const
    {
        return m_ptr == other.m_ptr;
    }

    template<typename D>
    bool operator != (const shared_ptr<D> &other) const
    {
        return m_ptr != other.m_ptr;
    }
    
    explicit operator bool() const
    {
        return m_ptr != 0;
    }

    T *get() const
    {
        return m_ptr;
    }

    long use_count() const
    {
        return m_ptr ? *m_counter : 0;
    }

    T &operator*() const
    {
        return *m_ptr;
    }

    T *operator->() const
    {
        return m_ptr;
    }

    void swap(shared_ptr &x) noexcept
    {
        std::swap(m_ptr, x.m_ptr);
        std::swap(m_counter, x.m_counter);
    }

    void reset(T *ptr = 0)
    {
        shared_ptr tmp(ptr);
        swap(tmp);
//        tmp.~shared_ptr();
    }

  private:
    void dec_counter()
    {
        if(--(*m_counter) == 0)
        {
            delete m_ptr;
            delete m_counter;
        }
    }

    void inc_counter()
    {
        (*m_counter)++;
    }
    
    T *m_ptr;
    size_t *m_counter;
};
} // namespace stepik
