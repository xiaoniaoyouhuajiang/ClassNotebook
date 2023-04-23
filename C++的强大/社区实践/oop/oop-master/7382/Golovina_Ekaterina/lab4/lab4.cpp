namespace stepik
{
  template <typename T>
  class shared_ptr
  {
  public:
    template <typename U>
    friend class shared_ptr;
      
    explicit shared_ptr(T *ptr = 0):ptr(ptr),counter(nullptr)
    {
      if (this->ptr) counter = new long(1);
    }

    ~shared_ptr()
    {
      if (ptr) destroying();
    }

    shared_ptr(const shared_ptr & other):ptr(other.ptr),counter(other.counter)
    {
        if (ptr) (*counter)++;
    }

    template <typename U>
    shared_ptr(const shared_ptr<U> & other):ptr(other.ptr),counter(other.counter)
    {
	    if (ptr) (*counter)++;
    }
      
    shared_ptr& operator=(const shared_ptr & other)
    {
      	if (ptr != other.ptr){
		    if (ptr) destroying();
		    ptr=other.ptr;
		    counter=other.counter;
		    if (ptr!= nullptr) (*counter)++;
	    }
	    return *this;
    }

    template <typename U>
    shared_ptr& operator=(const shared_ptr<U> & other)
    {
        if (ptr != other.ptr){
                if (ptr) destroying();
                ptr=other.ptr;
                counter=other.counter;
                if (ptr!= nullptr) (*counter)++;
        }
        return *this;
    }
      
    template <typename U>
    bool operator==(const shared_ptr<U>& other) const{
	return ptr == other.ptr;
    }

    template <typename U>
    bool operator!=(const shared_ptr<U>& other) const{
        return ptr != other.ptr;
    }
      
    explicit operator bool() const
    {
      if (ptr == nullptr) return false;
      else return true;
    }

    T* get() const
    {
      return ptr;
    }

    long use_count() const
    {
        if (counter) return *counter;
        else return 0;
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
      std::swap(ptr,x.ptr);
      std::swap(counter,x.counter);
    }

    void reset(T *ptr = 0)
    {
        if (this->ptr) destroying();
	    this->ptr = ptr;
	    if (this->ptr) counter = new long(1); 
        else counter = nullptr;
    }

  private:
    void destroying(){
		if (*counter==1){ 
			delete ptr;
			delete counter;
      	}
		else (*counter)--;
	}
    T * ptr;
    long * counter;
  };      
} // namespace stepik
