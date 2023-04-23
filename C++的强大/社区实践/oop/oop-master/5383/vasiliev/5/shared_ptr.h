#ifndef ETUOOP_SHAREDPTR_H
#define ETUOOP_SHAREDPTR_H

namespace etuoop
{


template <typename T>
class shared_ptr
{
public:
    explicit shared_ptr(T *ptr = 0) :
        raw_ptr(ptr),
        ref_counter(nullptr)
    {
        acquire();
    }

    ~shared_ptr()
    {
        release();
    }

    shared_ptr(const shared_ptr& other) :
        raw_ptr(other.raw_ptr),
        ref_counter(other.ref_counter)
    {
        acquire();
    }

    template <typename U>
    shared_ptr(const shared_ptr<U>& other) :
        raw_ptr(other.raw_ptr),
        ref_counter(other.ref_counter)
    {
        acquire();
    }

    shared_ptr& operator=(const shared_ptr& other)
    {
        if (this != &other) {
            release();
            raw_ptr = other.raw_ptr;
            ref_counter = other.ref_counter;
            acquire();
        }
        return *this;
    }

    template <typename U>
    shared_ptr& operator=(const shared_ptr<U>& other)
    {
        if (this != &other) {
            release();
            raw_ptr = other.raw_ptr;
            ref_counter = other.ref_counter;
            acquire();
        }
        return *this;
    }

    explicit operator bool() const
    {
        return raw_ptr != nullptr;
    }

    T* get() const
    {
        return raw_ptr;
    }

    long use_count() const
    {
        if (ref_counter) {
            return *ref_counter;
        }
        return 0;
    }

    T& operator*() const
    {
        return *raw_ptr;
    }

    T* operator->() const
    {
        return raw_ptr;
    }

    template <typename U>
    void swap(shared_ptr<U>& x) noexcept
    {
        std::swap(ref_counter, x.ref_counter);
        std::swap(raw_ptr, x.raw_ptr);
    }

    void reset(T *ptr = 0)
    {
        release();
        raw_ptr = ptr;
        ref_counter = nullptr;
        acquire();
    }

    template <typename U>
    bool operator==(const shared_ptr<U>& other) const
    {
        return this->get() == other.get();
    }

private:
    void acquire()
    {
        if (ref_counter) {
            ++*ref_counter;
        } else if (raw_ptr) {
            ref_counter = new long(1);
        }
    }

    void release()
    {
        if (!ref_counter) { return; }
        --*ref_counter;
        if (!*ref_counter) {
            delete raw_ptr;
            delete ref_counter;
        }
    }

    T* raw_ptr;
    long* ref_counter;

    template<typename U>
    friend class shared_ptr;
};
} // namespace etuoop

#endif
