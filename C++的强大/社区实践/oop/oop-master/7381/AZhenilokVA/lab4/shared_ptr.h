namespace stepik
{
  template <typename T>
  class shared_ptr
  {
  public:
    explicit shared_ptr(T *ptr = 0)
     {
        this->ptr = ptr;
        if(ptr != nullptr)
          count = new long(1);
        else 
          count = nullptr;
        }

    ~shared_ptr()
    {
      if(ptr != nullptr){
        if((*count) == 1){
          delete ptr;
          delete count;
        }
        else 
          (*count)--;
      }
    }

    shared_ptr(const shared_ptr & other)
    : ptr(other.ptr)
    , count(other.count)
    {
      if(ptr) 
        (*count)++;
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
      shared_ptr<T>(other).swap(*this);
      return *this;
    }
      
    template <class Derived>
    friend class shared_ptr;
        
    template <class Derived>
    shared_ptr(const shared_ptr<Derived> & other) : ptr(other.ptr), count(other.count)
    { 
      if(ptr) 
        (*count)++;
    }
        
    template <class Derived>
    shared_ptr& operator=(const shared_ptr<Derived> & other)
    {
      shared_ptr<T>(other).swap(*this);
      return *this;
    }
        
    template <class Derived>
    bool operator==(const shared_ptr<Derived> & other) const
    {
      return ptr == other.ptr;
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
      return ptr == nullptr ? 0 : *count;
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
      std::swap(ptr, x.ptr);
      std::swap(count, x.count);
    }

    void reset(T *ptr = 0)
    {
      shared_ptr temp(ptr);
      swap(temp);    
    }

  private:
    T * ptr;
    long * count;
  };      
} // namespace stepik