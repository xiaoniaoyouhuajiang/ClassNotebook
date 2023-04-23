namespace stepik
{
  template <typename T>
  class shared_ptr
  {
  public:
    explicit shared_ptr(T *ptr = 0) : ptr(ptr), count(ptr ? new long(1) : nullptr)
    {
    }
      
    template <typename M>
    friend class shared_ptr;
      
    ~shared_ptr()
    {
        
      if (ptr != nullptr) {
          
          if( (*count) == 1 ) {
              delete ptr;
              delete count;
          } else { 
              (*count)--;
          }
          
       }
        
    }
    
    template <typename M>
	bool operator==(const shared_ptr<M> &other) const {
	  return ptr == other.ptr;
    }
    
    template <typename M>
    shared_ptr(const shared_ptr<M> & other): ptr(other.ptr), count(other.count)
    { 
        if (ptr) (*count)++;
    }
    
    template <typename M>
    shared_ptr& operator=(const shared_ptr<M> & other)
    {
      shared_ptr<T>(other).swap(*this);
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
      return ptr ? *count : 0;
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
      shared_ptr<T>(ptr).swap(*this);
    }

  private:
    T* ptr;
    long* count;
  };      
} // namespace stepik