#pragma once

namespace stepik
{
template <typename T>
class shared_ptr
{
public:
    template <typename V>
    friend class shared_ptr;

    explicit shared_ptr(T *ptr = 0) :
        data(ptr), count(ptr ? new size_t(1) : nullptr)
    {
    }

    ~shared_ptr()
    {
        if (data)
        {
            if ((*count) == 1)
            {
                delete data;
                delete count;
            }
            else
                (*count)--;
        }
    }

    shared_ptr(const shared_ptr & other) :
        data(other.data), count(other.count)
    {
        if (data)
            (*count)++;
    }

    template <typename V>
    shared_ptr(const shared_ptr<V> & other) :
        data(other.data), count(other.count)
    {
        if (data)
            (*count)++;
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
        shared_ptr<T> temp_ptr(other);
        temp_ptr.swap(*this);
        return *this;
    }

    template <typename V>
    shared_ptr& operator=(const shared_ptr<V> & other)
    {
        shared_ptr<T> temp_ptr(other);
        temp_ptr.swap(*this);
        return *this;
    }

    template <typename V>
    friend bool operator==(const shared_ptr<T> &left, const shared_ptr<V> &right)
    {
        return left.get() == right.get();
    }

    template <typename V>
    friend bool operator!=(const shared_ptr<T> &left, const shared_ptr<V> &right)
    {
        return !(left == right);
    }

    explicit operator bool() const
    {
        return data != nullptr;
    }

    T* get() const
    {
        return data;
    }

    long use_count() const
    {
        return (count) ? *count : 0;
    }

    T& operator*() const
    {
        return *data;
    }

    T* operator->() const
    {
        return data;
    }

    void swap(shared_ptr& x) noexcept
    {
        T *tmp_data = data;
        data = x.data;
        x.data = tmp_data;

        size_t *tmp_count = count;
        count = x.count;
        x.count = tmp_count;
    }

    void reset(T *ptr = 0)
    {
        shared_ptr<T> new_ptr(ptr);
        new_ptr.swap(*this);
    }

private:
    T *data;
    size_t *count;
};
}
