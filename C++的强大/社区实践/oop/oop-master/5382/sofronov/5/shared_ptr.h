#ifndef INC_5_SHARED_PTR_H
#define INC_5_SHARED_PTR_H

#include <iostream>


template <typename T>
class shared_ptr
{
public:

    template <typename X>
    friend class shared_ptr;

    explicit shared_ptr(T *ptr = 0)
            :smart(ptr)
    {
        if (smart == 0)
            count = nullptr;
        else
            count = new long(1);
    }

    ~shared_ptr()
    {
        decrease();
    }

    template <typename X>
    shared_ptr(const shared_ptr<X> & other):smart(other.smart), count(other.get_count())
    {
        count=other.count;
        if (count)
            ++(*count);
    }

    shared_ptr(const shared_ptr<T> & other):smart(other.smart), count(other.get_count())
    {
        count=other.count;
        if (count)
            ++(*count);
    }


    template <typename X>
    shared_ptr& operator=(const shared_ptr<X> & other)
    {
        decrease();
        smart=other.smart;
        count=other.count;
        if (count)
            ++(*count);
        return *this;
    }

    shared_ptr& operator=(const shared_ptr<T> & other)
    {
        decrease();
        smart=other.smart;
        count=other.count;
        if (count)
            ++(*count);
        return *this;
    }


    explicit operator bool() const
    {
        return (smart!=nullptr);
    }

    T* get() const
    {
        return smart;
    }

    long* get_count() const
    {
        return count;
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
        return *smart;
    }

    T* operator->() const
    {
        return smart;
    }

    void swap(shared_ptr& x) noexcept
    {
        shared_ptr<T> t(*this);
        *this = x;
        x = t;
    }

    void reset(T *ptr = 0)
    {
        shared_ptr<T>(ptr).swap(*this);
    }



private:
    T *smart;
    long *count;

    void decrease ()
    {
        if ((smart) &&(count)&&(!--(*count)))
        {
            delete smart;
            count=0;
        }
    }
};

template <typename X, typename  Y>
bool  operator==(const shared_ptr<X>& l, const shared_ptr<Y>& r)
{
    return  (l.get() == r.get());
}


template <class X, class Y>
bool   operator!=(const shared_ptr<X>& l, const shared_ptr<Y>& r)
{
    return !(l == r);
}

template <class X, class Y>
bool operator<(const shared_ptr<X>& l, const shared_ptr<Y>& r)
{
    return (l.get()<r.get());
}

template <class X, class Y>
bool  operator>(const shared_ptr<X>& l, const shared_ptr<Y>& r)
{
    return (r < l);
}

template <class X, class Y>
bool  operator<=(const shared_ptr<X>& l, const shared_ptr<Y>& r)
{
    return !(r < l);
}

template <class X, class Y>
bool  operator>=(const shared_ptr<X>& l, const shared_ptr<Y>& r)
{
    return !(l < r );
}

template <class X>
bool  operator==(const shared_ptr<X>& l, std::nullptr_t r)
{
    return !l;
}

template <class X>
bool  operator==(std::nullptr_t l, const shared_ptr<X>& r)
{
    return !r;
}

template <class X>
bool operator!=(const shared_ptr<X>& l, std::nullptr_t r)
{
    return (bool)l;
}

template <class X>
bool operator!=(std::nullptr_t l, const shared_ptr<X>& r)
{
    return (bool)r;
}
template< class X >
bool  operator<( const shared_ptr<X>& l, std::nullptr_t r )
{
    return (l.get() < nullptr);
}

template< class X >
bool  operator<( std::nullptr_t l, const shared_ptr<X>& r ) {
    return (nullptr < r);
}

template< class X >
bool  operator>( const shared_ptr<X>& l, std::nullptr_t r ) {
    return (nullptr < l);
}

template< class X >
bool  operator>( std::nullptr_t l, const shared_ptr<X>& r )
{
    return (r < nullptr);
}
template< class X >
bool  operator<=( const shared_ptr<X>& l, std::nullptr_t r )
{
    return !(nullptr < l);
}
template< class X >
bool  operator<=( std::nullptr_t l, const shared_ptr<X>& r )
{
    return !(r < nullptr);
}
template< class X >
bool  operator>=( const shared_ptr<X>& l, std::nullptr_t r )
{
    return !(l < nullptr);
}
template< class X >
bool  operator>=( std::nullptr_t l, const shared_ptr<X>& r )
{
    return !(nullptr < r);
}


#endif //INC_5_SHARED_PTR_H
