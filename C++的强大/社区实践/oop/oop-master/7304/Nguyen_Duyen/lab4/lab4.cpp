
namespace stepik
{
	template <typename T>
	class shared_ptr
	{
	public:
		template<class Y>
		friend class shared_ptr;

		explicit shared_ptr(T *ptr = 0): m_ptr(ptr), m_counter(ptr?new long(1):nullptr)
		{}

		~shared_ptr()
		{
			// implement this
			if (m_ptr != nullptr) {
				if (*m_counter == 1) {
					delete m_ptr;
					delete m_counter;
					m_ptr = nullptr;
					m_counter = nullptr;
				}
				else
					(*m_counter)--;
			}
		}
		shared_ptr(const shared_ptr & other) : m_ptr(other.m_ptr), m_counter(other.m_counter)
		{
			// implement this
			if (use_count())
				(*m_counter)++;
		}

		template<typename Y>
		shared_ptr(const shared_ptr<Y> & other) : m_ptr(other.m_ptr), m_counter(other.m_counter)
		{
			// implement this
			if (use_count())
				(*m_counter)++;
		}

		shared_ptr& operator=(const shared_ptr & other)
		{
			// implement this
			shared_ptr(other).swap(*this);
		}

		template<typename Y>
		shared_ptr<T>& operator=(const shared_ptr<Y> & other)
		{
			// implement this
			shared_ptr<T>(other).swap(*this);
		}

		template <typename Y>
		bool operator==(const shared_ptr<Y>& other) const
		{
			// implement this
			return this->get() == other.get();
		}

		explicit operator bool() const
		{
			// implement this
			return m_ptr != nullptr;
		}

		T* get() const
		{
			// implement this
			return m_ptr;
		}

		long use_count() const
		{
			// implement this
			return m_ptr == nullptr ? 0 : *m_counter;
		}

		T& operator*() const
		{
			// implement this
			return *m_ptr;
		}

		T* operator->() const
		{
			// implement this
			return m_ptr;
		}

		void swap(shared_ptr& x) noexcept
		{
			// implement this
			T*temp_p = this->m_ptr;
			long* temp_c = this->m_counter;

			this->m_ptr = x.m_ptr;
			x.m_ptr = temp_p;
			this->m_counter = x.m_counter;
			x.m_counter = temp_c;
		}

		void reset(T *ptr = 0)
		{
			// implement this
			shared_ptr<T>(ptr).swap(*this);
		}

	private:
		// data members
		T* m_ptr;
		long* m_counter;
	};
} // namespace stepik
