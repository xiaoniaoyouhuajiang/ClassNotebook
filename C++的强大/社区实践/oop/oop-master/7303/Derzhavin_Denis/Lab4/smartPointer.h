namespace stepik
{
  template <typename T>
  class shared_ptr
  {
  public:      
    explicit shared_ptr(T *ptr = 0): ptr(ptr), counter(ptr ? new long(1) : 0) {}

    ~shared_ptr()
    {
      decreaseCounterAndFreeIfAllowed();
    }

    template<typename U>
    shared_ptr(const shared_ptr<U> &other): ptr(other.ptr), counter(other.counter)
    {
      if (ptr)
          ++*counter;
    }

    template<typename U>
    shared_ptr& operator=(const shared_ptr<U> & other)
    {
        if (*this != other) {
            if (other.ptr)
                ++*other.counter;

            decreaseCounterAndFreeIfAllowed();
            ptr = other.ptr;
            counter = other.counter;
        }
        return *this;
    }

    explicit operator bool() const
    {
      return get() != nullptr;
    }

    T* get() const
    {
      return ptr;
    }

    long use_count() const
    {
      return ptr ? *counter : 0;
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
		if (this != &x) {
			shared_ptr<T> tmp(*this);
			*this = x;
			x = tmp;
		}
    }

    void reset(T *ptr = 0)
    {
        decreaseCounterAndFreeIfAllowed();
        this->ptr = ptr;
        counter = ptr ? new long(1) : 0;  
    }
    
    template<typename U>
    bool operator==(const shared_ptr<U>& other) const{
      	return ptr == other.ptr;
    }

    template<typename U>
    bool operator!=(const shared_ptr<U>& other) const{
      	return ptr != other.ptr;
    }
  private:
    void decreaseCounterAndFreeIfAllowed() {
        if (ptr && !--*counter) {
            delete ptr;
            ptr = nullptr;
            delete counter;
            counter = 0;
        }
    }
  private:
    template<typename U>
    friend class shared_ptr;
      
    T *ptr;
    long *counter;
  };      
} // namespace stepik