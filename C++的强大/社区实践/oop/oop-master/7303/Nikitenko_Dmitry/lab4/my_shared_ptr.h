#ifndef MY_SHARED_PTR_H
#define MY_SHARED_PTR_H
#include <iostream>

namespace stepik
{
  template <typename T>
  class shared_ptr
  {
public:
    explicit shared_ptr(T *ptr = 0)
    {
      this->ptr = ptr;
      count = new int(1);
    }

    ~shared_ptr()
    {
        if (--(*count) == 0)
        {
            delete ptr;
            delete count;
        }
    }
    template <class TT>
    friend class shared_ptr;

    template <class TT>
    bool operator==(const shared_ptr<TT> &other) const
    {
        return ptr == other.ptr;
    }

    shared_ptr(const shared_ptr & other)
    {
      this->ptr = other.ptr;
      this->count = other.count;
      if (count)
          ++(*count);
    }

    template <class TT>
    shared_ptr(const shared_ptr<TT> & other)
    : ptr(other.ptr)
    , count(other.count)
    {
        if(ptr) ++ *count;
    }
    shared_ptr& operator=(const shared_ptr & other)
    {
        shared_ptr ptr(other);
        swap(ptr);
        return *this;
    }

    explicit operator bool() const
    {
        return ptr != nullptr;
    }

    T* get() const
    {
        return ptr;
    }

    long use_count() const
    {
        return (ptr) ? *count : 0;
    }

    T& operator*() const
    {
        return *ptr;
    }

    T* operator->() const
    {
        return ptr;
    }

    void swap(shared_ptr& x) noexcept
    {
        std::swap(this->ptr, x.ptr);
        std::swap(this->count, x.count);
    }

    void reset(T *ptr = 0)
    {
        shared_ptr<T>(ptr).swap(*this);
    }

  private:
    // data members
    T* ptr;
    int *count;
  };
} // namespace stepik


#endif // MY_SHARED_PTR_H
