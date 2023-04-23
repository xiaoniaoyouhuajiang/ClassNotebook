
#include <algorithm>
#include <cstddef>

namespace stepik
{
template <typename T>

class shared_ptr
{
    template <typename U>
    friend class shared_ptr;

public:
    explicit shared_ptr(T *ptr = nullptr) : ptr(ptr),
                                            count(ptr ? new size_t(1) : nullptr)
    {
    }

    ~shared_ptr()
    {
        release();
    }

    template <typename U>
    shared_ptr(const shared_ptr<U> &other) : ptr(other.ptr),
                                              count(other.count)
    {
        if (count)
            (*count)++;
    }

    shared_ptr(const shared_ptr &other) : ptr(other.ptr),
                                          count(other.count)
    {
        if (count)
            (*count)++;
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
        return (ptr != nullptr);
    }

    T *get() const
    {
        return ptr;
    }

    long use_count() const
    {
        return (count ? *count : 0);
    }

    T &operator*() const
    {
        return (*ptr);
    }

    T *operator->() const
    {
        return ptr;
    }
    template <typename U>
    bool operator==(const shared_ptr<U> &other) const
    {
        return (ptr == other.ptr);
    }
    void swap(shared_ptr &x) noexcept
    {
        std::swap(ptr, x.ptr);
        std::swap(count, x.count);
    }

    void reset(T *ptr = nullptr)
    {
        shared_ptr p(ptr);
        swap(p);
    }

private:
    T *ptr;
    size_t *count;

    void release()
    {
        if (ptr)
        {
            --(*count);

            if (*count == 0)
            {
                delete ptr;
                delete count;
            }
        }
    }
};
} // namespace stepik
