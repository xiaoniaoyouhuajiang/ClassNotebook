#include <algorithm> // std::swap

namespace stepik
{
	template <typename T>
	class shared_ptr{
		template <typename U>
		friend class shared_ptr;
	public:
		explicit shared_ptr(T *ptr = 0){
			_ptr = ptr;
			if (_ptr){
				ref = new long(1);
			}
			else{
				ref = nullptr;
			}
		}

		~shared_ptr()
		{
			release();
		}

		template <typename U>
		shared_ptr(const shared_ptr<U> & other) : _ptr(other._ptr)
		{
			ref = other.ref;
			if (ref) ++(*ref);
		}

		shared_ptr(const shared_ptr & other) : _ptr(other._ptr)
		{
			ref = other.ref;
			if (ref) ++(*ref);
		}

		template <typename U>
		shared_ptr& operator=(const shared_ptr<U> & other)
		{
			if (this != &other){
				release();
				_ptr = other._ptr;
				ref = other.ref;
				if (ref) ++(*ref);
			}

			return *this;
		}

		shared_ptr& operator=(const shared_ptr & other)
		{
			if (this != &other){
				release();
				_ptr = other._ptr;
				ref = other.ref;
				if (ref) ++(*ref);
			}

			return *this;
		}

		explicit operator bool() const
		{
			return _ptr != nullptr;
		}

		T* get() const
		{
			return _ptr;
		}

		long use_count() const
		{
			return *this ? *ref : 0;
		}

		T& operator*() const
		{
			return *_ptr;
		}

		T* operator->() const
		{
			return _ptr;
		}

		template <typename U>
		bool operator==(const shared_ptr<U> &other) const
		{
			return (_ptr == other._ptr);
		}

		void swap(shared_ptr& x) //noexcept
		{
			std::swap(_ptr, x._ptr);
			std::swap(ref, x.ref);
		}

		void reset(T *ptr = 0)
		{
			release();
			_ptr = ptr;
			if (_ptr)
				ref = new long(1);
			else
				ref = nullptr;
		}

	private:
		T* _ptr;
		long *ref;
		void release()
		{
			if (_ptr &&  ref && (!--(*ref))){
				delete _ptr;
				delete ref;
				ref = 0;
			}
		}
	};
} // namespace stepik