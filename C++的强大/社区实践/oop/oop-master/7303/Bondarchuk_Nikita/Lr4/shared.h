#ifndef SHARED_H
#define SHARED_H
namespace stepik
{
  template <typename T>
  class shared_ptr
  {
  public:
    explicit shared_ptr(T *newptr = 0)
    {
         pointer = newptr;
        if (pointer != nullptr)
            counter = new int(1);
        else
            counter  = NULL;
      // implement this
    }

    ~shared_ptr()
    {
        if (pointer != nullptr)
        {
            if (*counter == 1)
            {
                delete pointer;
                delete counter;
            }
            else
                (*counter)--;
        }
      // implement this
    }




    template <typename H>
    shared_ptr(const shared_ptr<H> & other): pointer(other.pointer), counter(other.counter)
    {
        if (pointer)
            (*counter)++;
      // implement this
    }

    template <typename H>
    shared_ptr& operator=(const shared_ptr<H> & other)
    {
        shared_ptr<T>(other).swap(*this);
        return *this;
      // implement this
    }

    explicit operator bool() const
    {
         if (pointer)
            return true;
        return false;
      // implement this
    }

    T* get() const
    {
        return pointer;
      // implement this
    }

    long use_count() const
    {
        if (counter)
            return (*counter);
        return 0;
      // implement this
    }

    T& operator*() const
    {
        return *pointer;
      // implement this
    }

    T* operator->() const
    {
         return pointer;
      // implement this
    }

    void swap(shared_ptr& x) noexcept
    {
        std::swap(pointer,x.pointer);
        std::swap(counter,x.counter);
      // implement this
    }

    void reset(T *ptr = 0)
    {
        shared_ptr<T>(ptr).swap(*this);
      // implement this
    }
      template <typename H>
friend class shared_ptr;

      template <typename H>
    bool operator==(const shared_ptr<H> &other) const{
     if(pointer== other.pointer)
       return 1;
     else
       return 0;
    }




  private:
      T* pointer;
    int* counter;

    // data members
  };

  template<typename H>
shared_ptr<H> make_shared(H* ptr)
{
    return shared_ptr<H>(ptr);
}

}

// namespace stepik
#endif // SHARED_H
