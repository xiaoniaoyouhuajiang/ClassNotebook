#ifndef MYSHAREDPTR_HPP
#define MYSHAREDPTR_HPP

namespace my_impl
{
  template <typename T>
  class shared_ptr
  {
  public:
    template<class V> friend class shared_ptr;
    typedef T element_type;
    typedef size_t size_type;

    explicit shared_ptr(element_type *ptr = 0)
    {
        object = ptr;
        ref_count = object ? new size_type(1) : nullptr;
    }

    ~shared_ptr() {
        remove();
    }

    shared_ptr(const shared_ptr & other)
    {
        object = other.get();
	    ref_count = other.get_count();
        if(use_count())
		    ++(*ref_count);
    }

    template <typename X>
    shared_ptr(const shared_ptr<X> & other)
    {
        object = other.get();
	    ref_count = other.get_count();
        if(use_count())
		    ++(*ref_count);
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
        if (this != &other) {
            remove();
		    object = other.get();
			ref_count = other.get_count();
            if(use_count())
			    ++(*ref_count);
		}
	    return *this;
    }

    template <typename X>
    shared_ptr& operator=(const shared_ptr<X> & other)
    {
        if (!(get() == other.get())) {
            remove();
			object = other.get();
			ref_count = other.get_count();
            if(use_count())
			    ++(*ref_count);
		}
	    return *this;
    }

    explicit operator bool() const { return object != nullptr; }

    element_type* get() const { return object; }

    size_type* get_count() const { return ref_count; }

    size_type use_count() const { return object ? *ref_count : 0; }

    element_type& operator*() const { return *object; }

    element_type* operator->() const { return object; }

    void swap(shared_ptr& x) noexcept { std::swap(*this, x); }

    void reset(element_type *ptr = 0) { shared_ptr<element_type>(ptr).swap(*this); }


  private:

    void remove() {
      if (use_count() > 1)
	    --(*ref_count);
	  else {
	    delete object;
		delete ref_count;
	    object = nullptr;
		ref_count = nullptr;
	  }
	}

    element_type *object;
	size_type *ref_count;
  };

  template <class X, class Y>
  bool operator== (const shared_ptr<X> & a, const shared_ptr<Y> & b) {
    return a.get() == b.get();
  }
} //namespace my_impl

#endif //MYSHAREDPTR_HPP