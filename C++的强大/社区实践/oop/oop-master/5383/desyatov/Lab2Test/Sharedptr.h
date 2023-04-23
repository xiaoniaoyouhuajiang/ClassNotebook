#pragma once
#include <algorithm>
namespace stepik
{
	template <typename T>
	class shared_ptr
	{
	public:
		//Дружим, для того чтобы умный указтель одного имел доступ к приватным членам другого класса
		//Шаблоны, потому что типы могут быть разные
		template <typename U>

		friend class shared_ptr;

		shared_ptr()
		{
			pointer = nullptr;
			count = nullptr;
		}
		explicit shared_ptr(T *ptr)
		{
			// implement this

			pointer = ptr;
			count = new long(1);
		}

		~shared_ptr()
		{
			// implement this
			if (count != nullptr)
			{
				dec_count();
				if (*count == 0)
				{
					delete pointer;
					delete count;
				}
			}
		}

		shared_ptr(const shared_ptr& other)
		{
			pointer = other.pointer;
			count = other.count;
			if (count != nullptr)
				inc_count(); 
		}

		template <typename U>
		shared_ptr(const shared_ptr<U> & other)
		{
			// implement this
			pointer = other.pointer;
			count = other.count;
			if (count != nullptr)
				inc_count();
		}

		shared_ptr& operator=(const shared_ptr & other)
		{
			// implement this
			shared_ptr p(other);
			swap(p);
			return *this;
		}

		template <typename U>
		shared_ptr& operator=(const shared_ptr<U> & other)
		{
			// implement this
			shared_ptr p(other);
			swap(p);
			return *this;
		}

		template <typename U>
		bool operator==(const shared_ptr<U> &other) const
		{
			return (pointer == other.pointer);
		}
		explicit operator bool() const
		{
			// implement this
			if (pointer != nullptr)
				return true;
			else
				return false;
		}

		T* get() const
		{
			// implement this
			return pointer;
		}

		long use_count() const
		{
			// implement this
			if (count && pointer)
			{
				return *count;
			}
			else
				return 0;
		}

		T& operator*() const
		{
			// implement this
			return *pointer;
		}

		T* operator->() const
		{
			// implement this
			return pointer;
		}

		void swap(shared_ptr& x) noexcept
		{
			// implement this
			std::swap(pointer, x.pointer);
			std::swap(count, x.count);
		}

		void reset(T *ptr = 0)
		{

			// implement this   
			shared_ptr p(ptr);
			swap(p);
		}

	private:
		// data members
		T* pointer;
		long *count;
		inline void dec_count()
		{
			(*count)--;
		}
		inline void inc_count()
		{
			(*count)++;
		}
	};
} // namespace stepik