#pragma once
#include <algorithm>
#include <cstddef>


	template <typename T>
	class shared_ptr
	{

		T *m_ptr;
		size_t *m_count;
		template <typename S>
		friend class shared_ptr;
		// your implementation

	public:

		explicit shared_ptr(T *ptr = 0) :
			m_ptr(ptr), m_count(ptr ? new size_t(1) : nullptr)
		{
			// implement this    
		}

		~shared_ptr()
		{
			// implement this
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

		template <typename S>
		shared_ptr(const shared_ptr<S> & other)
		{
			// implement this
			if (other.get())
			{
				m_ptr = other.get();
				m_count = other.get_count();
				++(*m_count);

			}
			else {
				m_ptr = nullptr;
				m_count = nullptr;
			}

		}


		template <typename S>
		shared_ptr& operator = (const shared_ptr<S> & other)
		{
			// implement this
			shared_ptr tmp(other);
			this->swap(tmp);
			return *this;
		}


		template <typename S>
		bool operator==(const shared_ptr<S> &other) const
		{
			return (m_ptr == other.m_ptr);
		}

		explicit operator bool() const
		{
			// implement this
			return (m_ptr != nullptr);
		}

		T* get() const
		{
			// implement this
			return m_ptr;
		}

		size_t* get_count() const
		{
			return m_count;
		}

		long use_count() const
		{
			// implement this
			return (m_count) ? *m_count : 0;
		}

		T& operator*() const
		{
			// implement this
			return (*m_ptr);
		}

		T* operator->() const
		{
			// implement this
			return m_ptr;
		}

		void swap(shared_ptr& x) noexcept
		{
			// implement this
			std::swap(m_ptr, x.m_ptr);
			std::swap(m_count, x.m_count);
		}


		void reset(T *ptr = 0)
		{
			// implement this
			shared_ptr<T>(ptr).swap(*this);
		}

	};