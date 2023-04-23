#include <iostream>

using namespace std;

namespace stepik
{
  template <typename T>
  class shared_ptr
  {
  public:
    explicit shared_ptr(T *ptr = nullptr) : pointer(ptr), count_link(new size_t(1))
    {}

    ~shared_ptr()
    {
        cout << "~shared_ptr(): " << " count_link = " << *count_link << " ptr = " << pointer << endl;
        if(*count_link > 0)
            --*count_link;

        if(*count_link == 0)
        {
            delete pointer;
            delete count_link;
        }
    }

    //Copy constructor
    shared_ptr(const shared_ptr & other)
    {
        pointer = other.pointer;
        count_link = other.count_link;
        ++*count_link;
    }

    //Assingment operator
    shared_ptr& operator=(const shared_ptr & other)
    {
        if(pointer!= other.pointer)
        {
            this->~shared_ptr();
            pointer = other.pointer;
            count_link = other.count_link;
            ++*count_link;
        }

        return *this;
    }

    explicit operator bool() const
    {
        return pointer!= nullptr;
    }

    T* get() const
    {
        return pointer;
    }

    long use_count() const
    {
       return *count_link;
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
        std::swap(count_link, x.count_link);
    }

    void reset(T *ptr = 0)
    {
        this->~shared_ptr();
        pointer = ptr;

        if(pointer)
            count_link = new size_t(1);
        else
            count_link = new size_t(0);
    }

  private:
    T* pointer;
    size_t *count_link;
  };
} // namespace stepik




int main()
{
    stepik::shared_ptr<int> a;
    stepik::shared_ptr<int> b = a;
    stepik::shared_ptr<int> c;
    c = b;

    return 0;
}
