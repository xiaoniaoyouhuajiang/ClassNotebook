#include <algorithm>
namespace stepik
{
  template <typename T>
  class shared_ptr
  {
  public:
    explicit shared_ptr(T *ptr = nullptr)
    : ptr(ptr)
    , counter(ptr?new long{0}:nullptr)
    {}
    void clear(){
    if(counter && *counter)
            -- *counter;
        else {
            delete counter;
            delete ptr;
            counter = nullptr;
        }
       ptr = nullptr; 
    }
    ~shared_ptr()
    {
        clear();
    }
      template <class TT>
      friend class shared_ptr;
      
      
    template <class TT>  
    shared_ptr(const shared_ptr<TT> & other)
    : ptr(other.ptr)
    , counter(other.counter){
        if(ptr) ++ *counter;
    }
    
    template <class TT>
    shared_ptr& operator=(const shared_ptr<TT> & other)
    {
        if(other.ptr == ptr) return *this;
        clear();
		ptr = other.ptr;
        counter = other.counter;
        if(ptr) ++ *counter;
        return *this;
    }
    template <class TT>
    bool operator==(const shared_ptr<TT> &other) const{
        return ptr == other.ptr;
    }

    explicit operator bool() const
    {
        return ptr;
    }

    T* get() const
    {
        return ptr;
    }

    long use_count() const
    {
        return counter?1+*counter:0;
    }

    T& operator*() const
    {
      if(!ptr)throw std::bad_alloc();
      return *ptr;
    }

    T* operator->() const
    {
      return ptr;
    }

    void swap(shared_ptr& x) noexcept
    {
      std::swap(ptr,x.ptr);
      std::swap(counter,x.counter);
    }

    void reset(T *ptr = 0)
    {
        shared_ptr<T>(ptr).swap(*this);
    }
  private:
      T* ptr;
      long *counter;
  };
}