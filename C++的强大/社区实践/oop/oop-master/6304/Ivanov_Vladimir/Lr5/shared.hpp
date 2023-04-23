#ifndef shared_hpp
#define shared_hpp

namespace last
{
  template <typename T>
  class shared_ptr
  {
  template<class V> friend class shared_ptr;
  public:
    explicit shared_ptr(T *ptr = 0) :
        mptr(ptr), mcount(mptr ? new long(1) : nullptr)
    {
    }

    ~shared_ptr()
    {
        if (use_count() > 1) {
            --(*mcount);
        }
        else{
            delete mptr;
            delete mcount;
            mptr=nullptr;
            mcount = nullptr;
        }
    }
    template <typename V>
    shared_ptr(const shared_ptr<V> & other) :
      mptr(other.mptr), mcount(other.mcount)
    {
    if(use_count())
      (*mcount)++;

    }

    shared_ptr(const shared_ptr & other) :
        mptr(other.mptr), mcount(other.mcount)
      {
        if(use_count())
          (*mcount)++;
      }

    template <typename V>
    shared_ptr& operator=(const shared_ptr<V> & other)
    {
      if(get() != other.get()){
		  this->~shared_ptr();
    	mptr = other.mptr;
    	mcount = other.mcount;
        if(use_count())
          (*mcount)++;
      }
		  return *this;
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
      if(this != &other){
		  this->~shared_ptr();
    	mptr = other.mptr;
    	mcount = other.mcount;
        if(use_count())
          (*mcount)++;
      }
		  return *this;
    }

    explicit operator bool() const
    {
      return get()!= nullptr;
    }

    T* get() const
    {
      return mptr;
    }

    long use_count() const
    {
       return mptr ? *mcount : 0;
    }

    T& operator*() const
    {
      return *mptr;
    }

    T* operator->() const
    {
      return mptr;
    }

    void swap(shared_ptr& x) noexcept
    {
      std::swap(mptr,x.mptr);
	    std::swap(mcount,x.mcount);
    }

    void reset(T *ptr = 0)
    {
      shared_ptr<T>(ptr).swap(*this);
    }

  private:
    T* mptr;
    long* mcount;
  };
  template <class A, class B>
  bool operator != (const shared_ptr<A> & a, const shared_ptr<B> & b) {
    return a.get() != b.get();
  }
  template <class A, class B>
  bool operator== (const shared_ptr<A> & a, const shared_ptr<B> & b) {
    return a.get() == b.get();
  }
}

#endif //shared_hpp