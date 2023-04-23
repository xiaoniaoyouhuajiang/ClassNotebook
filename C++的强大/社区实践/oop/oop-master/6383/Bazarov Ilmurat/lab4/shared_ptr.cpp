namespace stepik
{
  template <typename T>
  class shared_ptr
  {
      template <typename TN>
      friend class shared_ptr;
  public:
    explicit shared_ptr(T *ptr = 0)
    {
         this->k = new int(1);
         this->ptr = ptr;
    }

    ~shared_ptr()
    {
      dec();
    }
    template <typename TN>
    shared_ptr(const shared_ptr <TN> & other)
    {
      this->ptr = other.ptr;
      this->k = other.k;
       inc();
    }
       shared_ptr(const shared_ptr & other)
    {
      this->ptr = other.ptr;
      this->k = other.k;
       inc();
    }
template <typename TN>
    shared_ptr& operator=(const shared_ptr<TN> & other)
    {
      if((void*)other.ptr == (void*)(this->ptr)) return *this;
          dec();
       this->ptr = (T*)other.ptr;
       this->k = other.k;
        inc();
         return *this;
    }
      shared_ptr& operator=(const shared_ptr & other)
    {
      if((void*)other.ptr == (void*)(this->ptr)) return *this;
          dec();
        this->ptr = (T*)other.ptr;
       this->k = other.k;
        inc();
         return *this;
    }
      template <typename TN>
    bool operator ==(const shared_ptr<TN> &other) const{
        return (void*)ptr == (void*)other.ptr;
    }
      
    bool operator ==(const shared_ptr &other)const{
        return (void*)ptr == (void*)other.ptr;
    }
    explicit operator bool() const
    {
      return (ptr != nullptr);
    }

    T* get() const
    {
      return ptr;
    }

    long use_count() const
    {
        if (this->ptr == nullptr) return 0;
        return *k;
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
       std::swap(k,x.k); 
     
    }

    void reset(T *ptr = 0)
    {
      dec();
       k = new int(1);
       this->ptr = ptr;
    }
    
  private:
    T *ptr;
    int *k;
    void dec(){
   
        (*k)--;
        if ((*k) == 0){
            delete ptr;
            delete k;
            ptr = nullptr;
            k = nullptr;
        }
    }
    void inc(){
        (*k)++;
    }
  };  }    
// namespace stepik
