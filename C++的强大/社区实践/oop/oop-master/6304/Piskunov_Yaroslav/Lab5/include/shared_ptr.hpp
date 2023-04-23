#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#endif // SHARED_PTR_HPP


namespace stepik
{
template <typename T>
class shared_ptr
{
public:
    explicit shared_ptr(T *ptr = 0)
    {
        if (ptr)
        {
            pointer = ptr;
            count = new long(1);
        }
        else
        {
            pointer = nullptr;
            count = new long(0);
        }
    }

    ~shared_ptr()
    {
        if (pointer)
            (*(count))--;
        if (!use_count())
            delete pointer;
    }

    shared_ptr(const shared_ptr & other)
    {
        pointer = other.pointer;
        count = other.count;
        if (get())
            (*(count))++;
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
        shared_ptr<T>(other).swap(*this);
        return *this;
    }

    explicit operator bool() const
    {
        return (get() != 0);
    }

    template <class Y>
    shared_ptr(const shared_ptr<Y> & other): pointer(other.get()), count(other.get_count())
    {
        if (get()!=0)
            (*(count))++;
    }

    template <class Y>
    shared_ptr& operator=(const shared_ptr<Y> & other)
    {
        shared_ptr(other).swap(*this);
        return *this;
    }

    long* get_count() const
    {
        return count;
    }

    T* get() const
    {
        return pointer;
    }

    long use_count() const
    {
        return *count;
    }

    T& operator*() const
    {
        return *pointer;
    }

    T* operator->() const
    {
        return pointer;
    }

    void swap(shared_ptr& x) noexcept
    {
        std::swap(x.pointer, pointer);
        std::swap(x.count, count);
    }

    void reset(T *ptr = 0)
    {
        shared_ptr<T>(ptr).swap(*this);
    }

private:
    T* pointer;
    long* count;
};

    template <class U, class Y>
    bool operator==( const shared_ptr<U>& a, const shared_ptr<Y>& b ) noexcept
    {
        return a.get() == b.get();
    }

} // namespace stepik
