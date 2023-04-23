namespace stepik
{
  template <typename T>
  class shared_ptr
  {
    template<typename U>
    friend class shared_ptr;
  public:
    explicit shared_ptr(T *ptr = 0) : ptr_(ptr), count(new unsigned(1)){}
    
    ~shared_ptr()
    {
      dec();
    }

    shared_ptr(const shared_ptr & other) : ptr_(other.ptr_), count(other.count)
    {
     	if (count) inc();
    }
    
    template <typename U>
    shared_ptr(const shared_ptr<U> & other) : ptr_(other.ptr_), count(other.count)
    {
     	if (count) inc();
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
      /*if (this != &other)
        shared_ptr(other).swap(*this); 
      return *this;*/
      if ((void*)ptr_ == (void*)other.ptr_) return *this;
      ptr_ = other.ptr_;
      count = other.count;
      inc();
    }
    
    template <typename U>
    shared_ptr& operator=(const shared_ptr<U> & other)
    {
      /*if (this != &other)
        shared_ptr<U>(other).swap(*this); 
      return *this;*/
      if ((void*)ptr_ == (void*)other.ptr_) return *this;
      ptr_ = other.ptr_;
      count = other.count;
      inc();
    }
    
    bool operator == (const shared_ptr &other) const
    {
      return (void*) ptr_ == (void*) other.ptr_;
    }
    
    template <typename U>
    bool operator == (const shared_ptr<U> &other) const
    {
      return (void*) ptr_ == (void*) other.ptr_;
    }

    explicit operator bool() const
    {
      return ptr_ != nullptr;
    }

    T* get() const
    {
      return ptr_;
    }

    long use_count() const
    {
      return (ptr_) ?  *count : 0;
    }

    T& operator*() const
    {
      return *ptr_;
    }

    T* operator->() const
    {
      return ptr_;
    }

    void swap(shared_ptr& x) noexcept
    {
      std::swap(this->ptr_, x.ptr_);
      std::swap(this->count, x.count);
    }

    void reset(T *ptr = 0)
    {
      shared_ptr<T>(ptr).swap(*this);
    }

  private:
    T *ptr_;
    unsigned *count;
    void inc() { ++(*count); }
    void dec() 
	  { 
		  if (--(*count) == 0) 
		  {
              delete ptr_;
              delete count;
       }
	  }
  };      
}