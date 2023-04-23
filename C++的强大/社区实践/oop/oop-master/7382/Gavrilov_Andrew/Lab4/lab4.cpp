#include <algorithm> // std::swap
#include <cstddef>   // size_t

namespace stepik
{
template <typename T>

class shared_ptr
{
    template <typename U>
    friend class shared_ptr;

  public:
    explicit shared_ptr(T *ptr = nullptr) : m_ptr(ptr),
                                            m_count(ptr ? new size_t(1) : nullptr)
    {
    }

    ~shared_ptr()
    {
        if (m_ptr)
        {
            (*m_count)--;
            if (*m_count == 0)
            {
                delete m_ptr;
                delete m_count;
            }
        }
    }

    template <typename U>
    shared_ptr(const shared_ptr<U> &other) : m_ptr(other.m_ptr),
                                             m_count(other.m_count)
    {
        if (m_count)
            (*m_count)++;
    }

    shared_ptr(const shared_ptr &other) : m_ptr(other.m_ptr),
                                          m_count(other.m_count)
    {
        if (m_count)
            (*m_count)++;
    }

    template <typename U>
    shared_ptr &operator=(const shared_ptr<U> &other)
    {
        shared_ptr p(other);
        swap(p);
        return *this;
    }

    shared_ptr &operator=(const shared_ptr &other)
    {
        shared_ptr p(other);
        swap(p);
        return *this;
    }

    explicit operator bool() const
    {
        return (m_ptr != nullptr);
    }

    T *get() const
    {
        return m_ptr;
    }

    long use_count() const
    {
        return (m_count ? *m_count : 0);
    }

    T &operator*() const
    {
        return (*m_ptr);
    }

    T *operator->() const
    {
        return m_ptr;
    }

    template <typename U>
    bool operator==(const shared_ptr<U> &other) const
    {
        return (m_ptr == other.m_ptr);
    }

    void swap(shared_ptr &x) noexcept
    {
        std::swap(m_ptr, x.m_ptr);
        std::swap(m_count, x.m_count);
    }

    void reset(T *ptr = nullptr)
    {
        shared_ptr p(ptr);
        swap(p);
    }

  private:
    T *m_ptr;
    size_t *m_count;
};
} // namespace stepik
