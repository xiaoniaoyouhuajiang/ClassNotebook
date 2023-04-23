#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <iostream>

namespace stepik
{
  template <typename T>
  class shared_ptr
  {
    template<class A> friend class shared_ptr;
  public:
    explicit shared_ptr(T *ptr = 0) : pointer(ptr), counter(ptr ? new long(1) : nullptr) {}

    ~shared_ptr()
    {
        if(use_count() > 1)
            (*counter)--;
        else{
            delete pointer;
            delete counter;
        }
        pointer = nullptr;
        counter = nullptr;
    }

    shared_ptr(const shared_ptr & other) : pointer(other.pointer), counter(other.counter)
    {
        if(use_count())
            (*counter)++;
    }

    template <typename A>
    shared_ptr(const shared_ptr<A> & other) : pointer(other.pointer), counter(other.counter)
    {
        if(use_count())
            (*counter)++;
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
        if(pointer != other.pointer){
            this->~shared_ptr();
            pointer = other.pointer;
            counter = other.counter;
            if(use_count())
                (*counter)++;
        }
        return *this;
    }

    template <typename A>
    shared_ptr& operator=(const shared_ptr<A> & other)
    {
        if(pointer != other.pointer){
            this->~shared_ptr();
            pointer = other.pointer;
            counter = other.counter;
            if(use_count())
                (*counter)++;
        }
        return *this;
    }

    template <typename A>
    bool operator == (const shared_ptr<A> &other) const
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
        return counter ? *counter : 0;
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
        std::swap(pointer,x.pointer);
        std::swap(counter,x.counter);
    }

    void reset(T *ptr = 0)
    {
        this->~shared_ptr();
        pointer = ptr;
        counter = ptr ? new long(1) : nullptr;
    }

  private:
    T* pointer;
    long* counter;
  };
}

#endif // SHARED_PTR_H
