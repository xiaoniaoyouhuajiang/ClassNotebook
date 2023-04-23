
namespace stepik
{
	template <typename T>
	class shared_ptr
	{
		template <typename Y> friend class shared_ptr;

	public:
		explicit shared_ptr(T *ptr = 0) : ptr(ptr), count(0)
		{
			if (ptr)
			{
				count = new size_t(1);
			}
		}

		template <typename Y>
		shared_ptr(const shared_ptr<Y> & other)
		{
			if (other.operator bool())
			{
				ptr = other.ptr;
				count = other.count;
				++*count;

			}
			else
			{
				ptr = nullptr;
				count = nullptr;
			}

		}

		template <typename Y>
		shared_ptr& operator=(shared_ptr<Y> & other)
		{
			this->~shared_ptr();
			if (other.ptr)
			{
				ptr = other.ptr;
				count = other.count;
				++*count;
			}
			else
			{
				ptr = nullptr;
				count = nullptr;
			}
			return *this;
		}

		template <typename Y>
		bool operator==(const shared_ptr<Y> &other) const
		{
			return (ptr == other.ptr);
		}

		template<typename Y>
		bool operator!=(const shared_ptr<Y> &other)
		{
			return (ptr != other.ptr);
		}

		explicit operator bool() const
		{
			if (ptr)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		T* get() const
		{
			return ptr;
		}

		long use_count() const
		{
			if (count)
			{
				return *count;
			}
			else
			{
				return 0;
			}
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
			if (this != &x)
			{
				shared_ptr<T> tmp(*this);
				*this = x;
				x = tmp;
			}
		}

		void reset(T *ptr = 0)
		{
			shared_ptr tmp(ptr);
			swap(tmp);
		}

	private:
		T* ptr;
		size_t* count;
	};
} // namespace stepik

