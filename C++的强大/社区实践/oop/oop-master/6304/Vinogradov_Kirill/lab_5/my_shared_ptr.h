#pragma once
#include <iostream>

namespace stepik
{
	template <typename T>
	class shared_ptr
	{
	public:
		explicit shared_ptr(T *ptr = 0)
			:ptr(ptr), count(ptr ? new size_t(1) : new size_t(0))
		{
		}

		~shared_ptr()
		{
			if (ptr != 0) {
				--(*count);
			}
			if (use_count() == 0) {
				delete ptr;
			}
		}

		shared_ptr(const shared_ptr & other)
			: ptr(other.ptr), count(other.count)
		{
			if (get() != 0)
			{
				++(*count);
			}
		}

		shared_ptr& operator=(const shared_ptr & other)
		{
			shared_ptr(other).swap(*this);
			return *this;
		}

		template <class Third>
		shared_ptr(const shared_ptr<Third> & other)
			: ptr(other.get()), count(other.get_count())
		{
			if (get() != 0)
				++(*count);
		}

		template <class Third>
		shared_ptr& operator=(const shared_ptr<Third>& other)
		{
			shared_ptr(other).swap(*this);
			return *this;
		}


		explicit operator bool() const
		{
			if (ptr)
				return true;
			else
				return false;
		}

		T* get() const
		{
			return ptr;
		}

		size_t* get_count() const
		{
			return count;
		}

		size_t use_count() const
		{
			if (ptr)
				return *count;
			else
				return 0;
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
			std::swap(ptr, x.ptr);
			std::swap(count, x.count);
		}

		void reset(T *ptr = 0)
		{
			shared_ptr<T>(ptr).swap(*this);
		}

	private:

		T * ptr;
		size_t* count;
	};

	template <class First, class Second>
	bool operator== (const shared_ptr<First>& left, const shared_ptr<Second>& right)
	{
		return left.get() == right.get();
	}
} // namespace stepik