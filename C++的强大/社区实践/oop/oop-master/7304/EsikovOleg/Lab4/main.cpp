#include <iostream>

namespace stepik
{
template <typename T>
class shared_ptr
{
    template<class A> friend class shared_ptr;

public:
    explicit shared_ptr(T *ptr = 0) : ref(ptr), ref_count((ptr != nullptr) ? new long(1) : nullptr) {}

    ~shared_ptr()
    {
        if(use_count() > 1)
            (*ref_count) -= 1;
        else
        {
            delete ref;
            delete ref_count;
            ref = nullptr;
            ref_count = nullptr;
        }
    }

    shared_ptr(const shared_ptr & other) : ref(other.ref), ref_count(other.ref_count)
    {
        if(use_count())
            (*ref_count)++;
    }

    template <typename A>
    shared_ptr(const shared_ptr<A> & other) : ref(other.ref), ref_count(other.ref_count)
    {
        if(use_count())
            (*ref_count)++;
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
        if(ref != other.get())
        {
            this->~shared_ptr();
            ref = other.ref;
            ref_count = other.ref_count;
            if(use_count())
                (*ref_count)++;
        }
        return *this;
    }

    template <typename A>
    shared_ptr& operator=(const shared_ptr<A> & other)
    {
        if(ref != other.get())
        {
            this->~shared_ptr();
            ref = other.ref;
            ref_count = other.ref_count;
            if(use_count())
                (*ref_count)++;
        }
        return *this;
    }

    template <typename A>
    bool operator == (const shared_ptr<A> &other) const
    {
        return (void*)ref == (void*)other.ref;
    }

    bool operator == (const shared_ptr &other)const
    {
        return (void*)ref == (void*)other.ref;
    }

    explicit operator bool() const
    {
        return ref != nullptr;
    }

    T* get() const
    {
        return ref;
    }

    long use_count() const
    {
        return (ref != nullptr) ? *ref_count : 0;
    }

    T& operator*() const
    {
        return *ref;
    }

    T* operator->() const
    {
        return ref;
    }

    void swap(shared_ptr& x) noexcept
    {
        std::swap(ref, x.ref);
        std::swap(ref_count, x.ref_count);
    }

    void reset(T *ptr = 0)
    {
        shared_ptr<T>(ptr).swap(*this);
    }

private:
    T* ref;
    long* ref_count;
};
}   // namespace stepik

using namespace std;
using stepik::shared_ptr;

int main()
{
    int* ptr1 = new int;
    *ptr1 = 10;
    shared_ptr<int> s_ptr1(ptr1);
    cout << "s_ptr1.use_count(): " << s_ptr1.use_count() << endl;
    int* ptr2 = new int;
    *ptr2 = 20;
    shared_ptr<int> s_ptr2(s_ptr1);
    cout << "s_ptr2.use_count(): " << s_ptr2.use_count() << endl;
    if(s_ptr1 == s_ptr2)
        cout << "s_ptr1 == s_ptr2" << endl;
    else
        cout << "s_ptr1 != s_ptr2" << endl;
    s_ptr2.reset(ptr2);
    cout << "s_ptr1.use_count(): " << s_ptr1.use_count() << endl;
    cout << "s_ptr2.use_count(): " << s_ptr2.use_count() << endl;
    cout << "*s_ptr1.get(): " << *s_ptr1.get() << endl;
    cout << "*s_ptr2.get(): " << *s_ptr2.get() << endl;
    shared_ptr<int> s_ptr3(ptr2);
    s_ptr1.swap(s_ptr3);
    cout << "*s_ptr1.get(): " << *s_ptr1.get() << endl;
    cout << "*s_ptr3.get(): " << *s_ptr3.get() << endl;

    return 0;
}
