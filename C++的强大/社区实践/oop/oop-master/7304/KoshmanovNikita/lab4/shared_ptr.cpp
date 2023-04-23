namespace stepik
{
  template <typename T>
  class shared_ptr
  {
	template <typename T2> friend class shared_ptr;
   public:
        explicit shared_ptr(T *ptr = 0) : m_ptr(ptr), m_count(new long(1)){}

        ~shared_ptr()
        {
            delete_ptr();
        }

        shared_ptr(const shared_ptr & other) : m_ptr(other.m_ptr), m_count(other.m_count)
        {
	        if(m_count)
		        (*m_count)++;
        }

	template<typename T2> shared_ptr(const shared_ptr<T2>& other) : m_ptr(other.m_ptr), m_count(other.m_count)
	{
		if(m_count)
			(*m_count)++;
	}

        shared_ptr& operator=(const shared_ptr & other)
        {
	        if(m_ptr != other.m_ptr)
	        {
		        delete_ptr();
		        m_ptr = other.m_ptr;
		        m_count = other.m_count;
			    (*m_count)++;
	        }
	        return *this;
        }

	template<typename T2> shared_ptr& operator=(const shared_ptr<T2>& other)
	{
		if(m_ptr!=other.m_ptr)
		{
          	delete_ptr();
          	m_ptr=other.m_ptr;
          	m_count=other.m_count;
          	(*m_count)++;
      		}
	return *this;
	}

	template <typename T2> bool operator==(const shared_ptr<T2>& other) const
	{
		return m_ptr==other.m_ptr;
	}

        explicit operator bool() const
        {
	        return m_ptr != nullptr;
        }

        T* get() const
        {
	        return m_ptr;
        }

        long use_count() const
        {
	        return (m_ptr) ? (*m_count) : 0;
        }

        T& operator*() const
        {
	        return *m_ptr;
        }

        T* operator->() const
        {
	        return m_ptr;
        }

        void swap(shared_ptr& x) noexcept
        {
	        std::swap(m_ptr, x.m_ptr);
	        std::swap(m_count, x.m_count);
        }

        void reset(T *ptr = 0)
        {
	        shared_ptr tmp(ptr);
	        swap(tmp);
        }

   private:
	    T* m_ptr;
	    long* m_count;
	    void delete_ptr()
	    {
		    if((*m_count) > 0)
			    (*m_count)--;
		    if((*m_count) == 0)
		    {
			    delete m_ptr;
			    delete m_count;
		    }
	    }
  };
} // namespace stepik
