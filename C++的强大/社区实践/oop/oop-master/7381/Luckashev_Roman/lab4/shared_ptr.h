namespace stepik
{
	template <typename T>
	class shared_ptr
	{
	public:
        
        template<typename U> friend class shared_ptr;
        
		explicit shared_ptr(T *ptr = nullptr) :
			t_pointer(ptr),
			ref_counter(ptr ? new size_t(1) : nullptr)
		{
		}
        
		~shared_ptr()
		{
			dec_ref_count();
		}

		shared_ptr(const shared_ptr & other) :
			t_pointer(other.t_pointer),
			ref_counter(other.ref_counter)
		{
			inc_ref_count();
		}
        
        template<typename U> 
		shared_ptr(const shared_ptr<U> & other) :
			t_pointer(other.t_pointer),
			ref_counter(other.ref_counter)
		{
			inc_ref_count();
		}

		shared_ptr& operator=(const shared_ptr & other)
		{
			shared_ptr(other).swap(*this);
			return *this;
		}

        template<typename U> 
		shared_ptr& operator=(const shared_ptr<U> & other)
		{
			shared_ptr(other).swap(*this);
			return *this;
		} 
        
		explicit operator bool() const
		{
			return t_pointer != nullptr;
		}

		T* get() const
		{
			return t_pointer;
		}

		size_t use_count() const
		{
			return t_pointer ? *ref_counter : 0;
		}

		T& operator*() const
		{
			return *t_pointer;
		}

		T* operator->() const
		{
			return t_pointer;
		}
        
        template<typename U>
        bool operator == (const shared_ptr<U> & other) const
        {
            return t_pointer == other.t_pointer;    
        }

        template<typename U>
        bool operator != (const shared_ptr<U> & other) const
        {
            return !(t_pointer == other.t_pointer);    
        }
        
		void swap(shared_ptr& x) noexcept
		{
			std::swap(t_pointer, x.t_pointer);
			std::swap(ref_counter, x.ref_counter);
		}

		void reset(T *ptr = 0)
		{
			dec_ref_count();
			t_pointer = ptr;
			ref_counter = ptr ? new size_t(1) : nullptr;
		}

	private:
		// data members
		size_t * ref_counter;
		T* t_pointer;

		void destroy() {
			if (t_pointer) {
				delete ref_counter;
				delete t_pointer;
			}
		}

		void inc_ref_count() {
			if (ref_counter) (*ref_counter)++;
		}

		void dec_ref_count() {
			if (ref_counter) (*ref_counter)--;
			if (!use_count()) destroy();
		}

	};
} // namespace stepik