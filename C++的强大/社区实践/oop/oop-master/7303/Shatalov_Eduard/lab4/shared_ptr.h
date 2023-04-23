namespace stepik
{
  template <typename T>
  class shared_ptr
  {
  public:
    explicit shared_ptr(T *ptr = 0)
    {
      // implement this
      pointer = ptr;
        if (pointer != nullptr)
            count = new int(1);
        else
            count  = nullptr;
    }
	template <typename Z>
friend class shared_ptr;
    ~shared_ptr()
    {
      // implement this
        if (pointer != nullptr)
        {
            if (*count == 1)
            {
                delete pointer;
                delete count;
            }
            else 
                (*count)--;
        }
    }

	template <typename Z>
	bool operator==(const shared_ptr<Z> &other) const{
	return pointer== other.pointer;
}


    template <typename Z>
    shared_ptr(const shared_ptr<Z> & other):pointer(other.pointer),count(other.count)
    {
        if (pointer)
            (*count)++;
      // implement this
    }
	template <typename Z>
    shared_ptr& operator=(const shared_ptr<Z> & other)
    {
      // implement this
        shared_ptr<T>(other).swap(*this);
        return *this;
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
        if (count)
            return (*count);
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
      // implement this
        return pointer;
    }

    void swap(shared_ptr& x) noexcept
    {
        std::swap(pointer,x.pointer);
        std::swap(count,x.count);
      // implement this
    }

    void reset(T *ptr = 0)
    {
      // implement this    
        shared_ptr<T>(ptr).swap(*this);
    }

  private:
    // data members
    T* pointer;
    int* count;
  };      
} // namespace stepik