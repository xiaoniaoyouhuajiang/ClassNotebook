
#include <iostream>
#include <cstddef>
#include <algorithm>


namespace stepik
{

	template <typename T>
	class shared_ptr
	{


	public:

		explicit shared_ptr(T *ptr = 0)
			:ptr_(ptr), count(ptr ? new long(1) : nullptr)
		{}

		~shared_ptr()
		{
			if (use_count() > 1) {
				--(*count);
			}
			else {
				delete ptr_;
				delete count;
				ptr_ = nullptr;
				count = nullptr;
			}
		}

		shared_ptr(const shared_ptr & other) :
			ptr_(other.ptr_), count(other.count)
		{
			if (use_count())
				(*count)++;
		}

		shared_ptr& operator=(const shared_ptr & other)
		{
			if (this != &other) {
				this->~shared_ptr();
				ptr_ = other.ptr_;
				count = other.count;
				if (use_count())
					(*count)++;
			}
			return *this;
		}

		template <class X>
		shared_ptr(const shared_ptr<X> & other)
		{
			if (other.get()) {
				ptr_ = other.get();
				count = other.get_count();
				++(*count);
			}
			else {
				ptr_ = nullptr;
				count = nullptr;
			}
		}

		template <class X>
		shared_ptr& operator=(const shared_ptr<X>& other)
		{
			this->~shared_ptr();
			if (other.get()) {
				ptr_ = other.get();
				count = other.get_count();
				++(*count);
			}
			else {
				ptr_ = nullptr;
				count = nullptr;
			}
			return *this;
		}


		explicit operator bool() const
		{
			return ptr_ != nullptr;
		}

		T* get() const
		{
			return ptr_;
		}
		long* get_count() const
		{
			return count;
		}


		long use_count() const
		{
			return ptr_ ? *count : 0;
		}

		T& operator*() const
		{
			return *ptr_;
		}

		T* operator->() const
		{
			return ptr_;
		}

		void swap(shared_ptr& x) noexcept
		{
			std::swap(ptr_, x.ptr_);
			std::swap(count, x.count);
		}

		void reset(T *ptr = 0)
		{
			shared_ptr<T>(ptr).swap(*this);
		}

	private:
		T* ptr_;
		long* count;

	};

	template <class A, class B>
	bool operator== (const shared_ptr<A>& left, const shared_ptr<B>& right) {
		return left.get() == right.get();
	}

}
