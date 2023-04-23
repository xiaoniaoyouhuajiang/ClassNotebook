#pragma once
namespace stepik
{
	template <typename T>
	class shared_ptr
	{
	public:
		typedef long unsigned int count_type;
		explicit shared_ptr(T *ptr = 0)
		{
			if (ptr == 0) {
				object = nullptr;
				count_ptr = new count_type(0);
			}
			else {
				object = ptr;
				count_ptr = new count_type(1);
			}
		}

		~shared_ptr()
		{
			if (object != 0) {
				(*(count_ptr))--;
			}
			if (use_count() == 0) {
				delete object;
			}
		}

		shared_ptr(const shared_ptr & other) : object(other.object), count_ptr(other.count_ptr)
		{
			if (get() != 0)
				(*(count_ptr))++;
		}

		template <class Y>
		shared_ptr(const shared_ptr<Y> & other) : object(other.get()), count_ptr(other.get_count()) {
			if (get() != 0)
				(*(count_ptr))++;
		}


		shared_ptr& operator=(const shared_ptr & other)
		{
			shared_ptr(other).swap(*this);
			return *this;
		}

		template <class Y>
		shared_ptr& operator=(const shared_ptr<Y> & other) {
			shared_ptr(other).swap(*this);
			return *this;
		}

		explicit operator bool() const
		{
			return (get() != 0);
		}

		T* get() const
		{
			return object;
		}

		count_type use_count() const
		{
			return *count_ptr;
		}

		count_type* get_count() const {
			return count_ptr;
		}

		T& operator*() const
		{
			return *object;
		}

		T* operator->() const
		{
			return object;
		}

		void swap(shared_ptr& x) noexcept
		{
			std::swap(x.object, object);
			std::swap(x.count_ptr, count_ptr);
		}

		void reset(T *ptr = 0)
		{
			shared_ptr<T>(ptr).swap(*this);
		}

	private:
		T * object;
		count_type* count_ptr;
	};

	template <class U, class Y>
	bool operator==(const shared_ptr<U>& a, const shared_ptr<Y>& b) noexcept
	{
		return a.get() == b.get();
	}


} // namespace stepik
