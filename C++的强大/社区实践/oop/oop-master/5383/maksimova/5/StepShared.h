#include <algorithm>
#include <cstddef> 
namespace stepik
{
	template <typename T>
	class shared_ptr
	{
		template <typename T2>
		friend class shared_ptr;

	public:

		explicit shared_ptr(T *ptr = nullptr) {
			ptr_ = ptr;
			if (ptr_) {
				count_ = new size_t(1);
			}
			else {
				count_ = 0;
			}
		}
		~shared_ptr()
		{
			decrement_counter();
		}
		template <typename T2>
		shared_ptr(const shared_ptr<T2> & other)
		{
			ptr_ = other.ptr_;
			count_ = other.count_;
			if (ptr_) {
				++(*count_);
			}
		}
		template <typename T2>
		shared_ptr& operator=(const shared_ptr<T2> & other)
		{
			shared_ptr tmp(other);
			swap(tmp);
			return *this;
		}

		void decrement_counter() {
			if (count_ && ptr_ && !--(*count_)) {
				delete ptr_;
				delete count_;
				count_ = 0;
			}
		}
		explicit operator bool() const
		{
			return (ptr_ != nullptr);
		}

		T* get() const
		{
			return ptr_;
		}

		long use_count() const
		{
			return (count_ ? *count_ : 0);
		}

		T& operator*() const
		{
			return *ptr_;
		}

		T* operator->() const
		{
			return ptr_;
		}
		template <typename T2>
		bool operator==(const shared_ptr<T2> &other) const
		{
			return (ptr_ == other.ptr_);
		}

		void swap(shared_ptr& x) noexcept
		{
			std::swap(ptr_, x.ptr_);
			std::swap(count_, x.count_);
		}

		void reset(T *ptr = 0)
		{
			if (ptr_ != ptr) {
				decrement_counter();
				ptr_ = ptr;
				if (ptr) {
					count_ = new size_t(0);
					if (ptr_) {
						++(*count_);
					}
				}
			}
		}

	private:
		T* ptr_;
		size_t* count_;

	};
} // namespace stepik