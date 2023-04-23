
	template <typename T>
	class shared_ptr
	{

		template <typename OtherT>
		friend class shared_ptr;
	public:

		explicit shared_ptr(T *ptr = 0) :
			m_ptr(ptr), m_count(ptr ? new size_t(1) : nullptr)
		{
		}

		~shared_ptr()
		{
			if (m_ptr) {
				if (*m_count == 1) {
					delete m_count;
					delete m_ptr;
					m_ptr = nullptr;
					m_count = nullptr;
				}
				else (*m_count)--;
			}
		}

		template <typename OtherT>
		shared_ptr(const shared_ptr<OtherT> & other)
		{
			if (other.get())
			{
				m_ptr = other.get();
				m_count = other.get_count();
				(*m_count)++;

			}
			else {
				m_ptr = nullptr;
				m_count = nullptr;
			}

		}


		template <typename OtherT>
		shared_ptr& operator = (const shared_ptr<OtherT> & other)
		{
			shared_ptr p(other);
			swap(p);
		}


		template <typename OtherT>
		bool operator==(const shared_ptr<OtherT> &other) const
		{
			return (m_ptr == other.m_ptr);
		}

		explicit operator bool() const
		{

			return (m_ptr != nullptr);
		}

		T* get() const
		{
			return m_ptr;
		}

		long use_count() const
		{
			return (m_count) ? *m_count : 0;
		}

		T& operator*() const
		{
			return (*m_ptr);
		}

		T* operator->() const
		{
			return m_ptr;
		}

		void swap(shared_ptr& x) noexcept
		{
			if (this != &x)
			{
				shared_ptr<T> tmp(*this);
				*this = x;
				x = tmp;
			}
		}



		void reset(T *ptr = 0)
		{
			shared_ptr p(ptr);
			swap(p);
		}

	private:
		T *m_ptr;
		size_t *m_count;

		size_t* get_count() const
		{
			return m_count;
		}


	};
