namespace stepik {

template <typename T>
class shared_ptr {

public:
    template <typename C>
    friend class shared_ptr;

    explicit shared_ptr(T* ptr = nullptr)
        : pointer(ptr)
    {
        if (!ptr)
            count = nullptr;
        else
            count = new long(1);
    }

    ~shared_ptr()
    {
        if (pointer && *count == 1) {
            delete pointer;
            delete count;
        }
        else if (pointer)
            (*count)--;
    }

    shared_ptr(const shared_ptr& other)
        : pointer(other.pointer)
        , count(other.count)
    {
        if ((count))
            (*count)++;
    }

    template <typename C>
    shared_ptr(const shared_ptr<C>& other)
        : pointer(other.pointer)
        , count(other.count)
    {
        if ((count))
            (*count)++;
    }

    shared_ptr& operator=(const shared_ptr& other)
    {
        if (this->pointer == other.pointer)
            return *this;

        shared_ptr tmp(other);
        swap(tmp);

        return *this;
    }

    template <typename C>
    shared_ptr& operator=(const shared_ptr<C>& other)
    {
        if (this->pointer == other.pointer)
            return *this;

        shared_ptr tmp(other);
        swap(tmp);

        return *this;
    }

    template <typename C>
    bool operator==(const shared_ptr<C>& other) const
    {
        return pointer == other.pointer;
    }

    explicit operator bool() const
    {
        return pointer != nullptr;
    }

    T* get() const
    {
        return pointer;
    }

    long use_count() const
    {
        if (count)
            return *count;
        else
            return 0;
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
        std::swap(pointer, x.pointer);
        std::swap(count, x.count);
    }

    void reset(T* ptr = 0)
    {
        shared_ptr tmp(ptr);
        swap(tmp);
    }

private:
    T* pointer;
    long* count;
};
} // namespace stepik
