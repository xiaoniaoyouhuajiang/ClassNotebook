#pragma once

#ifndef SHAREDPTR_HPP_INCLUDED
#define SHAREDPTR_HPP_INCLUDED

namespace rabid
{
	template <typename T>
	class shared_ptr
	{
	public:
		explicit shared_ptr(T *ptr = 0)
		{
			this->ptr = ptr;
			rcount = new long(0);
			(*rcount)++;
		}

		~shared_ptr()
		{
			if (--(*rcount) == 0) {
				delete ptr;
				delete rcount;
			}
		}

		shared_ptr(const shared_ptr & other) : ptr(other.ptr), rcount(other.rcount)
		{
			(*rcount)++;
		}

		// копирование для полиморф.
		template <class Y> shared_ptr(const shared_ptr <Y> & other) : ptr(other.ptr), rcount(other.rcount)
		{
			(*rcount)++;
		}

		shared_ptr& operator=(const shared_ptr & other)
		{
			if (this != &other)
			{
				if ((--(*rcount)) == 0)
				{
					delete ptr;
					delete rcount;
				}
				ptr = other.ptr;
				rcount = other.rcount;
				(*rcount)++;
			}
			return *this;
		};

		//оператор присваивания для полиморф.
		template<class Y> shared_ptr& operator=(const shared_ptr<Y> & other)
		{
			shared_ptr<T>(other).swap(*this);
		};


		explicit operator bool() const
		{
			return (ptr != nullptr);
		}

		T* get() const
		{
			return ptr;
		}

		long use_count() const
		{
			if (ptr) return *rcount;
			else return 0;
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
			std::swap(rcount, x.rcount);
		}

		void reset(T *other = 0)
		{
			// implement this 
			shared_ptr(other).swap(*this);
		}

	private:
		// data members
		T *ptr;
		long *rcount;
		template<class U> friend class shared_ptr;
	};

	template < class T, class U > bool operator==(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept
	{
		return lhs.get() == rhs.get();
	};

	template< class T, class U > bool operator!=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept
	{
		return !(lhs == rhs);
	};

	template< class T, class U > bool operator<(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept
	{
		return lhs.get() < rhs.get();
	};

	template < class T, class U > bool operator>(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept
	{
		return rhs < lhs;
	};

	template < class T, class U > bool operator<=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept
	{
		return !(rhs < lhs);
	};

	template < class T, class U > bool operator>=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs) noexcept
	{
		return !(lhs < rhs);
	};

} // namespace rabid


#endif